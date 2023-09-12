from __future__ import absolute_import

import torch.nn as nn
import torch.nn.functional as F
import math
import torch
from torch.autograd import Variable

class Net(nn.Module):

    def __init__(self, num_classes):
        super(Net, self).__init__()
        # vocab_size = 36490
        # Fully connected layer
        # self.embedding = nn.Embedding(vocab_size, 256)
        # self.lstm = nn.LSTM(input_size=256, hidden_size=128
        self.fc1 = nn.Linear(2103, 256)
        self.fc2 = nn.Linear(256, 128)
        self.fc3 = nn.Linear(128, num_classes)

    def forward(self, x):
        # x = self.lstm(x)
        # x = x[:, x.size(1)-1,:].squeeze(1)
        # x = x.view(x.size()[0],-1)
        # x = self.embeddings(x)
        # lstm_out, self.hidden = self.lstm(x, self.hidden)
        x = nn.functional.relu(self.fc1(x))
        x = nn.functional.relu(self.fc2(x))
        x = self.fc3(x)

        return x

