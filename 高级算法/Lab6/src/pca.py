from sklearn.decomposition import PCA
import csv
import numpy as np


all = []
all_temp = []
with open("vector01.csv", 'r', encoding='utf-8') as file:
    reader = csv.reader(file)
    for row in reader:
        all_temp.append(row)
all.append(all_temp)

X = np.array(all[0])
pca = PCA(n_components=624)
result = pca.fit_transform(X)
print(result)

out = []
for i in range(len(result)):
    temp_out = []
    for j in range(len(result[i])):
        temp_out.append(result[i][j])
    out.append(temp_out)

print(len(out), len(out[0]))

f = open("pca_624.csv", 'w', newline="")
csv_writer = csv.writer(f)
for row in range(len(out)):
    csv_writer.writerow(out[row])
