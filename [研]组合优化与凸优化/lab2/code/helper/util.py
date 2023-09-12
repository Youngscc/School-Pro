from __future__ import print_function

import torch
import numpy as np
from torch import nn

def set_parameter_requires_grad(model, opt):
    for param in model.parameters():
        param.required_grad = False
    if 'resnet' in opt.model or 'ResNet' in opt.model:
        model.fc = nn.Linear(model.fc.in_features, opt.n_cls)
    elif 'densenet' in opt.model:
        model.classifier = nn.Linear(model.classifier.in_features, opt.n_cls)
    elif 'alexnet' in opt.model:
        model.classifier[6] = nn.Linear(4096, opt.n_cls)


def adjust_learning_rate_new(epoch, optimizer, LUT):
    """
    new learning rate schedule according to RotNet
    """
    lr = next((lr for (max_epoch, lr) in LUT if max_epoch > epoch), LUT[-1][1])
    for param_group in optimizer.param_groups:
        param_group['lr'] = lr


def adjust_learning_rate(epoch, opt, optimizer):
    """Sets the learning rate to the initial LR decayed by decay rate every steep step"""
    steps = np.sum(epoch > np.asarray(opt.lr_decay_epochs))
    if steps > 0:
        new_lr = opt.learning_rate * (opt.lr_decay_rate ** steps)
        for param_group in optimizer.param_groups:
            param_group['lr'] = new_lr


class AverageMeter(object):
    """Computes and stores the average and current value"""
    def __init__(self):
        self.reset()

    def reset(self):
        self.val = 0
        self.avg = 0
        self.sum = 0
        self.count = 0

    def update(self, val, n=1):
        self.val = val
        self.sum += val * n
        self.count += n
        self.avg = self.sum / self.count


def accuracy(output, target, topk=(1,)):
    """Computes the accuracy over the k top predictions for the specified values of k"""
    with torch.no_grad():
        maxk = max(topk)
        batch_size = target.size(0)

        _, pred = output.topk(maxk, 1, True, True)
        #print(pred.shape)
        pred = pred.t()
        #print(pred.shape)
        correct = pred.eq(target.view(1, -1).expand_as(pred))
        #print(correct.shape)

        res = []
        for k in topk:
            #print(k, correct[:k].shape)
            correct_k = correct[:k].contiguous().view(-1).float().sum(0, keepdim=True)
            res.append(correct_k.mul_(100.0 / batch_size))
        return res

def acc_nf(output_new, output_old, target, topk=(1,)):

    with torch.no_grad():
        maxk = max(topk)
        batch_size = target.size(0)

        _, pred_new = output_new.topk(maxk, 1, True, True)
        _, pred_old = output_old.topk(maxk, 1, True, True)
        pred_new = pred_new.t()
        pred_old = pred_old.t()
        correct_new = pred_new.eq(target.view(1, -1).expand_as(pred_new))
        correct_old = pred_old.eq(target.view(1, -1).expand_as(pred_old))

        nf = (~ correct_new) * (correct_old)
        #print(correct_new.shape)
        #print(correct_old.shape)
        #print(correct_new) #[0], correct_new[1], correct_new[2], correct_new[3], correct_new[4])
        #print(correct_old)
        #print(nf)
        #assert 0
        acc = []
        nfr = []
    
        for k in topk:
            correct_k = correct_new[:k].contiguous().view(-1).float().sum(0, keepdim=True)
            acc.append(correct_k.mul_(100.0 / batch_size))

            nfr_k = nf[:k].contiguous().view(-1).float().sum(0, keepdim=True)
            nfr.append(nfr_k.mul_(100.0 / batch_size))

    return acc, nfr

if __name__ == '__main__':

    pass
