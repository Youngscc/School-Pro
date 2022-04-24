# include <bits/stdc++.h>
# include "minhash.h"
using namespace std;


extern ofstream outFile;
extern int n, m;
extern vector <vector <int> > sets;

int hash_y(int x,int p,int q,int n) {
    return (int)((1LL*p*x+q)%n);
}

int gcd(int x,int y) {
    return y? gcd(y, x%y):x;
}

void get_sig(int hash_number, vector <int *> &dig) {
    srand(time(NULL));
    static vector <vector <int> > supe;
    static vector <int> single_set;
    single_set.clear();
    for (int i=0; i<=n; ++i) supe.push_back(single_set);
    for (int i=1; i<=m; ++i)
        for (auto x:sets[i]) supe[x].push_back(i);
    static int a[MAX_HASH];   
    for (int num=1,x=1; num<=hash_number; x++)
        if (gcd(x,n) == 1) a[num++] = x;
    for (int i=1; i<=hash_number; ++i) {
        int b = rand();
        for (int j=1; j<=m; ++j) dig[j][i] = 1e9;
        for (int j=1; j<=n; ++j) {
            int num = hash_y(j, a[i], b, n);
            for (auto k:supe[j]) dig[k][i] = min(dig[k][i], num);
        }
    }
}

void min_hash(double similarity_rate, int hash_number) {
    static vector <int *>dig;
    for (int i=0; i<=m; ++i) {
        int *a = (int *)malloc(sizeof(int) * MAX_HASH);
        dig.push_back(a);
    }
    get_sig(hash_number, dig);
    cerr << "Hash sign is over\n";
    int tt = m/100;
    for (int i=1; i<=m; ++i) {
        if (i%tt == 0) cerr << i/tt << " ";
        for (int j=i+1; j<=m; ++j) {
            int tot = 0;
            for (int k=1; k<=hash_number; ++k) {
                if (dig[i][k] == dig[j][k]) tot++;
            }
            // if (1.0*tot/hash_number >= similarity_rate) outFile << i << " - " << j << " : " << 1.0*tot/hash_number << endl;
        }
    }
    printf("\n");
        
    return;
}
