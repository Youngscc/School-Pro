import numpy as np
import matplotlib.pyplot as plt
import math

Mean = []
Var = []
N = []

for i in range(10000):
    X = np.random.normal(10, math.sqrt(5), i + 1)
    Mean.append(X.mean())
    Var.append(X.var())
    N.append(i + 1)

plt.subplot(2, 1, 1)
plt.xlabel('sample size')
plt.ylabel('Mean')
plt.plot(N, Mean)
plt.subplot(2, 1, 2)
plt.xlabel('sample size')
plt.ylabel('Variance')
plt.plot(N, Var)

plt.show()
