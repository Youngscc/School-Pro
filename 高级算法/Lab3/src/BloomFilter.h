# ifndef _BLOOMFILTER_H_
# define _BLOOMFILTER_H_
# include <bits/stdc++.h>
# include "testlib.h"
# define LL long long
using namespace std;

class BloomFilter {

# define _MAX_BIT_SIZE 60000000
# define _COUNT_SIZE 4

private:

    bitset <_MAX_BIT_SIZE> BF;
    int maxItems;
    double probFalse;
    int filterBits;
    int hashNumber;
    int hashB1, hashB2, hashA1, hashA2;
    int *hashRes;

    LL hash1(LL x) {
        LL ret = (1LL * hashA1 * x  + hashB1) % filterBits;
        ret ^= x / filterBits;
        return ret % filterBits;
    }

    LL hash2(LL x) {
        LL ret = (1LL * hashA2 * x + hashB2) % filterBits;
        ret ^= x / filterBits;
        return ret % filterBits;
    }

    void hash_youngsc(LL x) {
        LL h1 = hash1(x),h2 = hash2(x);
        // cerr << h1 << " -- " << h2 << endl;
        for (int i=0; i<hashNumber; ++i)
            hashRes[i] = (h1 + i * h2) % filterBits;
    }

    void assign(int pos, int number) {
        int pos_l = pos * _COUNT_SIZE, pos_r = pos_l + _COUNT_SIZE;
        for (int i=pos_r-1; i>=pos_l; --i) BF.set(i, number & 1), number >>= 1;
    }

    int count(int pos) {
        int pos_l = pos * _COUNT_SIZE, pos_r = pos_l + _COUNT_SIZE;
        int countNumber = 0;
        for (int i=pos_l; i<pos_r; ++i) countNumber = countNumber << 1 | BF[i];
        return countNumber;
    }

    bool add(int pos) {
        int number = count(pos);
        if (number + 1 == (1 << _COUNT_SIZE)) {
            cerr << "ADD!!\n";
            return true;
        }
        else assign(pos, number + 1);
        return false;
    }

    bool sub(int pos) {
        int number = count(pos);
        if (number == 0) {
            cerr << "SUB!!\n";
            return true;
        }
        else assign(pos, number - 1);
        return false;
    }

public:

    BloomFilter(int _maxItems, double _probFalse) {
        
        assert(_maxItems > 0 && "最大元素个数必须为正数");
        assert(_probFalse > 0 && _probFalse < 1 && "错误率必须为(0,1)的浮点数");
        
        BF.reset();
        maxItems = _maxItems;
        probFalse = _probFalse;
        filterBits = ceil((maxItems * log(probFalse)) / log(1.0 / pow(2.0, log(2.0))));
        
        assert (filterBits * _COUNT_SIZE < _MAX_BIT_SIZE && "元素个数太大或误差率太小");
        
        hashNumber = ceil(log(2.0) * filterBits / maxItems);
        hashRes = (int*) malloc(hashNumber * sizeof(int));
        
        int x=3;
        hashA1 = hashA2 = 0;
        while (!hashA2) {
            if (__gcd(x, filterBits) == 1) {
                if (!hashA1) hashA1 = x;
                else hashA2 = x;
            }
            x += 2;
        }
        // cerr << filterBits << " " << hashNumber << " " <<  hashA1 << " " << hashA2 << endl;
    }

    // true:成功 false:失败

    bool find(LL item) {
        hash_youngsc(item);
        bool hasInsterted = true;
        for (int i=0; i<hashNumber && hasInsterted; ++i) {
            if (!count(hashRes[i])) hasInsterted = false;
        }
        return hasInsterted;
    }

    bool insert(LL item) {
        if (find(item) == true) return false;
        for (int i=0; i<hashNumber; ++i)
            add(hashRes[i]);
        return true;
    }

    bool remove(LL item) {
        if (find(item) == false) return false;
        for (int i=0; i<hashNumber; ++i)
            sub(hashRes[i]);
        return true;
    }
};

# endif