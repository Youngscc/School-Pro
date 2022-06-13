import math
import random
import numpy as np

from loadData import load_data

epsilon = 1e-1

rows, max_len, datamat = load_data()

rounds = round(math.log(float(rows)) / (epsilon * epsilon))


# k = random.randint(24*round,30*round)
# k = rounds
# 0.5 1 1.5 2 3


def _JL_GAUSS(xs):
    k = round(xs * rounds)

    # sig = 1.0/max_len
    # loc：均值（数学期望为μ） ，scale：标准差 （标准方差为σ2，标准差就是去掉平放），size：抽取样本的size
    transformerGauss = np.random.normal(0.0, 1.0, size=(k, max_len))
    # print(transformerGauss,"mi", len(transformerGauss))
    # print(np.mat(transformerGauss).shape)
    return k, transformerGauss / np.sqrt(k)


# _JL_GAUSS()

def _JL_BINARY(xs):
    k = round(xs * rounds)
    transformerBinary = np.zeros((k, max_len))
    for i in range(k):
        for j in range(max_len):
            t = random.random()
            if (t < 2 / 3):
                continue
            elif (t < 5 / 6):
                transformerBinary[i, j] = -1
            else:
                transformerBinary[i, j] = 1
    # print(transformerBinary)
    return k, transformerBinary / np.sqrt(k) * np.sqrt(3)


# _JL_BINARY()

def _JL_FAST(xs):
    k = xs * round
    q = math.pow(math.log(rows), 2) / max_len * 100
    q = min(q, 1.0)
    print(q)
    matrixP = np.zeros((k, max_len))
    for i in range(k):
        for j in range(max_len):
            if (random.random() > q):
                continue
            else:
                matrixP[i, j] = np.random.normal(0, 1 / q, 1)[0]
    # print(matrixP)
    # matrixAF = np.zeros((k,5))

    matrixAF = np.zeros((k, max_len))
    squareD = math.pow(float(max_len), -0.5)
    for i in range(max_len):
        # for i in range(5):
        hadmard = np.zeros(max_len)
        for j in range(max_len):
            tempp = i & j
            countB = 0
            while tempp > 0:
                countB += tempp % 2
                tempp = tempp >> 1
            if countB & 1 == 0:
                hadmard[j] = squareD
            else:
                hadmard[j] = -squareD
        # print("\n\n\n\n")
        # print(hadmard)
        for ii in range(k):
            matrixAF[ii, i] = (np.mat([matrixP[ii]]) * np.mat([hadmard]).T)[0]
    # print(matrixAF)
    for i in range(k):
        for j in range(max_len):
            if (random.random() > 0.5):
                matrixAF[i, j] = -matrixAF[i, j]
    return matrixAF

# _JL_FAST()
