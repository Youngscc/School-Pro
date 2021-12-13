import numpy as np
import matplotlib.pyplot as plt
import cv2


def OTSU(img):
    n, m = img.shape
    t = np.zeros(256)
    for i in range(n):
        for j in range(m):
            t[img[i][j]] += 1
    th = 0
    ans = 0
    sum = n * m
    for tp in range(256):
        w0 = 0
        u0 = 0
        w1 = 0
        u1 = 0
        for i in range(256):
            if i <= tp:
                w0 += t[i]
                u0 += t[i] * i
            else:
                w1 += t[i]
                u1 += t[i] * i
        if u0 > 0:
            u0 /= w0
        if u1 > 0:
            u1 /= w1
        w0 /= sum
        w1 /= sum
        u = w0 * u0 + w1 * u1
        g = w0 * ((u0 - u) ** 2) + w1 * ((u1 - u) ** 2)
        if g > ans:
            th = tp
            ans = g
    ret_img = np.zeros(img.shape)
    for i in range(n):
        for j in range(m):
            if img[i][j] > th:
                ret_img[i][j] = 255
            else:
                ret_img[i][j] = 0
    return ret_img


def halftone(img, padding, th):
    n, m = img.shape
    ret_img = np.array(img)
    ret_img = np.pad(ret_img, (padding, padding)) / 255
    dst = np.zeros(ret_img.shape)
    k = np.array([
        [0, 0, 0, 7, 5],
        [3, 5, 7, 5, 3],
        [1, 3, 5, 3, 1]
    ]) / 48
    for i in range(padding, padding + n):
        for j in range(padding, padding + m):
            if ret_img[i][j] < th:
                dst[i][j] = 0
            else:
                dst[i][j] = 1
            e = ret_img[i][j] - dst[i][j]
            for x in range(3):
                for y in range(5):
                    ret_img[i+x][j-2+y] += e * k[x][y]
            ret_img[i][j] = dst[i][j]
    return OTSU(np.uint8(ret_img[padding:padding + n][padding:padding + m] * 255))


now_img = cv2.imread("lena512gray.tif", 0)
now_img_b = OTSU(now_img)
now_img_bi = halftone(now_img, 2, 0.5)
plt.subplot(1, 3, 1), plt.imshow(now_img, 'gray'), plt.title('Origin Image')
plt.subplot(1, 3, 2), plt.imshow(now_img_b, 'gray'), plt.title('OTSU')
plt.subplot(1, 3, 3), plt.imshow(now_img_bi, 'gray'), plt.title('halfone')
plt.show()
