import numpy as np

X = np.random.poisson(4.0, 3)
print('All:', X.sum())
print('the first minute:', X[0])
print('the second minute:', X[1])
print('the third minute:', X[2])

time = [0]
now = 0
while 1:
    Y = np.random.exponential(0.25)
    NowTime = time[now] + Y
    if NowTime <= 3.0:
        time.append(NowTime)
        now += 1
    else:
        break

print()
print('All: ', now)
for i in range(now):
    print(time[i+1])

