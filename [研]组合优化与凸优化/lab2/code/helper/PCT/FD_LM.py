from __future__ import print_function

import torch
import torch.nn as nn

class FD_LM(nn.Module):
    """ Input: logits before softmax """
    def __init__(self, alpha=1, beta=5, size_average=True):
        super(FD_LM, self).__init__()
        self.alpha = alpha
        self.beta = beta
        self.size_average = size_average
    
    def forward(self, y_new, y_old, label):
        """ label_old: 1: y_old==label, 0: y_old!=label """
        # correct = self.alpha + self.beta
        # wrong = self.alpha
        
        pred_old = y_old.argmax(dim=1)
        miscls = pred_old == label

        if torch.cuda.is_available():
            miscls = miscls.cuda()
        weight = miscls * self.beta + self.alpha
        MSELoss = nn.MSELoss(size_average=False)
        loss = weight * MSELoss(y_new, y_old)

        if self.size_average:
            return loss.mean()
        else:
            return loss.sum()


# class FD_LM2(nn.Module):
#     """ Input: logits before softmax """
#     def __init__(self, alpha=1, beta=5, weight_a=0.5, weight_b=0.5, size_average=True):
#         super(FD_LM2, self).__init__()
#         self.alpha = alpha
#         self.beta = beta
#         self.weight_a = weight_a
#         self.weight_b = weight_b
#         self.size_average = size_average
    
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
#         MSELoss = nn.MSELoss(reduce=True, size_average=False)
#         #loss = weight * MSELoss(p_new, p_old) / length
        
#         '''
#         for i in range(length):
#             p_new = y_new[i]
#             p_old = y_old[i]
#             loss += weight[i] * MSELoss(p_new, p_old)
#         loss /= length
#         '''
#         y_new = F.softmax(y_new, dim=0)
#         y_old = F.softmax(y_old, dim=0)
#         y_old2 = F.softmax(y_old2, dim=0)

#         avg_y_old = y_old * self.weight_a + y_old2 * self.weight_b
#         ensemble_y_old = torch.maximum(avg_y_old, y_old)

#         loss = weight * MSELoss(y_new, ensemble_y_old)
#         if self.size_average:
#             return loss.mean()
#         else:
#             return loss.sum()
