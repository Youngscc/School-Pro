# code by ChenSiying 2022/6/12
import numpy as np
import csv
import time
import os
from sklearn.cluster import KMeans
from Bio.Cluster import kcluster


k = 3
vector_num = 625
'''
txts = []
file_names = os.listdir("article")
for file_name in file_names:
    txt = ''
    with open("article" + '/' + file_name, 'r', encoding='utf-8') as file:
        # 删除换行符
        reader = file.read()
        for row in reader:
            content = row.strip('\n')
            txt += content
    txts.append(txt)
print(txts)
'''
start = time.time()
# 读取数据
txt = []
all = []

all_temp = []
with open("vector01.csv", 'r', encoding='utf-8') as file:
    reader = csv.reader(file)
    for row in reader:
        all_temp.append(row)
all.append(all_temp)

file_names = os.listdir("afterJL")
for file_name in file_names:
    all_temp = []
    with open("afterJL" + '/' + file_name, 'r', encoding='utf-8') as file:
        reader = csv.reader(file)
        for row in reader:
            all_temp.append(row)
    #print("向量的长度:", len(all_temp[0]))
    all.append(all_temp)


def hanming(a, b):
    dis0, dis1, dis2 = 0, 0, 0
    for i in range(len(a)):
        dis0 += float(a[i]) * float(b[i])
        dis1 += float(a[i]) * float(a[i])
        dis2 += float(b[i]) * float(b[i])
    return dis0 / np.sqrt(dis1) / np.sqrt(dis2)


def csy_min(my_list):
    max_value = -1
    max_index = 0
    for i in range(len(my_list)):
        if hanming(my_list[i][0], my_list[i][1]) > max_value:
            max_value = hanming(my_list[i][0], my_list[i][1])
            max_index = i + 1
    return max_index


def max_cate(a, b, c):
    if a >= b and a >= c:
        return 1
    if b > a and b >= c:
        return 2
    if c > a and c > b:
        return 3


def kmeans(txt):
    start = time.time()
    catagory = [-1 for _ in range(vector_num)]
    old_category = [-2 for _ in range(vector_num)]
    miu = [[] for _ in range(k)]
    for i in range(k):
        ran = np.random.randint(0, len(txt))
        for j in range(len(txt[ran])):
            miu[i].append(txt[ran][j])

    times = 0
    while times < 100:
        times += 1
        for i in range(vector_num):
            old_category = catagory
        # E step
        for i in range(vector_num):
            my_list = []
            for j in range(k):
                my_list.append([miu[j], txt[i]])
            catagory[i] = csy_min(my_list)
        miu = [[0 for _ in range(len(txt[0]))] for _ in range(k)]
        miu_num = [0 for _ in range(k)]
        # M step
        for i in range(vector_num):
            for j in range(len(miu)):
                if catagory[i] == j + 1:
                    miu_num[j] += 1
                    for p in range(len(txt[0])):
                        miu[j][p] += float(txt[i][p])
        for i in range(len(miu)):
            for p in range(len(txt[0])):
                if miu_num[i] != 0:
                    miu[i][p] / miu_num[i]
    print("分类结果:", catagory)
    print("时间:", time.time()-start)
    return catagory


def sk_kmeans(txt):
    X = np.array(txt)
    k_means = KMeans(n_clusters=3).fit(X)
    print(k_means.labels_+1)
    return k_means.labels_


def bio(txt):
    clusterid, error, nfound = kcluster(txt, 3, dist='u', npass=100)
    print(clusterid)
    return clusterid+1


print("---结果", ":   向量数=", len(all[0][0]), "---")
# truth = kmeans(all[0])

for idontknow in range(11):
    txt = all[idontknow+1]
    print("---第", idontknow+1, "次:   向量数=", len(txt[0]), "---")

    catagory = kmeans(txt)

    #print("time:", time.time() - start, "s")

    # calculate score
    k_cat = [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
    score = [0, 0, 0]
    for i in range(6):
        '''
        temp_score = 0
        for j in range(vector_num):
            if truth[j] == k_cat[i][catagory[j]-1]:
                temp_score += 1
        '''
        score1, score2, score3 = 0, 0, 0
        for j in range(0, 195):
            if catagory[j] == k_cat[i][0]:
                score1 += 1

        for j in range(195, 434):
            if catagory[j] == k_cat[i][1]:
                score2 += 1

        for j in range(434, 625):
            if catagory[j] == k_cat[i][2]:
                score3 += 1

        if score1+score2+score3 > np.sum(score):
            score = [score1, score2, score3]
            #k0 = k_cat[i]

    print("Score:", np.sum(score) / 625)
    # print("第一类score:", score[0]/195)#, k0[0])
    # print("第二类score:", score[1]/239)#, k0[1])
    # print("第三类score:", score[2]/191)#, k0[2])

