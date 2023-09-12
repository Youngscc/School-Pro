from locale import normalize
import torch
import os
import cv2

import numpy as np
import torchvision.transforms as transforms
import lmdb
import msgpack
from torch.utils.data import Dataset, DataLoader, Subset
from PIL import Image

def get_data_folder():
    return '/data/share/ImageNet'

class lmdbDataset(Dataset):

    def __init__(self, location, transform):
        self.transform = transform
        self.env = lmdb.open(location,subdir=False,max_readers=1,readonly=True,lock=False,readahead=False,meminit=False)
        self.txn = self.env.begin(write=False)
        self.length = self.txn.stat()['entries']

    def __len__(self):
        return self.length - 1
    
    def __getitem__(self, index):
        new_index = str(index).encode()
        data = self.txn.get(new_index)
        now_data = msgpack.loads(data, raw=False)
        data_img = now_data[0]
        label = now_data[1]
        now_arr = np.frombuffer(data_img[b'data'], dtype=np.uint8)
        image_content = cv2.imdecode(now_arr, cv2.IMREAD_COLOR)
        image_content = cv2.cvtColor(image_content,cv2.COLOR_BGR2RGB)
        image_content = Image.fromarray(image_content)
        image_content = self.transform(image_content)
        return image_content, label

def get_imagenet_dataloaders(batch_size=64, num_workers=16):
    data_folder = get_data_folder()

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
    
    # train_folder = os.path.join(data_folder, 'ILSVRC-train.lmdb')
    test_folder = os.path.join(data_folder, 'ILSVRC-val.lmdb')

    # train_set = lmdbDataset(train_folder, train_transform)
    # train_loader = DataLoader(train_set,
                            #   batch_size=batch_size,
                            #   shuffle=True,
                            #   num_workers=num_workers,
                            #   )
    
    test_set = lmdbDataset(test_folder, test_transform)
    
    n_data = len(test_set)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(0.5 * n_data))
    val_idx = idx[:split]
    val_set = Subset(test_set, val_idx)
    test_idx = idx[split:]
    test_set = Subset(test_set, test_idx)

    test_val_loader = DataLoader(val_set,
                            batch_size=batch_size,
                            shuffle=False,
                            num_workers=num_workers,
                            )
    test_loader = DataLoader(test_set,
                            batch_size=batch_size,
                            shuffle=False,
                            num_workers=num_workers,
                            )
    return None, None, test_val_loader, test_loader


def get_imagenet_v_dataloaders(batch_size=64, num_workers=16):
    data_folder = get_data_folder()

    normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                    std=[0.229, 0.224, 0.225])

    train_transform = transforms.Compose([
        transforms.RandomResizedCrop(299),
        transforms.RandomHorizontalFlip(),
        transforms.ToTensor(),
        normalize,
    ])
    test_transform = transforms.Compose([
        transforms.Resize((299,299)),
        transforms.ToTensor(),
        normalize,
    ])

    # train_folder = os.path.join(data_folder, 'ILSVRC-train.lmdb')
    test_folder = os.path.join(data_folder, 'ILSVRC-val.lmdb')

    # train_set = lmdbDataset(train_folder, train_transform)
    # train_loader = DataLoader(train_set,
                            #   batch_size=batch_size,
                            #   shuffle=True,
                            #   num_workers=num_workers,
                            #   )
    
    test_set = lmdbDataset(test_folder, test_transform)
    
    n_data = len(test_set)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(0.5 * n_data))
    val_idx = idx[:split]
    val_set = Subset(test_set, val_idx)
    test_idx = idx[split:]
    test_set = Subset(test_set, test_idx)

    test_val_loader = DataLoader(val_set,
                            batch_size=batch_size,
                            shuffle=False,
                            num_workers=num_workers,
                            )
    test_loader = DataLoader(test_set,
                            batch_size=batch_size,
                            shuffle=False,
                            num_workers=num_workers,
                            )
    return None, None, test_val_loader, test_loader