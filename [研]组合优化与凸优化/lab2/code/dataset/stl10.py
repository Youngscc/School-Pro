from __future__ import print_function

import os
import numpy as np
import pickle
import torch
from torch.utils.data import DataLoader, Subset
from torchvision import datasets, transforms
from torch.utils.data.sampler import SubsetRandomSampler
from PIL import Image
from typing import Any, Callable, Optional, Tuple

"""
mean = {
    'cifar10': (0.5071, 0.4867, 0.4408),
}

std = {
    'cifar10': (0.2675, 0.2565, 0.2761),
}
"""


def get_data_folder():
    data_folder = './data/stl10/'
    
    if not os.path.isdir(data_folder):
        os.makedirs(data_folder)

    return data_folder


def get_stl10_dataloaders(batch_size=128, num_workers=8, is_instance=False, size=1.0):
    """
    cifar 10
    """
    data_folder = get_data_folder()

    train_transform = transforms.Compose([
        transforms.Resize([32, 32]),
        transforms.RandomCrop(32, padding=4),
        transforms.RandomHorizontalFlip(),
        transforms.ToTensor(),
        transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2021)),
    ])
    test_transform = transforms.Compose([
        transforms.Resize([32, 32]),
        transforms.ToTensor(),
        transforms.Normalize((0.4914, 0.4822, 0.4465), (0.2023, 0.1994, 0.2021)),
    ])

    train_dataset = datasets.STL10(root=data_folder,
                                    download=True,
                                    split='train',
                                    transform=train_transform)
    
    # setting training data with size
    n_data = len(train_dataset)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(size * n_data))
    val_split = int(np.floor(split * 0.8))
    train_idx = idx[:val_split]
    train_val_idx = idx[val_split:split]
    train_set = Subset(train_dataset, train_idx)
    train_val_set = Subset(train_dataset, train_val_idx)


    train_loader = DataLoader(train_set,
                              batch_size=batch_size,
                              shuffle=True,
                              num_workers=num_workers)

    train_val_loader = DataLoader(train_val_set,
                              batch_size=batch_size,
                              shuffle=True,
                              num_workers=num_workers)


    test_dataset = datasets.STL10(root=data_folder,
                                 download=True,
                                 split='test',
                                 transform=test_transform)
    # further spilt as val data
    n_data = len(test_dataset)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(0.02 * n_data))
    val_idx = idx[:split]
    test_val_set = Subset(test_dataset, val_idx)
    test_idx = idx[split:]
    test_set = Subset(test_dataset, test_idx)

    test_val_loader = DataLoader(test_val_set,
                             batch_size=batch_size,
                             shuffle=False,
                             num_workers=num_workers)


    test_loader = DataLoader(test_set,
                             batch_size=batch_size,
                             shuffle=False,
                             num_workers=num_workers)


    return train_loader, train_val_loader, test_val_loader, test_loader
