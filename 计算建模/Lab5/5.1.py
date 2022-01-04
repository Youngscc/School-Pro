import math
import numpy as np
import numpy.linalg as lg
import matplotlib.pyplot as plt


def leastSquare(x_array, y_array):
    m = x_array.size
    X = np.zeros((m, 2))
    Y = np.zeros((m, 1))
    for i in range(m):
        X[i][0] = 1
        X[i][1] = x_array[i]
        Y[i][0] = y_array[i]
    th = lg.inv(X.T.dot(X)).dot(X.T).dot(Y)
    return th[0][0], th[1][0]


def dis(x, y, A, B, C):
    return abs(A*x+B*y+C)/math.sqrt(A**2 + B**2)


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
        k_now = (Y[p1]-Y[p2])/(X[p1]-X[p2])
        b_now = Y[p1] - k_now * X[p1]
        for i in range(m):
            if dis(X[i], Y[i], k_now, -1, b_now) < t:
                tot += 1
        if tot > tot_max:
            k_ret = k_now
            b_ret = b_now
            tot_max = tot
    return b_ret, k_ret


a = 5
b = -1
c = 13
m = 50
X = np.zeros(m)
for i in range(m):
    X[i] = np.random.uniform(0, 20)
Z = (c + a * X) / (-b)
Y = [np.random.normal(z, 2) for z in Z]
for i in range(m):
    X[i] = np.random.normal(X[i], 2)
for i in range(3):
    p = np.random.randint(m)
    X[p] = np.random.uniform(0,20)
    Y[p] = np.random.uniform(0,120)
b_ls, k_ls = leastSquare(X, Y)
b_r, k_r = ransac(X, Y, 0.3, 10000)
X_0 = np.arange(0, 20, 1)
plt.plot(X, Y, 'ro')
plt.plot(X, k_ls*X+b_ls, 'b')
plt.plot(X, k_r*X+b_r, 'g')
plt.plot(X_0, a*X_0+c, 'y')
plt.title('y=5x+13')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()