"""
the general training framework
"""
from __future__ import print_function
#import sys
#sys.path.remove('/home/zmr/.local/lib/python3.7/site-packages')
#print(sys.path)

import os
import argparse
import socket
import time

import tensorboard_logger as tb_logger
import torch
import torch.optim as optim
import torch.nn as nn
import torch.backends.cudnn as cudnn

from models import model_dict

from dataset.stl10 import get_stl10_dataloaders
from dataset.cifar10 import get_cifar10_dataloaders
from dataset.cifar100 import get_cifar100_dataloaders
from dataset.imageCLEF import get_imageclef_dataloaders
from dataset.imagenet import get_imagenet_dataloaders, get_imagenet_v_dataloaders
from dataset.polarity import get_polarity_dataloaders
from dataset.mnist import get_mnist_dataloaders
from dataset.usps import get_usps_dataloaders

from helper.util import adjust_learning_rate

from helper.loops import train_kd as train_kd, validate, nfr_validate


def parse_option():

    hostname = socket.gethostname()

    parser = argparse.ArgumentParser('argument for training')

    parser.add_argument('--print_freq', type=int, default=100, help='print frequency')
    parser.add_argument('--tb_freq', type=int, default=500, help='tb frequency')
    parser.add_argument('--save_freq', type=int, default=40, help='save frequency')
    parser.add_argument('--batch_size', type=int, default=64, help='batch_size')
    parser.add_argument('--num_workers', type=int, default=8, help='num of workers to use')
    parser.add_argument('--epochs', type=int, default=300, help='number of training epochs')

    # test
    parser.add_argument('--test', type=int, default=0, help='if testing, set --test 1')

    # optimization
    parser.add_argument('--learning_algorithm', type=str, default='SGD', help='learning algorithm')
    parser.add_argument('--learning_rate', type=float, default=0.05, help='learning rate')
    parser.add_argument('--lr_decay_epochs', type=str, default='150,225', help='where to decay lr, can be a list')
    parser.add_argument('--lr_decay_rate', type=float, default=0.1, help='decay rate for learning rate')
    parser.add_argument('--weight_decay', type=float, default=5e-4, help='weight decay')
    parser.add_argument('--momentum', type=float, default=0.9, help='momentum')

    # dataset
    parser.add_argument('--dataset', type=str, default='cifar100', choices=['cifar100', 'cifar10', 'imagenet', 'tiny_imagenet', 'stl10', 'imageclef', 'lmdb'], help='dataset')
    parser.add_argument('--category', type=str, default='c', choices=['b', 'c', 'i', 'p']) # category for imageclef
    parser.add_argument('--version', type=float, default=1.0, choices=[1.0, 2.0])
    parser.add_argument('--dataset_size', type=float, default=1.0, choices=[1.0, 0.5, 0.25, 0.2, 0.1, 0.05, 0.01])

    # model1
    parser.add_argument('--old_model', type=str, default='resnet110',
                        choices=['mnistlenet', 'alexnet32', 'rnn', 'alexnet', 'resnet8', 'resnet14', 'resnet20', 'resnet32', 'resnet44', 'resnet56', 'resnet110',
                                'resnet8x4', 'resnet32x4', 'wrn_10_2', 'wrn_16_1', 'wrn_16_2', 'wrn_40_1', 'wrn_40_2',
                                'vgg8', 'vgg11', 'vgg13', 'vgg16', 'vgg19', 
                                'ResNet18', 'ResNet34', 'ResNet50', 'ResNet101', 'ResNet152', 
                                'MobileNetV2', 'ShuffleV1', 'ShuffleV2',
                                'densenet100', 'densenet40', 'densenet121', 'densenet161', 'densenet169', 'densenet201',
                                'resnext101', 'resnext29', 'inceptionv3', 'MobileNetLarge', 'MobileNetSmall', 'prevgg11'])
    parser.add_argument('--is_model_old', type=int, default=1, choices=[0,1])
    parser.add_argument('--del_module_old', type=int, default=1, choices=[0,1])

    # model2
    parser.add_argument('--new_model', type=str, default='resnet110',
                        choices=['mnistlenet', 'alexnet32', 'rnn', 'resnet8', 'resnet14', 'resnet20', 'resnet32', 'resnet44', 'resnet56', 'resnet110',
                                'resnet8x4', 'resnet32x4', 'wrn_10_2', 'wrn_16_1', 'wrn_16_2', 'wrn_40_1', 'wrn_40_2',
                                'vgg8', 'vgg11', 'vgg13', 'vgg16', 'vgg19', 
                                'ResNet18', 'ResNet34', 'ResNet50', 'ResNet101', 'ResNet152', 
                                'MobileNetV2', 'ShuffleV1', 'ShuffleV2',
                                'densenet100', 'densenet40', 'densenet121', 'densenet161', 'densenet169', 'densenet201',
                                'resnext101', 'resnext29', 'inceptionv3', 'MobileNetLarge', 'MobileNetSmall', 
                                'efficientnet', 'wrn', 'preMobileNetLarge'])
    parser.add_argument('--is_model_new', type=int, default=1, choices=[0,1])
    parser.add_argument('--del_module_new', type=int, default=1, choices=[0,1])

    parser.add_argument('--oldmodel_path', type=str, help='old model snapshot')
    parser.add_argument('--newmodel_path', type=str, help='new model snapshot')

    # distillation
    parser.add_argument('--distill', type=str, default='kd', choices=['kd', 'lm'])

    parser.add_argument('--trial', type=str, default='1', help='trial id')

    parser.add_argument('-r', '--gamma', type=float, default=1, help='weight for classification')
    parser.add_argument('-a', '--alpha', type=float, default=None, help='weight balance for KD')

    # KL distillation
    parser.add_argument('--kd_T', type=float, default=4, help='temperature for KD distillation')

    opt = parser.parse_args()

    # set different learning rate from these 4 models
    if opt.new_model in ['MobileNetV2', 'ShuffleV1', 'ShuffleV2']:
        opt.learning_rate = 0.01

    opt.model_path = './save/student_model'
    opt.tb_path = './save/student_tensorboards'

    iterations = opt.lr_decay_epochs.split(',')
    opt.lr_decay_epochs = list([])
    for it in iterations:
        opt.lr_decay_epochs.append(int(it))
    
    opt.model_name = '{}_{}_{}_{}_{}_trial_{}'.format(opt.old_model, opt.new_model, opt.dataset, opt.dataset_size, opt.distill, opt.trial)

    opt.tb_folder = os.path.join(opt.tb_path, opt.model_name)
    if not os.path.isdir(opt.tb_folder):
        os.makedirs(opt.tb_folder)

    opt.save_folder = os.path.join(opt.model_path, opt.model_name)
    if not os.path.isdir(opt.save_folder):
        os.makedirs(opt.save_folder)

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

