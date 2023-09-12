from __future__ import print_function

import os
import argparse
import socket
import time

import tensorboard_logger as tb_logger
import torch
import torch.nn as nn
import torch.backends.cudnn as cudnn
import torch.nn.functional as F
import numpy as np

from models import model_dict

from dataset.stl10 import get_stl10_dataloaders
from dataset.cifar10 import get_cifar10_dataloaders
from dataset.cifar100 import get_cifar100_dataloaders
from dataset.imageCLEF import get_imageclef_dataloaders
from dataset.imagenet import get_imagenet_dataloaders, get_imagenet_v_dataloaders
from dataset.objectnet import get_objectnet_dataloaders
from dataset.mnist import get_mnist_dataloaders
from dataset.emnist import get_emnist_dataloaders

from helper.util import accuracy, AverageMeter, acc_nf
from helper.temperature_scaling import ModelWithTemperature, _ECELoss
from helper.loops import train_vanilla as train, validate

torch.manual_seed(1)
np.random.seed(1)

def parser_option():
    hostname = socket.gethostname()

    parser = argparse.ArgumentParser('argument for training')

    parser.add_argument('--print_freq', type=int, default=100, help='print frequency')
    parser.add_argument('--tb_freq', type=int, default=500, help='tb frequency')
    parser.add_argument('--save_freq', type=int, default=40, help='save frequency')
    parser.add_argument('--batch_size', type=int, default=64, help='batch_size')
    parser.add_argument('--num_workers', type=int, default=8, help='num of workers to use')

    # model1
    parser.add_argument('--old_model', type=str, default='resnet110',
                        choices=['mnistlenet', 'alexnet32', 'rnn', 'alexnet', 'resnet8', 'resnet14', 'resnet20', 'resnet32', 'resnet44', 'resnet56', 'resnet110',
                                'resnet8x4', 'resnet32x4', 'wrn_10_2', 'wrn_16_1', 'wrn_16_2', 'wrn_40_1', 'wrn_40_2',
                                'vgg8', 'vgg11', 'vgg13', 'vgg16', 'vgg19', 
                                'cifarresnet18', 'cifarresnet34', 'cifarresnet50', 'cifarresnet101', 'cifarresnet152', 
                                'ResNet18', 'ResNet34', 'ResNet50', 'ResNet101', 'ResNet152', 
                                'MobileNetV2', 'ShuffleV1', 'ShuffleV2',
                                'densenet100', 'densenet40', 'densenet121', 'densenet161', 'densenet169', 'densenet201',
                                'resnext101', 'resnext29', 'inceptionv3', 'MobileNetLarge', 'MobileNetSmall', 'prevgg11'])
    parser.add_argument('--is_model_old', type=int, default=1, choices=[0,1])
    parser.add_argument('--del_module_old', type=int, default=1, choices=[0,1])

    # model2
    parser.add_argument('--new_model', type=str, default='resnet110',
                        choices=['mnistlenet', 'alexnet32', 'lenet', 'rnn', 'resnet8', 'resnet14', 'resnet20', 'resnet32', 'resnet44', 'resnet56', 'resnet110',
                                'resnet8x4', 'resnet32x4', 'wrn_10_2', 'wrn_16_1', 'wrn_16_2', 'wrn_40_1', 'wrn_40_2',
                                'vgg8', 'vgg11', 'vgg13', 'vgg16', 'vgg19', 
                                'cifarresnet18', 'cifarresnet34', 'cifarresnet50', 'cifarresnet101', 'cifarresnet152', 
                                'ResNet18', 'ResNet34', 'ResNet50', 'ResNet101', 'ResNet152', 
                                'MobileNetV2', 'ShuffleV1', 'ShuffleV2',
                                'densenet100', 'densenet40', 'densenet121', 'densenet161', 'densenet169', 'densenet201',
                                'resnext101', 'resnext29', 'inceptionv3', 'MobileNetLarge', 'MobileNetSmall', 
                                'efficientnet', 'wrn', 'preMobileNetLarge'])
    parser.add_argument('--is_model_new', type=int, default=1, choices=[0,1])
    parser.add_argument('--del_module_new', type=int, default=1, choices=[0,1])

    parser.add_argument('--ensemble', type=str, default='compare', choices=['compare'])
    parser.add_argument('--tau', type=float, default=1.0, help='rate of requirement')


    parser.add_argument('--oldmodel_path', type=str, help='old model snapshot')
    parser.add_argument('--newmodel_path', type=str, help='new model snapshot')

    parser.add_argument('--T1', type=float, help='temperature for old model')
    parser.add_argument('--T2', type=float, help='temperature for new model')

    parser.add_argument('--dataset', type=str, default='cifar100', choices=['mnist', 'emnist', 'polarity', 'cifar10', 'cifar100', 'imagenet', 'objectnet', 'stl10', 'imageclef'], help='dataset')
    parser.add_argument('--category', type=str, default='c', choices=['b', 'c', 'i', 'p']) # category for imageclef
    parser.add_argument('--version', type=float, default=1.0, choices=[1.0, 2.0])    
    parser.add_argument('--dataset_size', type=float, default=1.0, choices=[1.0, 0.5, 0.25])

    parser.add_argument('--record', type=int, default=0)

    opt = parser.parse_args()
    print('old model: ', opt.old_model)
    print('new model: ', opt.new_model)
    
    return opt

