# code by ChenSiying 2022/6/12
import jieba
import numpy as np
import os
import time
import csv

text_num = 625

# 读取数据
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

# 分词
vector0 = [[] for _ in range(text_num)]
for i in range(text_num):
    vector0[i] = jieba.lcut(txts[i])

# 去除无关词
vector = [[] for _ in range(text_num)]
remove = ['的', '于', "及", "各", "为", "：", "，", "。", "？", "/", "”", "；", "‘", "【", "】", "{", "}", "、", "《", "》", "+", "=",
          "——", "-", "~", "·", "！", "@", "#", "￥", "%", "……", "&", "*", "（", "）"]
remove0 = []
with open("stopwords-master\\baidu_stopwords.txt", 'r', encoding='utf-8') as file:
    # 删除换行符
    reader = file.read()
    remove0 = reader.split('\n')
remove = remove + remove0

for i in range(text_num):
    vector1 = ''
    for key in vector0[i]:
        if key not in remove:
            vector1 += key
    vector[i] = jieba.lcut(vector1)
print(vector)

union = []
for i in range(text_num):
    for j in range(len(vector[i])):
        if vector[i][j] not in union:
            union.append(vector[i][j])
tf = [[0 for _ in range(text_num)] for _ in range(len(union))]
df0 = [0 for _ in range(len(union))]
df = []
# tf df
print("筛选前向量的长度:", len(union))
start = time.time()
for i in range(len(union)):
    if i % 5000 == 0:
        print("cal df0:", i/len(union)*100, "%", time.time()-start)
    for j in range(text_num):
        if union[i] in vector[j]:
            df0[i] += 1

union_new = []
for i in range(len(union)):
    if df0[i] / text_num > 0.005 and df0[i] / text_num < 0.9:
        union_new.append(union[i])
        df.append(df0[i])
print("calculate for df end.", time.time()-start)

for i in range(len(union_new)):
    for j in range(text_num):
        tf[i][j] = vector[j].count(union_new[i])
print("calculate for tf end.", time.time()-start)

w = [[0 for _ in range(text_num)] for _ in range(len(union_new))]
union_remove = []
result = [['0' for _ in range(len(union_new))] for _ in range(text_num)]
for i in range(len(union_new)):
    for j in range(text_num):
        w[i][j] = tf[i][j] * np.log2(text_num / df[i])
print("calculate for w end.", time.time()-start)

result = [['' for _ in range(len(union_new))] for _ in range(text_num)]
for i in range(text_num):
    for j in range(len(union_new)):
        result[i][j] = w[j][i]
print("文章数:", len(result), "\n向量维度:", len(result[0]))

# 写入文件
out = []
for i in range(text_num):
    temp_out = []
    for j in range(len(union_new)):
        temp_out.append(str(result[i][j]))
    out.append(temp_out)
f = open("vector01.csv", 'w', newline="")
csv_writer = csv.writer(f)
for row in range(len(out)):
    csv_writer.writerow(out[row])

'''
with open("vector01.txt", 'w') as file:
    file.write(out)
'''
'''

# 转换为01序列
union = []
for i in range(text_num):
    for j in range(len(vector[i])):
        if vector[i][j] not in union:
            union.append(vector[i][j])

result = [['0' for _ in range(len(union))] for _ in range(text_num)]
for i in range(text_num):
    for j in range(len(union)):
        if union[j] in vector[i]:
            result[i][j] = '1'
print(result)

# 写入文件
out = ''
for i in range(text_num):
    for j in range(len(union)):
        out += result[i][j]
    out += '\n'
with open("vector01.txt", 'w') as file:
    file.write(out)
'''
