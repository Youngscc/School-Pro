from __future__ import print_function

import torch.nn as nn
import torch
import torch.nn.functional as F
import torch.optim as optim
import numpy as np
    
class bayesian_combiner(nn.Module):

    def __init__(self, model, opt):
        # inf_data: inference data
        super(bayesian_combiner, self).__init__()
        self.models = model
        self.combine = opt.combine
        if self.combine == 'CostRatio':
            self.c = opt.c
        # self.prior = torch.ones(inf_data.shape[0], opt.n_cls) * (1/opt.n_cls)

    def compute_pi(self, data_loader, opt):
        self.pi_list = []
        for model in self.models:
            pi = torch.zeros(opt.n_cls, opt.n_cls)
            pred_list = []
            label_list = []
            with torch.no_grad():
                for inputs, label in data_loader:
                    inputs = inputs.cuda()
                    pred = model(inputs)
                    _, pred = torch.max(pred, 1)
                    pred_list.append(pred)
                    label_list.append(label)
            labels = torch.cat(label_list).cpu().detach()
            preds = torch.cat(pred_list).cpu().detach()
            for k in range(opt.n_cls):
                for i in range(opt.n_cls):
                    pi[i,k] = ((preds == i) * (labels == k)).sum() / (labels == k).sum() # p(pred = i | label = k)
            self.pi_list.append(pi)
            

    def compute_posterior(self, data_loader, opt):
        for i, model in enumerate(self.models):                
            pred_list = []
            with torch.no_grad():
                for inputs, _ in data_loader:
                    inputs = inputs.cuda()
                    pred = model(inputs)
                    _, pred = torch.max(pred, 1)
                    pred_list.append(pred)
            preds = torch.cat(pred_list).cpu().detach()
            if i == 0:
                self.preds = preds.clone()
                self.prior = torch.ones(preds.shape[0], opt.n_cls) * (1/opt.n_cls)
                posterior = torch.zeros(preds.shape[0], opt.n_cls)
            pi = self.pi_list[i]
            for y in range(preds.shape[0]):
                norm = (pi[preds[y], :] * self.prior[y, :]).sum()
                posterior[y, :] =  pi[preds[y], :] * self.prior[y, :] / norm 
            if self.combine == 'Replace':
                self.preds = preds
            if self.combine == 'MaxBelief':
                _, preds = torch.max(posterior, 1)
                self.preds = preds
            elif self.combine == 'MBME':
                pre_entropy = - (self.prior * torch.log(self.prior + 1e-5)).sum(dim=1)
                post_entropy = - (posterior * torch.log(posterior + 1e-5)).sum(dim=1)
                _, preds = torch.max(posterior, 1)
                idx = pre_entropy > post_entropy
                self.preds[idx] = preds[idx]
            elif self.combine == 'CostRatio':
                tmp = F.one_hot(self.preds, opt.n_cls)
                p_nf = (posterior * tmp).sum(dim=1)
                p_pf, preds = torch.max(posterior, 1)
                idx = (p_pf/p_nf) > self.c
                self.preds[idx] = preds[idx]
            self.prior = posterior.clone()
        
        return self.preds




                


