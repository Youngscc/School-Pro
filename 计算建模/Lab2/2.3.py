import numpy as np
import matplotlib.pyplot as plt
import cv2

img = cv2.imread('lena512gray.tif', cv2.IMREAD_GRAYSCALE)

img = img.astype(np.float)

T = cv2.dct(img)

s = np.zeros([128, 128])

for i in range(128):
    for j in range(128):
        s[i][j] = T[i][j] / 4

s_back = cv2.idct(s)

t = np.zeros([1024, 1024])
n, m = img.shape
for i in range(n):
    for j in range(m):
        t[i][j] = T[i][j]

t_back = cv2.idct(t)

plt.subplot(1, 2, 1), plt.imshow(s_back, 'gray'), plt.title('back1')
plt.subplot(1, 2, 2), plt.imshow(t_back, 'gray'), plt.title('back2')
plt.show()

N = 8
c1 = np.zeros([N, N])
for i in range(N):
    for j in range(N):
        if i == 0:
            c1[i][j] = 1 / np.sqrt(N)
        else:
            c1[i][j] = np.cos(np.pi * (2 * j + 1) * i / 2 / N) * np.sqrt(2 / N)

N = 4
c2 = np.zeros([N, N])
for i in range(N):
    for j in range(N):
        if i == 0:
            c2[i][j] = 1 / np.sqrt(N)
        else:
            c2[i][j] = np.cos(np.pi * (2 * j + 1) * i / 2 / N) * np.sqrt(2 / N)

print(c1)
print(c2)
