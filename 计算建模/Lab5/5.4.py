import math
import numpy as np
from matplotlib import pyplot as plt

r_a = 3
r_b = 3
r = 1


def make_array_round(m):
    theta = np.linspace(0, 2 * math.pi, m + 1)
    X = np.zeros(m)
    Y = np.zeros(m)
    for i in range(m):
        X[i] = np.random.normal(r * math.cos(theta[i]) + r_a, 0.1)
        Y[i] = np.random.normal(r * math.sin(theta[i]) + r_b, 0.1)
    for i in range(3):
        p = np.random.randint(m)
        X[p] = np.random.uniform(2, 6)
        Y[p] = np.random.uniform(2, 6)
    return X, Y


def vertical_bisector(x1, x2, y1, y2):
    k_v = (x1 - x2) / (y2 - y1)
    b_v = (y2 ** 2 - y1 ** 2 + x2 ** 2 - x1 ** 2) / (y2 - y1) / 2
    return k_v, b_v


def calculate_round(x, y, k1, b1, k2, b2):
    x0 = (b2 - b1) / (k1 - k2)
    y0 = (k1 * b2 - k2 * b1) / (k1 - k2)
    r0 = ((x - x0) ** 2 + (y - y0) ** 2) ** 0.5
    return x0, y0, r0


def ransac_round(x_arr, y_arr, t):
    num = x_arr.size
    w, N, i, z = 0, 1000, 0, 0.02
    x_ret, y_ret, r_ret = 0, 0, 0
    while i < N:
        p1 = np.random.randint(0, num - 1)
        p2 = np.random.randint(0, num - 1)
        p3 = np.random.randint(0, num - 1)
        while p1 == p2:
            p2 = np.random.randint(0, num - 1)
        while p1 == p3 or p2 == p3:
            p3 = np.random.randint(0, num - 1)
        k1, b1 = vertical_bisector(x_arr[p1], x_arr[p2], y_arr[p1], y_arr[p2])
        k2, b2 = vertical_bisector(x_arr[p1], x_arr[p3], y_arr[p1], y_arr[p3])
        x0, y0, r0 = calculate_round(x_arr[p1], y_arr[p1], k1, b1, k2, b2)
        w0 = 0
        for j in range(num):
            if abs(((x_arr[j] - x0) ** 2 + (y_arr[j] - y0) ** 2) ** 0.5 - r0) < t:
                w0 += 1

        if w0 == num:
            return x0, y0, r0

        if w0 > w:
            x_ret = x0
            y_ret = y0
            r_ret = r0
            w = w0
            if (w / num) ** num < 1e-8:
                N = 10000
            else:
                N = min(np.log(z) / np.log(1 - (w / num) ** num), 10000)
            print(w, num, N)
        i += 1
    print(w)
    return x_ret, y_ret, r_ret


m = 100
X, Y = make_array_round(m)
x0, y0, r0 = ransac_round(X, Y, 0.2)
rou_s = [1 for i in range(1000)]
theta_s = np.linspace(0, 2 * math.pi, 1000)
x0_arr, y0_arr = [], []
for i in range(1000):
    x0_arr.append(rou_s[i] * math.cos(theta_s[i]) + r_a)
    y0_arr.append(rou_s[i] * math.sin(theta_s[i]) + r_b)
plt.plot(x0_arr, y0_arr, 'g')

for i in range(1000):
    x0_arr[i] = r0 * math.cos(theta_s[i]) + x0
    y0_arr[i] = r0 * math.sin(theta_s[i]) + y0
plt.plot(x0_arr, y0_arr, 'b')
plt.plot(X, Y, 'ro')
plt.title("RANSAC Circle")
plt.show()
