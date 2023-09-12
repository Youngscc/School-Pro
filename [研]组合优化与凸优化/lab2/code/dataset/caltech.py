import os
import numpy as np
import pickle
import torch
from torch.utils.data import DataLoader, Subset
from torchvision import datasets, transforms
from torch.utils.data.sampler import SubsetRandomSampler
from PIL import Image
from typing import Any, Callable, Optional, Tuple

def get_data_folder(version):
    if version == '101':
        return '/data/share/Caltech101'
    elif version == '256':
        return '/data/share/Caltech256'
    else:
        raise NotImplementedError('No Caltech')

def get_caltech_dataloaders(version='101', batch_size=64, num_workers=16, size=1.0):
    data_folder = get_data_folder(version)

    normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                    std=[0.229, 0.224, 0.225])
    train_transform = transforms.Compose([
        transforms.RandomResizedCrop(224),
        transforms.RandomHorizontalFlip(),
        transforms.ToTensor(),
        normalize,
    ])
    test_transform = transforms.Compose([
        transforms.Resize(256),
        transforms.CenterCrop(224),
        transforms.ToTensor(),
        normalize,
    ]) 
    
    if version == '101':
        train_dataset = datasets.Caltech101(root=data_folder,
                                    download=True,
                                    train=True,
                                    transform=train_transform)
    elif version == '256':
        train_dataset = datasets.Caltech256(root=data_folder,
                                    download=True,
                                    train=True,
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
                              shuffle=False,
                              num_workers=num_workers)


    if version == '101':
        test_dataset = datasets.Caltech101(root=data_folder,
                                    download=True,
                                    train=True,
                                    transform=train_transform)
    elif version == '256':
        test_dataset = datasets.Caltech256(root=data_folder,
                                    download=True,
                                    train=True,
                                    transform=train_transform)

    # further spilt as val data
    n_data = len(test_dataset)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(0.5 * n_data))
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