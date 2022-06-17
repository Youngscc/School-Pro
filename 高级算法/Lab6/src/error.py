# code by ChenSiying 2022/6/15
import csv
import os
import numpy as np
import time


# 读取数据
txt = []
all = []

all_temp = []
with open("vector01.csv", 'r', encoding='utf-8') as file:
    reader = csv.reader(file)
    for row in reader:
        all_temp.append(row)
all.append(all_temp)

file_names = os.listdir("gaussJL2")
for file_name in file_names:
    all_temp = []
    with open("gaussJL2" + '/' + file_name, 'r', encoding='utf-8') as file:
        reader = csv.reader(file)
        for row in reader:
            all_temp.append(row)
    #print("向量的长度:", len(all_temp[0]))
    all.append(all_temp)


def cosine(a, b):
    dis0, dis1, dis2 = 0, 0, 0
    for i in range(len(a)):
        dis0 += float(a[i]) * float(b[i])
        dis1 += float(a[i]) * float(a[i])
        dis2 += float(b[i]) * float(b[i])
    if dis1 == 0 or dis2 == 0:
        return 0
    return dis0 / np.sqrt(dis1) / np.sqrt(dis2)


def european(a, b):
    dis = 0
    for i in range(len(a)):
        dis += (float(a[i]) - float(b[i]))**2
    return np.sqrt(dis)


ncjs = time.time()
for times in range(10):
    error = [[0 for _ in range(625)] for _ in range(625)]
    cnt = 0
    for i in range(5000):
        ran_a = np.random.randint(0, 625)
        ran_b = np.random.randint(0, 625)
        a = european(all[times+1][ran_a], all[times+1][ran_b])
        b = european(all[0][ran_a], all[0][ran_b])
        if b != 0:
            error[ran_a][ran_b] = a/b - 1
        if error[ran_a][ran_b] > 0.1:
            cnt += 1
    print(times+1, ":超过的对数:", cnt/5000*625*312, "平均误差率:", np.sum(error)/5000)
    '''
    for i in range(625):
        print(i/625*100, "%", time.time()-ncjs)
        for j in range(i+1, 625):
            a = cosine(all[times+1][i], all[times+1][j])
            b = cosine(all[0][i], all[0][j])
            if b != 0:
                error[i][j] = a/b - 1
            if error[i][j] > 0.1:
                cnt += 1
    print(times+1, ":超过的对数:", cnt, "平均误差率:", np.sum(error)/625/312)
    '''
print("time:", time.time()-ncjs)
