# ifndef _ARRAY_SET_
# define _ARRAY_SET_

# include "testlib.h"
# include <bits/stdc++.h>

# define LL long long

class ArraySet{
    
private:
    LL* sets;
    bool* val;
    int maxItems;
    int maxPos, minPos;

public:
    ArraySet(int _maxItems) {
        maxItems = _maxItems;
        maxPos = 0;
        minPos = -1;
        sets = (LL*) malloc(maxItems * sizeof(LL));
        val = (bool*) malloc(maxItems * sizeof(bool));
    }

    int find(LL x) {
        for (int i=0; i<maxPos; ++i) {
            if (val[i] == true && sets[i] == x) return i;
            if (val[i] == false && minPos == -1) minPos = i;
        }
        return -1;
    }
    
    bool insert(LL x) {
        int p = find(x);
        if (p != -1) return false;
        if (minPos == -1) minPos = maxPos, maxPos++;
        val[minPos] = true;
        sets[minPos] = x;
        minPos = -1;
        return true;
    }

    bool remove(LL x) {
        int p = find(x);
        if (p == -1) return false;
        val[p] = false;
        return true;
    }
};

# endif