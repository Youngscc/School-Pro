from __future__ import print_function
from cmath import polar

import os
import numpy as np
import string
import pickle
import random
import re
import time
import torch
import tensorflow_transform as tft
import tensorflow as tf
from torchtext.legacy import data
from torch.utils.data import DataLoader
from torch.utils.data import Subset
from torchvision import datasets, transforms
from tensorflow.keras.preprocessing import text, sequence
from torch.utils.data import TensorDataset


def get_data_folder(version=1.0):
    
    if version == 1.0:
        data_folder = './data/polarity_v1'
    elif version == 2.0:
        data_folder = './data/polarity_v2'
    else:
        raise NotImplementedError('Polarity dataset version not supported')
    
    return data_folder

class Polarity(torch.utils.data.Dataset):
    def __init__(self, datatxt, transform=None):
        super(Polarity, self).__init__()
        data_integration(datatxt+'/tokens/pos', datatxt+'/tokens/neg')
        x_text, y = load_data_and_labels(datatxt+'/tokens/pos/pos.txt', datatxt+'/tokens/neg/neg.txt')
        # max_document_length = max([len(x.split(' ')) for x in x_text])
        max_document_length = 2103
        tokenizer = tf.keras.preprocessing.text.Tokenizer(oov_token="<UNK>")
        tokenizer.fit_on_texts(x_text)
        # self.vocab_size = len(tokenizer.word_index) + 1
        x = tokenizer.texts_to_sequences(x_text)
        x = tf.keras.preprocessing.sequence.pad_sequences(x, maxlen=max_document_length, padding='post', truncating='post')
        x = torch.Tensor(x).type(torch.LongTensor)
        y = torch.Tensor(y).view(-1).to(torch.int64)  
        self.data = TensorDataset(x, y)
    
    # def __getitem__(self, index):
        # fn = self.data[index].reshape(1, -1)
        # label = self.label[index]
        # if self.transform is not None:
            # fn = self.transform(fn)
        # return fn, label
    
    # def __len__(self):
        # return self.data.shape[0]
    

def get_polarity_dataloaders(dataset='polarity', version=1.0, batch_size=32, num_workers=4, size=1.0):
    
    data_folder = get_data_folder(version)

    dataset = Polarity(data_folder).data
    n_data = len(dataset)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(0.6 * n_data))
    train_dataset = Subset(dataset, idx[0:split])
    test_dataset = Subset(dataset, idx[split:])

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

    n_data = len(test_dataset)
    idx = np.arange(n_data)
    np.random.shuffle(idx)
    split = int(np.floor(0.5 * n_data))
    val_idx = idx[:split]
    val_set = Subset(test_dataset, val_idx)
    test_idx = idx[split:]
    test_set = Subset(test_dataset, test_idx)

    test_val_loader = torch.utils.data.DataLoader(dataset=val_set, batch_size=batch_size, shuffle=False, num_workers=int(num_workers))
    test_loader = torch.utils.data.DataLoader(dataset=test_set, batch_size=batch_size, shuffle=False, num_workers=int(num_workers))

    return train_loader, train_val_loader, test_val_loader, test_loader

def clean_str(string):

    """
    Tokenization/string cleaning for all datasets except for SST.
    Original taken from https://github.com/yoonkim/CNN_sentence/blob/master/process_data.py
    """

    string = re.sub(r"[^A-Za-z0-9(),!?\'\`\,\']", " ", string)
    string = re.sub(r"\'s", " \'s", string)
    string = re.sub(r"\'ve", " \'ve", string)
    string = re.sub(r"n\'t", " n\'t", string)
    string = re.sub(r"\'re", " \'re", string)
    string = re.sub(r"\'d", " \'d", string)
    string = re.sub(r"\'ll", " \'ll", string)
    string = re.sub(r",", " , ", string)
    string = re.sub(r"!", " ! ", string)
    string = re.sub(r"\(", " \( ", string)
    string = re.sub(r"\)", " \) ", string)
    string = re.sub(r"\?", " \? ", string)
    string = re.sub(r"\s{2,}", " ", string)

    return string.strip().lower()

def load_data_and_labels(positive_data_file, negative_data_file):
    positive = open(positive_data_file, 'rb').read().decode('utf-8')  
    negative = open(negative_data_file, 'rb').read().decode('utf-8')
    positive_examples = positive.split('\n')[:-1]  
    negative_examples = negative.split('\n')[:-1]  

    positive_examples = [s.strip() for s in positive_examples]  
    negative_examples = [s.strip() for s in negative_examples]

    x_text = positive_examples + negative_examples
    x_text = [clean_str(sent) for sent in x_text]

    positive_label = [[1] for _ in positive_examples]
    negative_label = [[0] for _ in negative_examples]

    y = np.concatenate([positive_label, negative_label], axis=0)

    return [x_text, y]


def data_integration(pos_path, neg_path):
    files = os.listdir(pos_path)
    f = open(pos_path + '/pos.txt', 'a+')
    for file in files:
        t = open(pos_path + '/' + file, 'rb')
        lines = t.readlines()
        f.write(str(lines[0]) + '\n')
    f.close()

    files = os.listdir(neg_path)
    f = open(neg_path + '/neg.txt', 'a+')
    for file in files:
        t = open(neg_path + '/' + file, 'rb')
        lines = t.readlines()
        f.write(str(lines[0]) + '\n')
    f.close()

if __name__ == '__main__':
    save_txt(1.0)
    save_txt(2.0)