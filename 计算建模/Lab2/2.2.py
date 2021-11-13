import numpy as np
import matplotlib.pyplot as plt
import cv2

img = cv2.imread('lena512gray.tif', cv2.IMREAD_GRAYSCALE)

img = img.astype(np.float)

T = cv2.dct(img)
T_log = np.log(np.abs(T))
img_back = cv2.idct(T)

n, m = T.shape
T1 = np.zeros([n, m])
T2 = np.zeros([n, m])

for i in range(n):
    for j in range(m):
        if i < 128 and j < 128:
            T1[i][j] = T[i][j]
        else:
            T1[i][j] = 0

img_back1 = cv2.idct(T1)


for i in range(n):
    for j in range(m):
        if i < 128 and j < 128:
            T2[i][j] = 0
        else:
            T2[i][j] = T[i][j]

img_back2 = cv2.idct(T2)


plt.subplot(2, 2, 1), plt.imshow(T_log, 'gray'), plt.title('DCT')
plt.subplot(2, 2, 2), plt.imshow(img_back, 'gray'), plt.title('iDCT')
plt.subplot(2, 2, 3), plt.imshow(img_back1, 'gray'), plt.title('img back1')
plt.subplot(2, 2, 4), plt.imshow(img_back2, 'gray'), plt.title('img back2')
plt.show()
