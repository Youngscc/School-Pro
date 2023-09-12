from __future__ import print_function

import torch.nn as nn
import torch
import torch.nn.functional as F
import torch.optim as optim
import numpy as np
from sklearn.mixture import GaussianMixture
from sklearn.cluster import KMeans

def temperature_scale(logits, T):

    # Expand temperature to match the size of logits
    temperature = T.unsqueeze(1).expand(logits.size(0), logits.size(1))
    return logits / temperature
    
class ensemble_model(nn.Module):

    def __init__(self, model1, model2, opt):
        super(ensemble_model, self).__init__()
        self.model1 = model1
        self.model2 = model2
        self.ensemble = opt.ensemble
        if opt.ensemble == 'weight':
            self.k = opt.weight
    
    # it should note that the output of ensemble model is the softmax value
    def forward(self, x):
        output1 = self.model1(x)
        output2 = self.model2(x)

        # old_confs = F.softmax(output1, dim=-1)
        # new_confs = F.softmax(output2, dim=-1)
        # p, _ = torch.max(old_confs, 1)
        # q, _ = torch.max(new_confs, 1)

        if self.ensemble == 'average':
            old_confs = F.softmax(output1, dim=-1)
            new_confs = F.softmax(output2, dim=-1)
            output = (new_confs + old_confs) / 2
        elif self.ensemble == 'maximum':
            old_confs = F.softmax(output1, dim=-1)
            new_confs = F.softmax(output2, dim=-1)
            p, _ = torch.max(old_confs, 1)
            q, _ = torch.max(new_confs, 1)
            output = output2.clone()
            ind = p > q
            output[ind] = output1[ind]
        elif self.ensemble == 'deepgini':
            old_confs = F.softmax(output1, dim=-1)
            new_confs = F.softmax(output2, dim=-1)
            p = 1 - old_confs.square().sum(dim=-1)
            q = 1 - new_confs.square().sum(dim=-1)
            print(p.shape, q.shape)
            output = output2.clone()
            ind = p > q
            output[ind] = output1[ind]
        elif self.ensemble == 'weight':
            old_confs = F.softmax(output1, dim=-1)
            new_confs = F.softmax(output2, dim=-1)
            output = new_confs * self.k + old_confs * (1-self.k)
        elif self.ensemble == 'scaling' or self.ensemble == 'scaling_unlabel':
            if torch.cuda.is_available():
                self.k = self.k.cuda()
            old_confs = F.softmax(temperature_scale(output1, self.T1), dim=-1)
            new_confs = F.softmax(temperature_scale(output2, self.T2), dim=-1)
            output = old_confs * self.k + new_confs * (1-self.k)
        elif self.ensemble == 'dropout':
            loops = 10
            # old_confs = F.softmax(output1, dim=-1)
            # new_confs = F.softmax(output2, dim=-1)
            pred1 = []
            pred2 = []
            for _ in range(loops):
                pred1.append(F.softmax(self.model1(x, drop=0.2), dim=-1))
                pred2.append(F.softmax(self.model2(x, drop=0.2), dim=-1))
            var_pred1 = torch.zeros(output1.shape).cuda()
            var_pred2 = torch.zeros(output2.shape).cuda()
            mean_pred1 = torch.zeros(output1.shape).cuda()
            mean_pred2 = torch.zeros(output2.shape).cuda()
            for _ in range(loops):
                mean_pred1 += pred1[_]
                mean_pred2 += pred2[_]
                var_pred1 += pred1[_].square()
                var_pred2 += pred2[_].square()
            var_pred1 = (var_pred1/loops) - (mean_pred1/loops).square()
            var_pred2 = (var_pred2/loops) - (mean_pred2/loops).square()
            weight1 = var_pred1.sum(dim=-1)
            weight2 = var_pred2.sum(dim=-1)
            # clip for numerical stability
            weight1 = torch.clamp(var_pred1.sum(dim=-1), min=1e-3, max=1-1e-3) 
            weight2 = torch.clamp(var_pred2.sum(dim=-1), min=1e-3, max=1-1e-3)  
            # add a priori with weight1=0.0, weight2=1.0.
            w1 = torch.unsqueeze((weight2 / (2*(weight1+weight2))+0.0), -1)
            w2 = torch.unsqueeze((weight1 / (2*(weight1+weight2))+0.5), -1)
            output = torch.mul(mean_pred1 / loops, w1) + torch.mul(mean_pred2 / loops, w2)
        elif self.ensemble == 'perturb':
            loops = 10
            # old_confs = F.softmax(output1, dim=-1)
            # new_confs = F.softmax(output2, dim=-1)
            pred1 = []
            pred2 = []
            for _ in range(loops):
                pert = torch.randn(x.shape).cuda()
                pred1.append(F.softmax(self.model1(x + 0.01 * pert), dim=-1))
                # pert = torch.randn(x.shape).cuda()
                pred2.append(F.softmax(self.model2(x + 0.01 * pert), dim=-1))
            var_pred1 = torch.zeros(output1.shape).cuda()
            var_pred2 = torch.zeros(output2.shape).cuda()
            mean_pred1 = torch.zeros(output1.shape).cuda()
            mean_pred2 = torch.zeros(output2.shape).cuda()
            for _ in range(loops):
                mean_pred1 += pred1[_]
                mean_pred2 += pred2[_]
                var_pred1 += pred1[_].square()
                var_pred2 += pred2[_].square()
            var_pred1 = (var_pred1/loops) - (mean_pred1/loops).square()
            var_pred2 = (var_pred2/loops) - (mean_pred2/loops).square()
            # clip for numerical stability
            weight1 = torch.clamp(var_pred1.sum(dim=-1), min=1e-3, max=1-1e-3) 
            weight2 = torch.clamp(var_pred2.sum(dim=-1), min=1e-3, max=1-1e-3)  
            # set priori weight as w1=0.0, w2=1.0
            w1 = torch.unsqueeze((weight2 / (2*(weight1+weight2))+0.0), -1)
            w2 = torch.unsqueeze((weight1 / (2*(weight1+weight2))+0.5), -1)
            output = torch.mul(mean_pred1 / loops, w1) + torch.mul(mean_pred2 / loops, w2)
        else:
            raise NotImplementedError(opt.ensemble)
        return output

    # using labeled data to compute the optimal weight
    def scaling(self, data_loader, opt):
        old_model = self.model1
        new_model = self.model2
        old_model.cuda()
        new_model.cuda()
        old_logit_list = []
        new_logit_list = []
        labels_list = []
        with torch.no_grad():
            for inputs, label in data_loader:
                inputs = inputs.cuda()
                old_logit = old_model(inputs)
                new_logit = new_model(inputs)
                old_logit_list.append(old_logit)
                new_logit_list.append(new_logit)
                labels_list.append(label)
            old_logit_list = torch.cat(old_logit_list).detach()
            new_logit_list = torch.cat(new_logit_list).detach()
            labels = torch.cat(labels_list).cuda()

        # p_ = F.softmax(old_logit_list, dim=-1)
        T1 = nn.Parameter(torch.ones(1).cuda())
        p_ = F.softmax(temperature_scale(old_logit_list, T1), dim=-1)
        q_ = F.softmax(new_logit_list, dim=-1)
        p, old_pred  = torch.max(p_, 1)
        q, new_pred  = torch.max(q_, 1)

        def eval(k):
            output = p_ * k + q_ * (1-k)
            conf, pred = torch.max(output, 1)
            acc = (pred == labels).float().mean()
            nfr = torch.logical_and(old_pred == labels, pred != labels).float().mean()
            return acc, nfr

        acc = 0
        interval = np.arange(0.0, 1.001, 0.001)
        acc_low = (new_pred == labels).float().mean()
        best_nfr = 1.0 
        best_acc = 0.0
        best_k = 0.0
        acc_list = []
        nfr_list = []
        for i in range(len(interval)):
            k = interval[i]
            acc, nfr = eval(k)
            acc_list.append(acc.item())
            nfr_list.append(nfr.item())
            np.savetxt('curve.csv', [acc_list, nfr_list])
            if acc >= acc_low and nfr < best_nfr:
                best_k = k
                best_nfr = nfr
                best_acc = acc        
        self.k = torch.Tensor([best_k])
        T1 = nn.Parameter(torch.ones(1).cuda() * 1.0)
        T2 = nn.Parameter(torch.ones(1).cuda() * 1.0)
        self.T1 = T1
        self.T2 = T2
        print(self.k)
        return self.T1, self.T2, self.k

    # the temperature scaling method
    def scaling_unlabel(self, data_loader, opt):
        old_model = self.model1
        new_model = self.model2
        old_model.cuda()
        new_model.cuda()
        old_logit_list = []
        new_logit_list = []
        with torch.no_grad():
            for inputs, label in data_loader:
                inputs = inputs.cuda()
                old_logit = old_model(inputs)
                new_logit = new_model(inputs)
                old_logit_list.append(old_logit)
                new_logit_list.append(new_logit)
            old_logit_list = torch.cat(old_logit_list).detach()
            new_logit_list = torch.cat(new_logit_list).detach()

        def solveT(old_logit_list, new_logit_list, init_T = 1.0, reg=0.0):
            T1 = nn.Parameter(torch.ones(1).cuda() * init_T)
            optimizer = optim.LBFGS([T1], lr=1)
            mse_loss = nn.MSELoss()
            # nll_criterion = nn.CrossEntropyLoss().cuda()
            def eval():
                optimizer.zero_grad()
                p = F.softmax(temperature_scale(old_logit_list, T1), dim=-1)
                q = F.softmax(new_logit_list, dim=-1)
                # loss = F.kl_div(p.log(), q, reduction='batchmean') + F.kl_div(q.log(), p, reduction='batchmean')
                loss = mse_loss(p, q) + reg * T1.square()
                loss.backward()
                return loss
            optimizer.step(eval)
            return T1
        
        init_list = [1.0, 2.0, 3.0]
        best_loss = 1e6
        for T in init_list:
            mse_loss = nn.MSELoss()
            T1 = solveT(old_logit_list, new_logit_list, init_T = T, reg=5e-4)
            with torch.no_grad():
                p = F.softmax(temperature_scale(old_logit_list, T1), dim=-1)
                q = F.softmax(new_logit_list, dim=-1)
                # loss = F.kl_div(p.log(), q, reduction='batchmean') + F.kl_div(q.log(), p, reduction='batchmean')
                loss = mse_loss(p, q) 
            if loss.item() < best_loss and T1.item() > 0:
                best_T = T1
                best_loss = loss.item()
            print('T: {}, loss: {}'.format(T1.item(), loss.item()))
        # if bestT1 is too large add reg
        if best_T < 0.8:
            init_list = [1.0, 2.0, 3.0]
            best_loss = 1e6
            for T in init_list:
                mse_loss = nn.MSELoss()
                T1 = solveT(old_logit_list, new_logit_list, init_T = T, reg=0.0)
                with torch.no_grad():
                    p = F.softmax(temperature_scale(old_logit_list, T1), dim=-1)
                    q = F.softmax(new_logit_list, dim=-1)
                    # loss = F.kl_div(p.log(), q, reduction='batchmean') + F.kl_div(q.log(), p, reduction='batchmean')
                    loss = mse_loss(p, q) 
                if loss.item() < best_loss and T1.item() > 0:
                    best_T = T1
                    best_loss = loss.item()
                print('T: {}, loss: {}'.format(T1.item(), loss.item()))
        print('set T by {}'.format(best_T.item()))
        self.T1 = best_T
        self.T2 = nn.Parameter(torch.ones(1).cuda())
        self.k = torch.Tensor([0.5])



    







