from __future__ import print_function

import os
import numpy as np
import pickle
import torch
from torch.utils.data import DataLoader
from torch.utils.data import Subset
from torchvision import datasets, transforms
from PIL import Image
from typing import Any, Callable, Optional, Tuple

def get_data_folder(category='c'):
    if category == 'b':
        data_folder = './data/image_CLEF/b/'
    elif category == 'c':
        data_folder = './data/image_CLEF/c/'
    elif category == 'i':
        data_folder = './data/image_CLEF/i/'
    elif category == 'p':
        data_folder = './data/image_CLEF/p/'
    else:
        raise NotImplementedError('No ImageCLEF')
    return data_folder

class ImageCLEF(torch.utils.data.Dataset):
    def __init__(self, datatxt, transform=None):
        super(ImageCLEF, self).__init__()
        fh = open(datatxt, 'r')
        imgs = []
        for line in fh:
            line = line.strip('\n')
            words = line.split(' ')
            imgs.append((words[0], int(words[1])))
        
        self.imgs = imgs
        self.transform = transform
    
    def __getitem__(self, index):
        fn, label = self.imgs[index]
        img = Image.open(fn).convert('RGB')

        if self.transform is not None:
            img = self.transform(img)
        
        return img, label
    
    def __len__(self):
        return len(self.imgs)

def get_imageclef_dataloaders(category='c', batch_size=128, num_workers=8, size=1.0):

    c = category.split('+')

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
        # transforms.Resize([224,224]),
        transforms.ToTensor(),
        normalize,
    ])

    if len(c) == 1:
        data_folder = get_data_folder(category)
        train_path = os.path.join(data_folder, 'train.txt')
        test_path = os.path.join(data_folder, 'val.txt')
        if not os.path.exists(train_path) or not os.path.exists(test_path):
            save_txt(category)
        train_dataset = ImageCLEF(train_path, train_transform)        
        test_dataset = ImageCLEF(test_path, test_transform)
    else:
        train_data_list = []
        test_data_list = []
        for f in c:
            data_folder = get_data_folder(f)
            train_path = os.path.join(data_folder, 'train.txt')
            test_path = os.path.join(data_folder, 'val.txt')
            if not os.path.exists(train_path) or not os.path.exists(test_path):
                save_txt(f)
            train_dataset = ImageCLEF(train_path, train_transform)        
            test_dataset = ImageCLEF(test_path, test_transform)
            train_data_list.append(train_dataset)
            test_data_list.append(test_dataset)
        train_dataset = torch.utils.data.ConcatDataset(train_data_list)
        test_dataset = torch.utils.data.ConcatDataset(test_data_list)

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


    n_data = len(test_dataset)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(0.5 * n_data))
    val_idx = idx[:split]
    test_val_set = Subset(test_dataset, val_idx)
    test_idx = idx[split:]
    test_set = Subset(test_dataset, test_idx)

    test_val_loader = torch.utils.data.DataLoader(dataset=test_val_set, batch_size=batch_size, shuffle=False, num_workers=int(num_workers))
    test_loader = torch.utils.data.DataLoader(dataset=test_set, batch_size=batch_size, shuffle=False, num_workers=int(num_workers))

    return train_loader, train_val_loader, test_val_loader, test_loader

def save_txt(category='c'):
    path = get_data_folder(category)
    classes = [i for i in os.listdir(path)]
    files = os.listdir(path)
    train = open(os.path.join(path, 'train.txt'), 'w')
    val = open(os.path.join(path, 'val.txt'), 'w')
    for i in classes:
        s = 1
        for imgname in os.listdir(os.path.join(path, str(i))):  
            if not s % 4 == 0:
                name = os.path.join(path, str(i)) + '/' + imgname + ' ' + str(i) + '\n'
                train.write(name)
            else:
                name = os.path.join(path, str(i)) + '/' + imgname + ' ' + str(i) + '\n'
                val.write(name)
            s += 1
    val.close()
    train.close()

if __name__ == '__main__':
    save_txt('c')
    save_txt('p')
    