def remove_module_in_state_dict(filepath, del_module=False, is_model=True):
    if is_model:
        state_dict = torch.load(filepath, map_location='cuda:0')['model']
    else:
        state_dict = torch.load(filepath, map_location='cuda:0')

    if del_module == False:
        # state_dict = torch.load(filepath, map_location='cuda:0')
        return state_dict

    from collections import OrderedDict
    new_state_dict = OrderedDict()
    for k, v in state_dict.items():
        name = k[7:]
        new_state_dict[name] = v
    return new_state_dict

def test(model, data_loader, opt):
    acc = 0
    total = 0
    ece = 0
    conf = 0
    ece_loss = _ECELoss()
    mse_loss = nn.MSELoss()
    nll_criterion = nn.CrossEntropyLoss()
    logits = []
    softmaxes = []
    labels = []
    
    model.eval()
    with torch.no_grad():
        for idx, (inputs, targets) in enumerate(data_loader):
            inputs = inputs.float()
            if torch.cuda.is_available():
                inputs = inputs.cuda()
                targets = targets.cuda()
            output = model(inputs)
            logits.append(output)
            labels.append(targets)
            if opt.softmax == True:
                confs = torch.nn.functional.softmax(output, dim=-1)
            else:
                confs = output
            softmaxes.append(confs)
            confs, output = torch.max(confs, 1)
            conf += confs.sum()

            indicate = (output == targets)
            acc += indicate.sum()

            length = int(targets.shape[0])
            total += length

    logits = torch.cat(logits, 0)
    labels = torch.cat(labels, 0)
    conf = conf/total
    acc = acc/total
    softs = torch.cat(softmaxes, 0)
    targets = F.one_hot(labels, opt.n_cls)
    mse = mse_loss(softs, targets)
    # tmp_ce = - targets * torch.log(softs)
    # ce = torch.mean(tmp_ce.sum(dim=1))
    ce = nll_criterion(logits, labels)
    ece = ece_loss(logits, labels, opt.softmax).item()

    print('Accuracy of the model: {:.4f}, Cross entropy: {:.4f}, Mean squared error: {:.4f}, '.format(acc, ce, mse))
    print('ECE of the model: {:.4f}, avg conf of the model: {:.4f}'.format(ece, conf))
    return 

