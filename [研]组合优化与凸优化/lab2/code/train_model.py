from __future__ import print_function

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

from dataset.imageCLEF import get_imageclef_dataloaders
from dataset.stl10 import get_stl10_dataloaders
from dataset.cifar10 import get_cifar10_dataloaders
from dataset.cifar100 import get_cifar100_dataloaders
from dataset.imagenet import get_imagenet_dataloaders
from dataset.svhn import get_svhn_dataloaders
from dataset.mnist import get_mnist_dataloaders
from dataset.emnist import get_emnist_dataloaders

from helper.util import adjust_learning_rate, accuracy, AverageMeter, set_parameter_requires_grad
from helper.loops import train_vanilla as train, validate

def parse_option():

    hostname = socket.gethostname()

    parser = argparse.ArgumentParser('argument for training')

    parser.add_argument('--print_freq', type=int, default=100, help='print frequency')
    parser.add_argument('--tb_freq', type=int, default=500, help='tb frequency')
    parser.add_argument('--save_freq', type=int, default=40, help='save frequency')
    parser.add_argument('--batch_size', type=int, default=64, help='batch_size')
    parser.add_argument('--num_workers', type=int, default=8, help='num of workers to use')
    parser.add_argument('--epochs', type=int, default=300, help='number of training epochs')

    # optimization
    parser.add_argument('--learning_algorithm', type=str, default='SGD', help='learning algorithm')
    parser.add_argument('--learning_rate', type=float, default=0.05, help='learning rate')
    parser.add_argument('--lr_decay_epochs', type=str, default='150,225,300', help='where to decay lr, can be a list')
    parser.add_argument('--lr_decay_rate', type=float, default=0.1, help='decay rate for learning rate')
    parser.add_argument('--weight_decay', type=float, default=0.0, help='weight decay')
    parser.add_argument('--momentum', type=float, default=0.9, help='momentum')

    # dataset
    parser.add_argument('--model', type=str, default='resnet110',
                        choices=['mnistlenet', 'alexnet32', 'rnn', 'alexnet', 'resnet8', 'resnet14', 'resnet20', 'resnet32', 'resnet44', 'resnet56', 'resnet110',
                                'resnet8x4', 'resnet32x4', 'wrn_10_2', 'wrn_16_1', 'wrn_16_2', 'wrn_40_1', 'wrn_40_2',
                                'vgg8', 'vgg11', 'vgg13', 'vgg16', 'vgg19', 
                                'cifarresnet18', 'cifarresnet34', 'cifarresnet50', 'cifarresnet101', 'cifarresnet152', 
                                'ResNet18', 'ResNet34', 'ResNet50', 'ResNet101', 'ResNet152', 
                                'MobileNetV2', 'ShuffleV1', 'ShuffleV2',
                                'densenet100', 'densenet40', 'densenet121', 'densenet161', 'densenet169', 'densenet201',
                                'resnext101', 'resnext29', 'inceptionv3', 'MobileNetLarge', 'MobileNetSmall'])
    parser.add_argument('--finetune', type=int, default=0, choices=[0, 1])                                
    parser.add_argument('--pretrained', type=int, default=0, choices=[0, 1])
    parser.add_argument('--dataset', type=str, default='cifar100', choices=['mnist', 'emnist', 'svhn', 'cifar10', 'cifar100', 'imagenet', 'tiny_imagenet', 'stl10', 'imageclef'], help='dataset')
    parser.add_argument('--category', type=str, default='c', choices=['b', 'c', 'i', 'p', 'b+c']) # category for imageclef
    parser.add_argument('--version', type=str, default='101', choices=['101', '256'])
    parser.add_argument('--dataset_size', type=float, default=1.0, choices=[1.0, 0.8, 0.5, 0.25, 0.2, 0.1, 0.05, 0.01])

    # block depth
    parser.add_argument('--block_depth', type=str, default='3,3,3', help='the depth of each block')

    parser.add_argument('-t', '--trial', type=int, default=0, help='the experiment id')

    # train method
    parser.add_argument('--train_method', type=str, default='CE', choices=['CE', 'FL'])
    parser.add_argument('--miscls_path', type=str, default=None, help='misclassified samples\' filenames' )

    opt = parser.parse_args()
    
    # set different learning rate from these 4 models
    if opt.model in ['MobileNetV2', 'ShuffleV1', 'ShuffleV2']:
        opt.learning_rate = 0.01

    # set the path according to the environment
    opt.model_path = './save/models'
    opt.tb_path = './save/tensorboard'

    iterations = opt.lr_decay_epochs.split(',')
    opt.lr_decay_epochs = list([])
    for it in iterations:
        opt.lr_decay_epochs.append(int(it))

    iterations = opt.block_depth.split(',')
    opt.block_depth = list([])
    for it in iterations:
        opt.block_depth.append(int(it))

    opt.model_name = '{}_{}_{}_lr_{}_decay_{}_trial_{}'.format(opt.model, opt.dataset, opt.dataset_size, opt.learning_rate,
                                                            opt.weight_decay, opt.trial)


    opt.tb_folder = os.path.join(opt.tb_path, opt.model_name)
    if not os.path.isdir(opt.tb_folder):
        os.makedirs(opt.tb_folder)

    opt.save_folder = os.path.join(opt.model_path, opt.model_name)
    if not os.path.isdir(opt.save_folder):
        os.makedirs(opt.save_folder)

    return opt


