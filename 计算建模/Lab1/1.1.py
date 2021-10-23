import numpy as np

n = 100000
X = 2 * np.random.random(n) - 1
Y = 2 * np.random.random(n) - 1

m = 0

# 统计在园内的点的个数
for i in range(n):
    if X[i] ** 2 + Y[i] ** 2 <= 1:
        m += 1

Pi = 4 * m / n
print('点的个数为:', n)
print('前十个数字为:')
print(X[0:10])
print(Y[0:10])
print('π=', Pi)