def main():
    best_acc = 0
    least_nfr = 100

    opt = parse_option()

    # dataloader
    n_cls = 0
    if opt.dataset == 'cifar100':
        train_loader, val_loader, _, _ = get_cifar100_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 100
    elif opt.dataset == 'imageclef':
        train_loader, val_loader, _, _ = get_imageclef_dataloaders(category=opt.category, batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 12        
    elif opt.dataset == 'cifar10':
        train_loader, val_loader, _, _ = get_cifar10_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10
    elif opt.dataset == 'imagenet':
        if 'inception' in opt.model:
            train_loader, val_loader, _, _ = get_imagenet_v_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers)
        else:
            train_loader, val_loader, _, _ = get_imagenet_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers)
        n_cls = 1000
    elif opt.dataset == 'stl10':
        train_loader, val_loader, _, _ = get_stl10_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers)
        n_cls = 10
    elif opt.dataset == 'polarity':
        train_loader, val_loader, _, _ = get_polarity_dataloaders(version=opt.version, batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 2
    elif opt.dataset == 'mnist':
        train_loader, val_loader, _, _ = get_mnist_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10
    elif opt.dataset == 'usps':
        train_loader, val_loader, _, _ = get_usps_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10       
    else:
        raise NotImplementedError(opt.dataset)
    opt.n_cls = n_cls

    old_model = model_dict[opt.old_model](num_classes=n_cls)
    new_model = model_dict[opt.new_model](num_classes=n_cls)

    old_model.load_state_dict(remove_module_in_state_dict(opt.oldmodel_path, del_module=opt.del_module_old, is_model=opt.is_model_old))

    # tensorboard logger
    logger = tb_logger.Logger(logdir=opt.tb_folder, flush_secs=2)

    old_model.eval()

    module_list = nn.ModuleList([])
    module_list.append(old_model)
    module_list.append(new_model)

    criterion_cls = nn.CrossEntropyLoss()
    
    if torch.cuda.is_available():
        old_model = nn.DataParallel(old_model)
        new_model = nn.DataParallel(new_model)
        old_model = old_model.cuda()
        new_model = new_model.cuda()
        criterion_cls.cuda()
        cudnn.benchmark = True

    # validate teacher accuracy
    o_acc, _, _ = validate(val_loader, old_model, criterion_cls, opt)
    print('old_model accuracy: ', o_acc)

    # optimizer
    if opt.learning_algorithm == 'SGD':
        optimizer = optim.SGD(new_model.parameters(),
                            lr=opt.learning_rate,
                            momentum=opt.momentum,
                            weight_decay=opt.weight_decay)
    elif opt.learning_algorithm == 'adam':
        optimizer = optim.Adam(new_model.parameters(),
                            lr=opt.learning_rate,
                            weight_decay=opt.weight_decay)

    
    for epoch in range(1, opt.epochs + 1):

        adjust_learning_rate(epoch, opt, optimizer)
        print("==> training...")

        time1 = time.time()
        train_acc, train_nfr, train_loss = train_kd(epoch, train_loader, module_list, criterion_cls, optimizer, opt)
        time2 = time.time()
        print('epoch {}, total time {:.2f}'.format(epoch, time2 - time1))

        logger.log_value('train_acc', train_acc, epoch)
        logger.log_value('train_loss', train_loss, epoch)
        logger.log_value('train_nfr', train_nfr, epoch)

        test_acc, test_acc_top5, test_nfr, test_nfr_top5, test_loss = nfr_validate(val_loader, new_model, old_model, criterion_cls, opt)
        logger.log_value('test_acc', test_acc, epoch)
        logger.log_value('test_loss', test_loss, epoch)
        logger.log_value('test_acc_top5', test_acc_top5, epoch)
        logger.log_value('test_nfr', test_nfr, epoch)
        logger.log_value('test_nfr_top5', test_nfr_top5, epoch)

        # save the best model
        if test_acc > best_acc:
            best_acc = test_acc
            state = {
                'epoch': epoch,
                'model': new_model.state_dict(),
                'best_acc': best_acc,
            }
            save_file = os.path.join(opt.save_folder, '{}_best.pth'.format(opt.new_model))
            best_file = save_file
            print('saving the best model!')
            torch.save(state, save_file)
        
        # save the least nfr model
        if test_nfr < least_nfr:
            least_nfr = test_nfr
            state = {
                'epoch': epoch,
                'model': new_model.state_dict(),
                'best_acc': test_acc,
            }
            save_file = os.path.join(opt.save_folder, '{}_least_NFR.pth'.format(opt.new_model))
            least_nfr_file = save_file
            print('saving the least NFR model!')
            torch.save(state, save_file)

        # regular saving
        if epoch % opt.save_freq == 0:
            print('==> Saving...')
            state = {
                'epoch': epoch,
                'model': new_model.state_dict(),
                'accuracy': test_acc,
            }
            save_file = os.path.join(opt.save_folder, 'ckpt_epoch_{epoch}.pth'.format(epoch=epoch))
            torch.save(state, save_file)

    
    # This best accuracy is only for printing purpose.
    # The results reported in the paper/README is from the last epoch. 
    print('best accuracy: ', best_acc)
    print('least nfr: ', least_nfr)

if __name__ == '__main__':
    main()
