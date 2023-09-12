from __future__ import print_function, division

import sys
import time
import torch
import torch.nn as nn

from helper.PCT.FD_KL import FD_KL
from helper.PCT.FD_LM import FD_LM

from .util import AverageMeter, accuracy, acc_nf

from torch.nn import functional as F

def train_vanilla(epoch, train_loader, model, criterion, optimizer, opt):
    """vanilla training"""
    model.train()

    batch_time = AverageMeter()
    data_time = AverageMeter()
    losses = AverageMeter()
    top1 = AverageMeter()
    top5 = AverageMeter()

    end = time.time()
    for idx, data in enumerate(train_loader):
        #input, target, _, _ = data
        inputs, targets = data
        data_time.update(time.time() - end)

        inputs = inputs.float()
        if torch.cuda.is_available():
            inputs = inputs.cuda()
            targets = targets.cuda()

        # ===================forward=====================
        output = model(inputs)
        loss = criterion(output, targets)

        if opt.n_cls <= 5:
            acc1 = accuracy(output, targets)
            # acc5 = [torch.Tensor([1.0])]
            top1.update(acc1[0].item(), inputs.size(0))
            top5.update(100.0, inputs.size(0))            
        else:
            acc1, acc5 = accuracy(output, targets, topk=(1, 5))
            top1.update(acc1[0], inputs.size(0))
            top5.update(acc5[0], inputs.size(0))
        losses.update(loss.item(), inputs.size(0))
        

        # ===================backward=====================
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        # ===================meters=====================
        batch_time.update(time.time() - end)
        end = time.time()

        # tensorboard logger
        pass

        # print info
        if idx % opt.print_freq == 0:
            print('Epoch: [{0}][{1}/{2}]\t'
                  'Time {batch_time.val:.3f} ({batch_time.avg:.3f})\t'
                  'Data {data_time.val:.3f} ({data_time.avg:.3f})\t'
                  'Loss {loss.val:.4f} ({loss.avg:.4f})\t'
                  'Acc@1 {top1.val:.3f} ({top1.avg:.3f})\t'
                  'Acc@5 {top5.val:.3f} ({top5.avg:.3f})'.format(
                   epoch, idx, len(train_loader), batch_time=batch_time,
                   data_time=data_time, loss=losses, top1=top1, top5=top5))
            sys.stdout.flush()

    print(' * Acc@1 {top1.avg:.3f} Acc@5 {top5.avg:.3f}'
          .format(top1=top1, top5=top5))

    return top1.avg, losses.avg

def train_kd(epoch, train_loader, module_list, criterion_cls, optimizer, opt):
    """One epoch distillation"""
    # set modules as train()
    for module in module_list:
        module.train()
    # set old_model as eval()
    module_list[0].eval()

    old_model = module_list[0]
    new_model = module_list[1]

    batch_time = AverageMeter()
    data_time = AverageMeter()
    losses = AverageMeter()
    top1 = AverageMeter()
    top5 = AverageMeter()
    nfr_top1 = AverageMeter()
    nfr_top5 = AverageMeter()

    if opt.distill == 'kd':
        reg_loss = FD_KL(T=opt.kd_T)
    elif opt.distill == 'lm': 
        reg_loss = FD_LM()

    end = time.time()
    for idx, data in enumerate(train_loader):
        input, target = data

        data_time.update(time.time() - end)

        input = input.float()
        if torch.cuda.is_available():
            input = input.cuda()
            target = target.cuda()

        logit_n = new_model(input)
        with torch.no_grad():
            logit_o = old_model(input)

        loss_cls = criterion_cls(logit_n, target)
        
        if opt.distill == 'kd':
            y_s, y_t = logit_n, logit_o
            kd_loss = reg_loss(y_s, y_t, target)
        elif opt.distill == 'lm': 
            y_s, y_t = logit_n, logit_o
            kd_loss = reg_loss(y_s, y_t, target)
        else:
            raise NotImplementedError(opt.distill)

        loss = opt.gamma * loss_cls + opt.alpha * kd_loss

        #acc1, acc5 = accuracy(logit_s, target, topk=(1, 5))
        acc, nfr = acc_nf(logit_n, logit_o, target, topk=(1, 5))
        acc1, acc5 = acc[0], acc[1]
        nfr1, nfr5 = nfr[0], nfr[1]

        losses.update(loss.item(), input.size(0))
        top1.update(acc1[0], input.size(0))
        top5.update(acc5[0], input.size(0))
        nfr_top1.update(nfr1[0], input.size(0))
        nfr_top5.update(nfr5[0], input.size(0))

        # ===================backward=====================
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        # ===================meters=====================
        batch_time.update(time.time() - end)
        end = time.time()

        # print info
        if idx % opt.print_freq == 0:
            print('Epoch: [{0}][{1}/{2}]\t'
                  'Time {batch_time.val:.3f} ({batch_time.avg:.3f})\t'
                  'Data {data_time.val:.3f} ({data_time.avg:.3f})\t'
                  'Loss {loss.val:.4f} ({loss.avg:.4f})\t'
                  'Acc@1 {top1.val:.3f} ({top1.avg:.3f})\t'
                  'Acc@5 {top5.val:.3f} ({top5.avg:.3f})\t'
                  'NFR@1 {nfr_top1.val:.3f} ({nfr_top1.val:.3f})\t'
                  'NFR@5 {nfr_top5.val:.3f} ({nfr_top5.val:.3f})'.format(
                epoch, idx, len(train_loader), batch_time=batch_time,
                data_time=data_time, loss=losses, top1=top1, top5=top5, nfr_top1=nfr_top1, nfr_top5=nfr_top5))
            sys.stdout.flush()

    print(' * Acc@1 {top1.avg:.3f} Acc@5 {top5.avg:.3f} NFR@1 {nfr_top1.val:.3f} NFR@5 {nfr_top5.val:.3f}'
          .format(top1=top1, top5=top5, nfr_top1=nfr_top1, nfr_top5=nfr_top5))

    return top1.avg, nfr_top1.avg, losses.avg

    
