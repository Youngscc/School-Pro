import numpy as np
import matplotlib.pyplot as plt
import cv2

img = cv2.imread('lena512gray.tif', cv2.IMREAD_GRAYSCALE)
Y = np.fft.fftshift(np.fft.fft2(img))

b = np.log(np.abs(Y))
ph = np.angle(Y)

img_back = np.abs(np.fft.ifft2(np.fft.ifftshift(Y)))

plt.subplot(2, 2, 1), plt.imshow(img, 'gray'), plt.title('img')
plt.subplot(2, 2, 2), plt.imshow(b, 'gray'), plt.title('amplitude')
plt.subplot(2, 2, 3), plt.imshow(ph, 'gray'), plt.title('phase')
plt.subplot(2, 2, 4), plt.imshow(img_back, 'gray'), plt.title('img back')
plt.show()


