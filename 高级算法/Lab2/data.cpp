# include <bits/stdc++.h>
# include "testlib.h"
using namespace std;

char s[100];
int a[1000010];

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    int n = 1000000;
    for (int t=0; t<=10; ++t) {
        sprintf(s,"data/%d.txt",t);
        freopen(s, "w", stdout);
        for (int i=0; i<n; ++i) a[i] = i;
        if (t > 0) {
            int p = rnd.next(n);
            int tt = n/10*t;
            if (t == 10) tt = n;
            for (int i=0; i<tt; ++i) a[i] = p;
        }
        shuffle(a, a+n);
        for (int i=0; i<n; ++i) printf("%d ",a[i]);
    }
}