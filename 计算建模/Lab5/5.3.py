import math
import numpy as np
import numpy.linalg as lg
from matplotlib import pyplot as plt


def make_array_sin():
    m = 100
    X = np.zeros(m)
    for i in range(m):
        X[i] = np.random.uniform(0, 10)
    X.sort()
    Z = [math.sin(x) for x in X]
    Y = [np.random.normal(z, 0.1) for z in Z]
    for i in range(m):
        X[i] = np.random.normal(X[i], 0.1)
    X.sort()
    return X, Y


def leastSquare(x_array, y_array):
    n = 14
    m = x_array.size
    X = np.zeros((m, n))
    Y = np.zeros((m, 1))
    for i in range(m):
        X[i][0] = 1
        for j in range(n - 1):
            X[i][j + 1] = X[i][j] * x_array[i]
        Y[i][0] = y_array[i]
    th = lg.inv(X.T.dot(X)).dot(X.T).dot(Y)
    th_ret = np.zeros(n)
    for i in range(n):
        th_ret[i] = th[i][0]
    return th_ret


def calc_value(x, th):
    tot = 0
    t = 1
    for i in range(th.size):
        tot += t * th[i]
        t *= x
    return tot


def calc_array(X, th):
    return [calc_value(x, th) for x in X]


X, Y = make_array_sin()
th_ls = leastSquare(X, Y)
plt.plot(X, Y, 'ro')
plt.plot(X, calc_array(X, th_ls), 'b')
plt.title('y=sin(x)')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
