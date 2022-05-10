# include <bits/stdc++.h>
# include "testlib.h"
# define LL long long
LL a[2000010];
int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);
    int num = 1300000;
    for (int i=0; i<num; ++i) a[i] = rnd.next((LL)0X7fffffffffffff);
    int t=0;
    int n = opt <int> ("n");
    int o = opt <int> ("o");
    if (o == 0) {
        freopen("data1.txt", "w", stdout);
        for (int i=1; i<=n*2; ++i) {
            if (i <= 100) printf("1 %lld\n",a[t]), t++;
            else {
                int p = rnd.next(6);
                if (p >= 3) {
                    p = rnd.next(6);
                    if (p && t < n) printf("1 %lld\n",a[t]), t++;
                    else printf("1 %lld\n",a[rnd.next(t)]);
                } else if (p >= 1) {
                    p = rnd.next(6);
                    if (p) printf("2 %lld\n",a[rnd.next(t)]);
                    else printf("2 %lld\n",rnd.next((LL)0X7fffffffffffff));
                } else {
                    p = rnd.next(6);
                    if (p) printf("0 %lld\n",a[rnd.next(t)]);
                    else printf("0 %lld\n",rnd.next((LL)0X7fffffffffffff));
                }
            }
        }
    } else {
        freopen("data2.txt", "w", stdout);
        for (int i=1; i<=n; ++i) {
            printf("1 %lld\n",a[t]), t++;
        }
        for (int i=1; i<=n; ++i) {
            int p = rnd.next(6);
            if (p) printf("2 %lld\n",a[rnd.next(t)]);
            else printf("2 %lld\n",rnd.next((LL)0X7fffffffffffff));
        }
    }
    return 0;
}