import math

import cv2
import numpy as np
from matplotlib import pyplot as plt


def make_noise(img, a, b, psn, p):
    s = 1.0 - p
    img_1 = np.zeros(img.shape)
    (n, m) = img.shape
    for i in range(n):
        for j in range(m):
            rd = float(np.random.rand(1))
            if rd > psn/100.0:
                img_1[i][j] = img[i][j]
                continue
            rd = np.random.rand()
            if rd < p:
                img_1[i][j] = a
            else:
                img_1[i][j] = b
    return img_1


def filter_out_noise(img, k_size):
    (n, m) = img.shape
    img_inv = np.zeros(img.shape)
    arr = []
    for i in range(n):
        for j in range(m):
            if 0 < img[i][j] < 255:
                img_inv[i][j] = img[i][j]
                continue
            for x in range(i-k_size, i+k_size+1):
                for y in range(j-k_size, j+k_size+1):
                    if 0 <= x < n and 0 <= y < m:
                        arr.append(img[x][y])
                    else:
                        arr.append(0)
            img_inv[i][j] = np.median(arr)
            arr = []
    return img_inv


def get_snr(img1, img2):
    (n, m) = img1.shape
    a = 0
    b = 0
    for i in range(n):
        for j in range(m):
            a += int(img1[i][j])**2
            b += (int(img1[i][j]) - int(img2[i][j]))**2
    return 10*math.log10(a/b)


def get_psnr(img1, img2):
    (n, m) = img1.shape
    mse = 0
    for i in range(n):
        for j in range(m):
            mse += (int(img1[i][j]) - int(img2[i][j]))**2
    mse /= (n*m)
    return 10*math.log10((255*255)/mse)


def get_ssim(img1, img2):
    (n, m) = img1.shape
    c1 = (0.01*255)**2
    c2 = (0.03*255)**2
    mu_x = img1.mean()
    sigma_x = img1.std()
    mu_y = img2.mean()
    sigma_y = img2.std()
    sigma_xy = 0
    for i in range(n):
        for j in range(m):
            sigma_xy += (int(img1[i][j]) - mu_x) * (int(img2[i][j]) - mu_y)
    sigma_xy /= (n*m-1)
    return (2 * mu_x * mu_y + c1) * (2 * sigma_xy + c2) / ((mu_x ** 2) + (mu_y ** 2) + c1) / ((sigma_x ** 2) + (sigma_y ** 2) + c2)


now_img = cv2.imread("lena512gray.tif", 0)

rate = 45
print("Now rate is "+str(rate)+"%.")
now_img_1 = make_noise(now_img, 0, 255, rate, 0.5)
now_img_2 = filter_out_noise(now_img_1, 1)
# now_img_2 = cv2.medianBlur(now_img_1, 3)
SNR = get_snr(now_img, now_img_2)
PSNR = get_psnr(now_img, now_img_2)
SSIM = get_ssim(now_img, now_img_2)
print("SNR=", SNR)
print("PSNR=", PSNR)
print("SSIM=", SSIM)
plt.subplot(1, 3, 1), plt.imshow(now_img, 'gray'), plt.title('Origin image')
plt.subplot(1, 3, 2), plt.imshow(now_img_1, 'gray'), plt.title('Made noise')
plt.subplot(1, 3, 3), plt.imshow(now_img_2, 'gray'), plt.title('filter out noise')
plt.show()