def validate(val_loader, model, criterion, opt, ind=False):
    """validation"""
    batch_time = AverageMeter()
    losses = AverageMeter()
    top1 = AverageMeter()
    top5 = AverageMeter()
    #nfr_top1 = AverageMeter()
    #nfr_top5 = AverageMeter()

    # switch to evaluate mode
    model.eval()

    with torch.no_grad():
        end = time.time()
        for idx, data in enumerate(val_loader):
            if ind == False:
                inputs, targets = data
            else:
                inputs, targets, _, _ = data


            inputs = inputs.float()
            if torch.cuda.is_available():
                inputs = inputs.cuda()
                targets = targets.cuda()

            # compute output
            outputs = model(inputs)
            loss = criterion(outputs, targets)

            # measure accuracy and record loss
            if opt.n_cls <= 5:
                acc1 = accuracy(outputs, targets)
                # acc5 = [torch.Tensor([1.0])]
                top1.update(acc1[0].item(), inputs.size(0))
                top5.update(100.0, inputs.size(0))            
            else:
                acc1, acc5 = accuracy(outputs, targets, topk=(1, 5))
                top1.update(acc1[0], inputs.size(0))
                top5.update(acc5[0], inputs.size(0))

            # measure elapsed time
            batch_time.update(time.time() - end)
            end = time.time()

            if idx % opt.print_freq == 0:
                print('Test: [{0}/{1}]\t'
                      'Time {batch_time.val:.3f} ({batch_time.avg:.3f})\t'
                      'Loss {loss.val:.4f} ({loss.avg:.4f})\t'
                      'Acc@1 {top1.val:.3f} ({top1.avg:.3f})\t'
                      'Acc@5 {top5.val:.3f} ({top5.avg:.3f})\t'.format(
                       idx, len(val_loader), batch_time=batch_time, loss=losses,
                       top1=top1, top5=top5))

        print(' * Acc@1 {top1.avg:.3f} Acc@5 {top5.avg:.3f}'
              .format(top1=top1, top5=top5))

    return top1.avg, top5.avg, losses.avg

def nfr_validate(val_loader, model_s, model_t, criterion, opt):
    """validation"""
    batch_time = AverageMeter()
    losses = AverageMeter()
    nfr_losses = AverageMeter()
    top1 = AverageMeter()
    top5 = AverageMeter()
    nfr_top1 = AverageMeter()
    nfr_top5 = AverageMeter()

    # switch to evaluate mode
    model_s.eval()
    model_t.eval()

    with torch.no_grad():
        end = time.time()
        for idx, (input, target) in enumerate(val_loader):

            input = input.float()
            if torch.cuda.is_available():
                input = input.cuda()
                target = target.cuda()

            # compute output
            output_s = model_s(input)
            output_t = model_t(input)
            loss = criterion(output_s, target)

            softmaxes_t = F.softmax(output_t, dim=1)
            softmaxes_s = F.softmax(output_s, dim=1)
            softmaxes_t = softmaxes_t * F.one_hot(target, opt.n_cls)
            softmaxes_s = softmaxes_s * F.one_hot(target, opt.n_cls)
            confs_t, _ = torch.max(softmaxes_t, 1) 
            confs_s, _ = torch.max(softmaxes_s, 1)
            nfr_loss = -torch.log(confs_s + (1-confs_t) * (1-confs_s)).mean()

            # measure accuracy and record loss
            acc, nfr = acc_nf(output_s, output_t, target, topk=(1, 5))
            acc1, acc5 = acc[0], acc[1]
            nfr1, nfr5 = nfr[0], nfr[1]

            losses.update(loss.item(), input.size(0))
            nfr_losses.update(nfr_loss, input.size(0))
            top1.update(acc1[0], input.size(0))
            top5.update(acc5[0], input.size(0))
            nfr_top1.update(nfr1[0], input.size(0))
            nfr_top5.update(nfr5[0], input.size(0))

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
                       idx, len(val_loader), batch_time=batch_time, loss=losses,
                       top1=top1, top5=top5, nfr_top1=nfr_top1, nfr_top5=nfr_top5))

        print(' * Acc@1 {top1.avg:.3f} Acc@5 {top5.avg:.3f} NFR@1 {nfr_top1.avg:.3f} NFR@5 {nfr_top5.avg:.3f} ce_loss {loss.avg:.3f} nfr_loss {nfr_loss.avg:.3f}'
              .format(top1=top1, top5=top5, nfr_top1=nfr_top1, nfr_top5=nfr_top5, loss=losses, nfr_loss=nfr_losses))

    return top1.avg, top5.avg, nfr_top1.avg, nfr_top5.avg, losses.avg