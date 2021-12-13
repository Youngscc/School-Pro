import cv2
import matplotlib.pyplot as plt

img = cv2.imread("lena512gray.tif", 2)
print(img)
plt.subplot(1, 1, 1)
plt.imshow(img, 'gray')
plt.title('Origin image')
plt.show()
