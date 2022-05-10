### 编译

```
make //编译main主程序
make data //编译数据生成器
make check //编译结果检查器
make clean //清空所有可执行文件
```

### 程序参数

```
./main -n [预计元素个数] -p [期望误报率] -w [1:使用BloomFilter 2:使用数组] //查询结果输出至BloomFilter.txt 或 ArraySet.txt
./data -n [元素个数] -o [0:生成随机数据 1:生成极端数据]
./check //比较 BloomFilter.txt 和 ArraySet.txt 并将结果输出至 checkResult.txt
```

