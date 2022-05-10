# include <bits/stdc++.h>
# include "lsh.h"
# include "minhash.h"

extern ofstream outFile;
extern int n, m;
extern vector <vector <int> > sets;

using namespace std;

vector <unordered_set <int> > to_cmp;

int hash_lsh(int l,int r,int *sig) {
    int ret = 0;
    for (int i=l; i<=r; ++i) ret = ((1LL * ret * 20001019) % HASH_MOD + sig[i] ) % HASH_MOD;
    return ret;
}

void lsh(double similarity_rate, int hash_number, int t) {
    static vector <int *> sig;
    static vector <int> table[HASH_MOD];
    static unordered_set <int> ep;
    for (int i=0; i<=m; ++i) {
        int *a = (int *)malloc(sizeof(int) * MAX_HASH);
        sig.push_back(a);
        unordered_set <int> ep;
        ep.clear();
        to_cmp.push_back(ep);
    }
    get_sig(hash_number, sig);
    cerr << "Get Sig Over!\n";
    int b = hash_number/t;
    for (int i=1; i<=b; ++i) {
        int l = (i-1)*t+1, r = min(hash_number,t*i);
        for (int j=1; j<=m; ++j) {
            // if (j % 10000 == 0 ) cerr << j << " ";
            int has_res = hash_lsh(l, r, sig[j]);
            for (auto x:table[has_res]) to_cmp[x].insert(j);
            table[has_res].push_back(j);
        }
        // cerr << l << " ";
        for (int j=0; j<HASH_MOD; ++j) table[j].clear();
    }
    int num = 0;
    cerr << "Step First Over!\n";
    int tt = m/100;
    for (int i=1; i<=m; ++i) {
        if (i%tt == 0) cerr << i/tt << " ";
        for (auto j:to_cmp[i]) {
            int tot = 0;
            for (int k=1; k<=hash_number; ++k)
                if (sig[i][k] == sig[j][k]) tot++;
            if (1.0*tot/hash_number >= similarity_rate)
                num++;
                // outFile << i << " - " << j << " : " << 1.0*tot/hash_number << endl;
        }
    }
    outFile << "The number of similar pairs: " << num << endl;
    cerr << endl;
}