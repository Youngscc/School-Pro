import math
import numpy as np
import numpy.linalg as lg
from matplotlib import pyplot as plt


def leastSquare(x_array, y_array):
    n = 2
    m = x_array.size
    X = np.zeros((m, n))
    Y = np.zeros((m, 1))
    for i in range(m):
        X[i][0] = 1
        for j in range(n - 1):
            X[i][j + 1] = X[i][j] * x_array[i]
        Y[i][0] = y_array[i]
    theta = lg.inv(X.T.dot(X)).dot(X.T).dot(Y)
    k = theta[1][0]
    dt = y_array - k * x_array
    dt.sort()
    return dt[0:int(m / 3)].mean(), dt[int(m / 3):int(2 * m / 3)].mean(), dt[int(2 * m / 3):m].mean(), theta[1][0]


def dis(x, y, A, B, C):
    return abs(A * x + B * y + C) / math.sqrt(A ** 2 + B ** 2)


def ransac(X, Y, t, N):
    m = X.size
    k_ret = 0
    b_ret = 0
    tot_max = 0
    for ep in range(N):
        tot = 0
        p1 = np.random.randint(0, m)
        p2 = np.random.randint(0, m)
        while p1 == p2:
            p2 = np.random.randint(0, m)
        k_now = (Y[p1] - Y[p2]) / (X[p1] - X[p2])
        b_now = Y[p1] - k_now * X[p1]
        for i in range(m):
            if dis(X[i], Y[i], k_now, -1, b_now) < t:
                tot += 1
        if tot > tot_max:
            k_ret = k_now
            b_ret = b_now
            tot_max = tot
    dt = Y - k_ret * X
    dt.sort()
    return dt[0:int(m / 3)].mean(), dt[int(m / 3):int(2 * m / 3)].mean(), dt[int(2 * m / 3):m].mean(), k_ret


a = 5
b = -1
c = 13
m = 150
X = np.zeros(m)
Z = np.zeros(m)
Y = np.zeros(m)
for i in range(m):
    X[i] = np.random.uniform(0, 20)
    Z[i] = (c + a * X[i]) / (-b)
    if i % 3 == 1:
        Z[i] += 20
    elif i % 3 == 2:
        Z[i] -= 20

for i in range(m):
    X[i] = np.random.normal(X[i], 1)
    Y[i] = np.random.normal(Z[i], 1)

b1_ls, b2_ls, b3_ls, k_ls = leastSquare(X, Y)
b1_r, b2_r, b3_r, k_r = ransac(X, Y, 0.1, 10000)
X_0 = np.arange(0, 20, 1)

plt.plot(X, Y, 'ro')
plt.plot(X, k_ls * X + b1_ls, 'b')
plt.plot(X, k_ls * X + b2_ls, 'b')
plt.plot(X, k_ls * X + b3_ls, 'b')
plt.plot(X, k_r * X + b1_r, 'g')
plt.plot(X, k_r * X + b2_r, 'g')
plt.plot(X, k_r * X + b3_r, 'g')
plt.plot(X_0, a * X_0 + c, 'y')
plt.plot(X_0, a * X_0 + c+20, 'y')
plt.plot(X_0, a * X_0 + c-20, 'y')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()
