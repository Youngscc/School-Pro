程序文件：
main.py：用来进行分词操作，输入是article中的txt文章，输出是分词后转化的向量，存在vector01.csv中。
kmeans.py：用来实现kmeans算法，其中包括了所有改进版本（欧式距离版本、余弦距离版本、多次迭代版本）
error.py：用来计算JL降维之后的向量的误差率。
pca.py：实现了pca降维，在实验中，用来对比JL降维的效果。
getArticle/*:三个爬虫代码，分别从三个网站爬取三种类别的文章
JL.py：实现了高斯JL和binaryJL分别在GaussJL.py和binary.py中。引用了loadData.py中的函数。生成了两种不同的变换矩阵。
loadData.py：把原本的词向量存储在矩阵中。
accessData.py：输出矩阵并计算误差。

数据集：
article：爬虫得到的原始文章，共625篇。
afterJL：JL降维之后的向量结果，共10个结果（每个结果的向量维度大小和JL变换方式有所不同）。
result：实验优化过程中，每一词迭代新内容得到分类结果的日志，可以看到优化过程（score一步步上升）
stopwords-master：停用词表，是选取了百度的停用词。
vector01.csv：分词之后得到的降维前的向量。