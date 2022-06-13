# include <bits/stdc++.h>
# include "testlib.h"
using namespace std;

int id[10000],n,m;

void solve1() {
    for (int i=1; i<=n; ++i) {
        char s[20];
        sprintf(s, "table/table%d.tab", i);
        freopen(s, "w", stdout);
        // outFile.open(s);
        for (int j=0; j<m; ++j) {
            if (i == 1) {
                int r = rnd.next(10);
                printf("%d %d %d\n", 0, j, r);
            } else {
                int l, r = rnd.next(10);
                int rd = rnd.next(55);
                for (l=1; l<=10; ++l) {
                    if (rd < l) break;
                    rd -= l;
                }
                l -= 1;
                printf("%d %d %d\n", l, j, r);
            }
        }
        fclose(stdin);
        // outFile.close();
    }
}

void solve2() {
    for (int i=1; i<=n; ++i) {
        char s[20];
        sprintf(s, "table/tableRS%d.tab", i);
        freopen(s, "w", stdout);
        // outFile.open(s);
        int tm = max(1, m*3/4);
        for (int i=0; i<m; ++i) id[i] = i;
        shuffle(id+0, id+m);
        for (int j=0; j<m; ++j) {
            int l = rnd.next(tm);
            if (i == 1) printf("%d %d %d\n", 0, j, l);
            else printf("%d %d %d\n", id[j], j, l);
        }
        m = tm;
        fclose(stdin);
        // outFile.close();
    }
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    rnd.setSeed(time(NULL));
    n = opt<int>("n");
    m = opt<int>("m");
    int o = opt<int>("o");
    // ofstream outFile;
    
    if (o == 1) solve1();
    else solve2();
}