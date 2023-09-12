import torch
import torch.nn as nn
import torch.nn.functional as F


class mnistlenet(nn.Module):
    def __init__(self, num_classes):
        super(mnistlenet, self).__init__()
        self.conv1 = nn.Sequential(     
            nn.Conv2d(1, 6, 5, 1, 2),
            nn.ReLU(),      
            nn.MaxPool2d(kernel_size=2, stride=2),
        )
        self.conv2 = nn.Sequential(
            nn.Conv2d(6, 16, 5),
            nn.ReLU(),     
            nn.MaxPool2d(2, 2) 
        )
        self.fc1 = nn.Sequential(
            nn.Linear(16 * 5 * 5, 120),
            nn.ReLU()
        )
        self.fc2 = nn.Sequential(
            nn.Linear(120, 84),
            nn.ReLU()
        )
        self.fc3 = nn.Linear(84, num_classes)

    def forward(self, x, drop=0.0):
        x = self.conv1(x)
        x = self.conv2(x)
        x = x.view(x.size()[0], -1)
        x = self.fc1(x)
        x = self.fc2(x)
        if drop > 0:
            x = F.dropout(x, drop, training=True)
        x = self.fc3(x)
        return x
