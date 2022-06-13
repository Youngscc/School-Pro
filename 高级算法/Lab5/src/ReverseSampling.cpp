# include <bits/stdc++.h>
# include "testlib.h"
# include "tuples.h"
# include "test.h"
# define LL long long
using namespace std;

table data;

void init(int n) {
    data.w.clear();
    static vector <tuples> sig;
    for (int i=0; i<=n; ++i) data.w.push_back(sig);
    int pk, fk, DATA;
    for (int i=n; i; --i) {
        sprintf(s, "table/tableRS%d.tab", i);
        freopen(s, "r", stdin);
        while (~scanf("%d%d%d", &pk, &DATA, &fk))
            data.w[i].push_back(tuples(pk, DATA, fk));
        if (i != n) {
            for (auto& x:data.w[i]) {
                for (int j=0; j<data.w[i+1].size(); ++j) {
                    auto y = data.w[i+1][j];
                    if (y.pk == x.fk) x.nxt.push_back(j);
                }
            }
        }
        fclose(stdin);
    }
    data.w[0].push_back(tuples(0, 0, 0));
    for (int i=0; i<data.w[1].size(); ++i) {
        data.w[0][0].nxt.push_back(i);
    }
}

vector <int> Sample(int n) {
    vector <int> ret{};
    int nxtpk = rnd.next(data.w[1].size());
    tuples now = data.w[1][nxtpk];
    ret.push_back(data.w[1][nxtpk].data);
    for (int i=1; i<n; ++i){
        nxtpk = now.nxt[0];
        now = data.w[i+1][nxtpk];
        ret.push_back(now.data);
    }
    return ret;
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    rnd.setSeed(time(0));
    int n = opt<int>("n");
    int o = opt<int>("o");
    init(n);
    LL tot = 1;
    if (o == 1) {
        tot = 1200000 * data.w[1].size();
    } else tot = 100000;
    test tt(data.w);
    cerr << tt.pt();
    long time_1 = clock();
    cerr << "Start sampling...\n";
    LL ti = tot/100;
    for (LL i=1; i<=tot; ++i) {
        if (i % ti == 0) cerr << i/ti << " ";
        auto sam = Sample(n);
        tt.insert(sam);
        // for (auto x:sam) cerr << x << " ";
        // cerr << endl;
    }
    long time_2 = clock();
    cerr << "\nSampling over with time cost each time " << 1.0*(time_2 - time_1)/CLOCKS_PER_SEC << "s"<< endl;
    if (o == 1) tt.printRes((char*)"RSResult.txt");
} 