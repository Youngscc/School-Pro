from __future__ import print_function

import torch
import torch.nn as nn
import torch.nn.functional as F

class FD_KL(nn.Module):
    """ Input: after softmax """
    def __init__(self, T=100, alpha=1, beta=5, size_average=True):
        super(FD_KL, self).__init__()
        self.T = T
        self.alpha = alpha
        self.beta = beta
        self.size_average = size_average
    
    def forward(self, y_new, y_old, label):
        """ label_old: 1: y_old==label, 0: y_old!=label """
        # correct = self.alpha + self.beta
        # wrong = self.alpha
        pred_old = y_old.argmax(dim=1)
        miscls = pred_old == label
        
        loss = 0
        if torch.cuda.is_available():
            miscls = miscls.cuda()
        weight = miscls * self.beta + self.alpha
        
        p_new = F.log_softmax(y_new/self.T, dim=1)
        p_old = F.softmax(y_old/self.T, dim=1)
        loss = F.kl_div(p_new, p_old, size_average=False) * (self.T**2)
        loss = loss * weight

        if self.size_average:
            return loss.mean()
        else:
            return loss.sum()


# class FD_KL2(nn.Module):
#     """ Input: after softmax """
#     def __init__(self, T=100, alpha=1, beta=5):
#         super(FD_KL2, self).__init__()
#         self.T = T
#         self.alpha = alpha
#         self.beta = beta
    
#     def forward(self, y_new, y_old, y_old2, miscls, label):
#         """ label_old: 1: y_old==label, 0: y_old!=label """
#         correct = self.alpha + self.beta
#         wrong = self.alpha

#         loss = 0
#         length = int(label.shape[0])
#         #label_old = self.compare(y_old, label)
#         if torch.cuda.is_available():
#             miscls = miscls.cuda()
#         weight = miscls * self.beta + self.alpha
#         '''
#         p_new = F.log_softmax(y_new/self.T, dim=1)
#         p_old = F.softmax(y_old/self.T, dim=1)
#         loss = F.kl_div(p_new, p_old, size_average=False) * (self.T**2)
#         loss = loss * weight / length
#         '''
#         avg_y_old = (y_old + y_old2)/2
#         #print(y_old[0], y_old2[0], avg_y_old[0])

#         for i in range(length):
#             # p_new = F.log_softmax(y_new[i]/self.T, dim=0)
#             p_new = F.log_softmax(y_new[i], dim=0)          # for testing
#             p_old = F.softmax(avg_y_old[i]/self.T, dim=0)
#             loss += weight[i] * F.kl_div(p_new, p_old, size_average=False) * (self.T**2)
#         loss /= length
        
#         return loss