def main():
    best_acc = 0
    last_acc = 0

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
        train_loader, val_loader, _, _ = get_stl10_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10
    elif opt.dataset == 'svhn':
        train_loader, val_loader, _, _ = get_svhn_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 20
    elif opt.dataset == 'mnist':
        train_loader, val_loader, _, _ = get_mnist_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10
    elif opt.dataset == 'emnist':
        train_loader, val_loader, _, _ = get_emnist_dataloaders(batch_size=opt.batch_size, num_workers=opt.num_workers, size=opt.dataset_size)
        n_cls = 10       
    else:
        raise NotImplementedError(opt.dataset)
    opt.n_cls = n_cls

    # model
    if opt.pretrained:
        tmp_model = 'pre' + opt.model
        model = model_dict[tmp_model](pretrained=True)
    elif opt.finetune:
        tmp_model = 'pre' + opt.model
        model = model_dict[tmp_model](pretrained=True)
        set_parameter_requires_grad(model, opt)        
    else:
        model = model_dict[opt.model](num_classes=n_cls)

    # optimizer
    if opt.learning_algorithm == 'SGD':
        optimizer = optim.SGD(model.parameters(),
                            lr=opt.learning_rate,
                            momentum=opt.momentum,
                            weight_decay=opt.weight_decay)
    elif opt.learning_algorithm == 'adam':
        optimizer = optim.Adam(model.parameters(),
                            lr=opt.learning_rate,
                            weight_decay=opt.weight_decay)


    if opt.train_method == 'CE':
        criterion = nn.CrossEntropyLoss()
    elif opt.train_method == 'FL':
        criterion = FocalLoss()
    else:
        NotImplementedError(opt.train_method)

    if torch.cuda.is_available():
        model = nn.DataParallel(model)
        model = model.cuda()
        criterion = criterion.cuda()
        cudnn.benchmark = True

    # tensorboard
    logger = tb_logger.Logger(logdir=opt.tb_folder, flush_secs=2)

    # routine
    for epoch in range(1, opt.epochs + 1):

        adjust_learning_rate(epoch, opt, optimizer)
        print("==> training...")

        time1 = time.time()
        train_acc, train_loss = train(epoch, train_loader, model, criterion, optimizer, opt)
        time2 = time.time()
        print('epoch {}, total time {:.2f}'.format(epoch, time2 - time1))

        logger.log_value('train_acc', train_acc, epoch)
        logger.log_value('train_loss', train_loss, epoch)

        test_acc, test_acc_top5, test_loss = validate(val_loader, model, criterion, opt)

        logger.log_value('test_acc', test_acc, epoch)
        logger.log_value('test_acc_top5', test_acc_top5, epoch)
        logger.log_value('test_loss', test_loss, epoch)

        # save the best model
        if test_acc > best_acc:
            best_acc = test_acc
            state = {
                'epoch': epoch,
                'model': model.state_dict(),
                'best_acc': best_acc,
                'optimizer': optimizer.state_dict(),
            }
            save_file = os.path.join(opt.save_folder, '{}_dataset_{}_best.pth'.format(opt.model, opt.dataset_size))
            print('saving the best model!')
            torch.save(state, save_file)

        # regular saving
        if epoch % opt.save_freq == 0:
            if epoch == opt.epochs:
                last_acc = test_acc
            print('==> Saving...')
            state = {
                'epoch': epoch,
                'model': model.state_dict(),
                'accuracy': test_acc,
                'optimizer': optimizer.state_dict(),
            }
            save_file = os.path.join(opt.save_folder, 'dataset_{size}_ckpt_epoch_{epoch}.pth'.format(size=opt.dataset_size, epoch=epoch))
            torch.save(state, save_file)

    # This best accuracy is only for printing purpose.
    # The results reported in the paper/README is from the last epoch.
    print('best accuracy on validation set:', best_acc)

    # save model
    state = {
        'opt': opt,
        'model': model.state_dict(),
        'optimizer': optimizer.state_dict(),
    }
    save_file = os.path.join(opt.save_folder, '{}_dataset_{}_last.pth'.format(opt.model, opt.dataset_size))
    torch.save(state, save_file)

    # with open('train_resnet.txt', 'a') as f:
        # f.write("model:{}, dataset:{}, best_acc:{}, last_acc:{}\n".format(opt.model, opt.dataset_size, best_acc, last_acc))


if __name__ == '__main__':
    main()