def nfr_validate(data_loader, old_model, new_model, opt):
    """validation"""
    batch_time = AverageMeter()
    losses = AverageMeter()
    nfr_losses = AverageMeter()
    top1 = AverageMeter()
    top5 = AverageMeter()
    nfr_top1 = AverageMeter()
    nfr_top5 = AverageMeter()

    # switch to evaluate mode
    old_model.eval()
    new_model.eval()

    with torch.no_grad():
        end = time.time()
        for idx, (input, target) in enumerate(data_loader):
            input = input.float()
            if torch.cuda.is_available():
                input = input.cuda()
                target = target.cuda()

            # compute output
            old_output = old_model(input)
            new_output = new_model(input)

            softmaxes_o = F.softmax(old_output, dim=1)
            softmaxes_o = softmaxes_o * F.one_hot(target, opt.n_cls)
            if opt.softmax == True:
                softmaxes_n = F.softmax(new_output, dim=1)
            else:
                softmaxes_n = new_output
            softmaxes_n = softmaxes_n * F.one_hot(target, opt.n_cls)
            confs_o, _ = torch.max(softmaxes_o, 1) 
            confs_n, _ = torch.max(softmaxes_n, 1)
            nfr_loss = -torch.log(confs_n + (1-confs_o) * (1-confs_n)).mean()
            loss = - torch.log(confs_n).mean()

            # measure accuracy and record loss
            if opt.n_cls <= 5:
                acc1, nfr1 = acc_nf(new_output, old_output, target, topk=(1,))
                top1.update(acc1[0].item(), input.size(0))
                top5.update(1.0, input.size(0))
                nfr_top1.update(nfr1[0].item(), input.size(0))
                nfr_top5.update(0.0, input.size(0))
            else:
                acc, nfr = acc_nf(new_output, old_output, target, topk=(1, 5))
                acc1, acc5 = acc[0], acc[1]
                nfr1, nfr5 = nfr[0], nfr[1]
                top1.update(acc1[0], input.size(0))
                top5.update(acc5[0], input.size(0))
                nfr_top1.update(nfr1[0], input.size(0))
                nfr_top5.update(nfr5[0], input.size(0))                

            losses.update(loss.item(), input.size(0))
            nfr_losses.update(nfr_loss, input.size(0))

            # measure elapsed time
            batch_time.update(time.time() - end)
            end = time.time()

            if idx % opt.print_freq == 0:
                print('Test: [{0}/{1}]\t'
                      'Time {batch_time.val:.3f} ({batch_time.avg:.3f})\t'
                      'Loss {loss.val:.4f} ({loss.avg:.4f})\t'
                      'Acc@1 {top1.val:.3f} ({top1.avg:.3f})\t'
                      'Acc@5 {top5.val:.3f} ({top5.avg:.3f})\t'
                      'NFR@1 {nfr_top1.avg:.3f} ({nfr_top1.avg:.3f})\t'
                      'NFR@5 {nfr_top5.avg:.3f} ({nfr_top5.avg:.3f})'.format(
                       idx, len(data_loader), batch_time=batch_time, loss=losses,
                       top1=top1, top5=top5, nfr_top1=nfr_top1, nfr_top5=nfr_top5))

        print(' * Acc@1 {top1.avg:.3f} Acc@5 {top5.avg:.3f} NFR@1 {nfr_top1.avg:.3f} NFR@5 {nfr_top5.avg:.3f} ce_loss {loss.avg:.3f} nfr_loss {nfr_loss.avg:.3f}'
              .format(top1=top1, top5=top5, nfr_top1=nfr_top1, nfr_top5=nfr_top5, loss=losses, nfr_loss=nfr_losses))

    return top1.avg, top5.avg, nfr_top1.avg, nfr_top5.avg, losses.avg

