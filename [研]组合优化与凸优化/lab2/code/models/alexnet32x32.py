import torch.nn as nn
import torch.nn.functional as func
import torch.nn.functional as F



class alexnet32x32(nn.Module):
    def __init__(self, num_classes):
        super(alexnet32x32, self).__init__()
        self.features=nn.Sequential(
            nn.Conv2d(3, 64, kernel_size=3, stride=2, padding=1), 
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
            
            nn.Conv2d(64, 192, kernel_size=5, padding=2),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(kernel_size=3, stride=2),
        
            nn.Conv2d(192, 384, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
        
            nn.Conv2d(384,256, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),
        
            nn.Conv2d(256, 256, kernel_size=3, padding=1),
            nn.ReLU(inplace=True),  
            nn.MaxPool2d(kernel_size=3, stride=2),)
        self.classifier=nn.Sequential(
            nn.Linear(256*1*1, 4096),
            nn.ReLU(inplace=True),
            nn.Linear(4096, 4096),
            nn.ReLU(inplace=True),
            nn.Linear(4096, num_classes),)

    def forward(self, x, drop=0.0):
        x = self.features(x)
        x = x.view(x.size(0), 256*1*1)
        if drop > 0:
            x = F.dropout(x, drop, training=True)
        x = self.classifier(x)
        return x
        #return F.log_softmax(inputs, dim=3)
