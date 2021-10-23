import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def gaussian(x, mu, sigma):
    return 1 / ((2 * np.pi) * pow(np.linalg.det(sigma), 0.5)) * np.exp(
        -0.5 * (x - mu).dot(np.linalg.pinv(sigma)).dot((x - mu).T))


class GMM:
    def __init__(self, n, data, mmu, times=50):
        self.n = n
        self.times = times
        self.sample = data.shape[0]
        self.feature = data.shape[1]
        self.mu = mmu
        self.sig = np.full((n, self.feature, self.feature), np.eye(self.feature, dtype=float)/10.0)
        self.alpha = np.ones(n) / n
        self.X = data

    def main(self):
        gam = np.zeros((self.sample, self.n))
        for t in range(self.times):
            for j in range(self.sample):
                num = 0
                for k in range(self.n):
                    num += self.alpha[k] * gaussian(self.X[j], self.mu[k], self.sig[k])
                for i in range(self.n):
                    gam[j, i] = self.alpha[i] * gaussian(self.X[j], self.mu[i], self.sig[i]) / num
            for i in range(self.n):
                a = np.zeros(self.feature)
                b = 0
                for j in range(self.sample):
                    a += gam[j, i] * self.X[j]
                    b += gam[j, i]
                self.mu[i] = (a/b).tolist()
                a = np.zeros((self.feature, self.feature))
                b = 0
                for j in range(self.sample):
                    a += (self.X[j] - self.mu[i]).reshape(1, self.feature).T.dot(
                        (self.X[j] - self.mu[i]).reshape(1, self.feature)) * gam[j, i]
                    b += gam[j, i]
                self.sig[i] = a/b
                self.alpha[i] = b/self.sample
        return gam


data = pd.read_excel('data.xlsx', header=None)
data = data.values
mmu = []
a = data[5]
a = a.tolist()
mmu.append(a)
a = data[21]
a = a.tolist()
mmu.append(a)
a = data[26]
a = a.tolist()
mmu.append(a)
Main = GMM(3, data, mmu)
Gam = Main.main()
result = np.argmax(Gam, axis=1)

col = []
print(data.shape[0], result.shape[0])


plt.scatter(data[:, 0], data[:, 1], c=result, label=['Class A', 'Class B', 'Class C'])

plt.show()