def rho_estimate(data_loader, old_model, new_model, opt):
    # switch to evaluate mode
    old_model.eval()
    new_model.eval()
    mse_loss = nn.MSELoss()
    old_logits = []
    new_logits = []
    labels = []
    with torch.no_grad():
        for idx, (inputs, targets) in enumerate(data_loader):
            inputs = inputs.float()
            if torch.cuda.is_available():
                inputs = inputs.cuda()
                targets = targets.cuda()
            old_output = old_model(inputs)
            new_output = new_model(inputs)
            old_logits.append(old_output)
            new_logits.append(new_output)
            labels.append(targets)

    old_logits = torch.cat(old_logits, 0)
    new_logits = torch.cat(new_logits, 0)
    labels = torch.cat(labels, 0)

    if opt.softmax == True:
        old_confs = torch.nn.functional.softmax(old_logits, dim=-1).cpu()
        new_confs = torch.nn.functional.softmax(new_logits, dim=-1).cpu()
    else:
        old_confs = old_logits.cpu()
        new_confs = new_logits.cpu()

    from scipy import stats
    import numpy as np
    corrs = []
    for k in range(opt.n_cls):
        rho = stats.pearsonr(old_confs[:, k], new_confs[:, k])
        corrs.append(rho)
    
    mse_corr = torch.mean(torch.sum((new_confs - old_confs).square(), dim=1))
    print('Correlation of old and new model is {:.4f}, mse is {:.4f}'.format(np.mean(corrs), mse_corr))
    return 

def main():
    opt = parser_option()

    # dataloader
    n_cls = 0
    if opt.dataset == 'cifar100':
        _, _, val_loader, test_loader = get_cifar100_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 100
    elif opt.dataset == 'imageclef':
        _, _, val_loader, test_loader = get_imageclef_dataloaders(category=opt.category, batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 12        
    elif opt.dataset == 'cifar10':
        _, _, val_loader, test_loader = get_cifar10_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10
    elif opt.dataset == 'imagenet':
        if 'inception' in opt.model:
            _, _, val_loader, test_loader = get_imagenet_v_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers)
        else:
            _, _, val_loader, test_loader = get_imagenet_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers)
        n_cls = 1000
    elif opt.dataset == 'stl10':
        _, _, val_loader, test_loader = get_stl10_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers)
        n_cls = 10
    elif opt.dataset == 'polarity':
        _, _, val_loader, test_loader = get_polarity_dataloaders(version=opt.version, batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 2
    elif opt.dataset == 'mnist':
        _, _, val_loader, test_loader = get_mnist_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10
    elif opt.dataset == 'emnist':
        _, _, val_loader, test_loader = get_emnist_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10  
    elif opt.dataset == 'objectnet':
        _, _, val_loader, test_loader = get_objectnet_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 1000  
    else:
        raise NotImplementedError(opt.dataset)
    opt.n_cls = n_cls

    old_model = model_dict[opt.old_model](num_classes=n_cls)
    new_model = model_dict[opt.new_model](num_classes=n_cls)

    old_model.load_state_dict(remove_module_in_state_dict(opt.oldmodel_path, del_module=opt.del_module_old, is_model=opt.is_model_old))
    new_model.load_state_dict(remove_module_in_state_dict(opt.newmodel_path, del_module=opt.del_module_new, is_model=opt.is_model_new))

    # old_model.eval()
    # new_model.eval()
    # old_model = ModelWithTemperature(old_model)
    # old_model.set_temperature(val_loader)
    # new_model = ModelWithTemperature(new_model)
    # new_model.set_temperature(val_loader)

    old_model.eval()
    new_model.eval()

    criterion_cls = nn.CrossEntropyLoss()
    opt.softmax = True

    if torch.cuda.is_available():
        old_model = nn.DataParallel(old_model)
        new_model = nn.DataParallel(new_model)        
        old_model = old_model.cuda()
        new_model = new_model.cuda()
        cudnn.benchmark = True

    print('eval the old model:')
    test(old_model, test_loader, opt)
    print('eval the new model:')
    test(new_model, test_loader, opt)

    # estimate correlation]
    rho_estimate(test_loader, old_model, new_model, opt)

    # nfr compute
    nfr_validate(val_loader, old_model, new_model, opt)
    nfr_validate(test_loader, old_model, new_model, opt)


    model_e = model_dict['ensemble_model'](model1=old_model, model2=new_model, opt=opt)

    if torch.cuda.is_available():
        model_e = model_e.cuda()
    
    model_e.eval()

    model_e.compare(test_loader, opt)
    



if __name__ == '__main__':
    main()



