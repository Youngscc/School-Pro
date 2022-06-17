import time
import numpy as np
import sys
import csv

from JL import datamat
from JL import rows
from JL import max_len

import JL

np.set_printoptions(threshold=sys.maxsize)

filename11 = "afterJL/gaussJL"
filename22 = "afterJL/binaryJL"
xss = [0.5, 1, 1.5, 2, 3]


# xss = [3 for x in range(10)]

def computeErr(original_data, reduce_data):
    num = original_data.shape[0]
    err = np.zeros((num, num))
    for i in range(num):
        for j in range(i + 1, num):
            original_distance = np.linalg.norm(original_data[i] - original_data[j])
            reduce_distance = np.linalg.norm(reduce_data[i] - reduce_data[j])
            err[i][j] = err[j][i] = np.abs(reduce_distance - original_distance) / original_distance
    return err


def test(xs, idx):
    print(str(xs))
    ERR = np.zeros((rows, rows))
    start = time.time()
    for times in range(10):
        k = 0
        transss = 0
        if idx == 1:
            k, transss = JL._JL_GAUSS(xs)
        elif idx == 2:
            k, transss = JL._JL_BINARY(xs)
        trans = np.mat(transss)
        result = np.zeros((rows, k))
        i = 0
        for line in datamat:
            Out = (trans * np.mat([line]).T).T.A
            result[i, :] = Out[0]
            i += 1
        err = computeErr(datamat, result)
        ERR += err
    errorR = 0
    for i in range(rows):
        for j in range(i + 1, rows):
            errorR += ERR[i][j]
    print(str(errorR / (rows * (rows - 1) / 2) / 10))
    print("time:" + str(time.time() - start))


def outG():
    for xs in xss:
        print(str(xs))
        # test(xs, 1)
        filename1 = filename11 + str(xs) + ".csv"
        file1 = open(filename1, mode='w', newline="")
        wt = csv.writer(file1)
        k, transss = JL._JL_GAUSS(xs)
        trans = np.mat(transss)
        gauss = np.zeros((rows, k))
        i = 0
        for line in datamat:
            gaussOut = (trans * np.mat([line]).T).T.A
            wt.writerow(gaussOut[0])
            gauss[i, :] = gaussOut[0]
            i += 1
        file1.close()


def outB():
    for xs in xss:
        test(xs, 2)
        # print(str(xs))
        filename2 = filename22 + str(xs) + ".csv"
        file2 = open(filename2, mode='w', newline="")
        wt = csv.writer(file2)
        k, transss = JL._JL_BINARY(xs)
        trans = np.mat(transss)
        binary = np.zeros((rows, k))
        i = 0
        for line in datamat:
            BOut = (trans * np.mat([line]).T).T.A
            wt.writerow(BOut[0])
            binary[i, :] = BOut[0]
            i += 1
        file2.close()


print("gauss")
outG()
print("binary")
outB()
