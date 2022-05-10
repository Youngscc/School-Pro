# include <bits/stdc++.h>
# include "mix.h"
# include "minhash.h"
using namespace std;

extern ofstream outFile;
extern int n, m;
extern vector <vector <int> > sets;
extern int randit(int n);

void mix(double similarity_rate, int hash_number) {
    double rate = similarity_rate;
    int nu = hash_number;
    static vector <int *>dig;
    for (int i=0; i<=m; ++i) {
        int *a = (int *)malloc(sizeof(int) * MAX_HASH);
        dig.push_back(a);
    }
    get_sig(hash_number, dig);
    cerr << "Hash sign is over\n";
    int tt = m/100, num = 0;
    for (int i=1; i<=m; ++i) {
        if (i%tt == 0) cerr << i/tt << " ";
        for (int j=i+1; j<=m; ++j) {
            if (sets[i].size() < sets[j].size() * similarity_rate || 
                sets[j].size() < sets[i].size() * similarity_rate)
                continue;
            if (sets[i].size() + sets[j].size() < hash_number) {
                int a=0, b=0;
                int tot = 0;
                while (a < sets[i].size() && b < sets[j].size()) {
                    if (sets[i][a] < sets[j][b]) a++;
                    else if (sets[i][a] > sets[j][b]) b++;
                    else if (sets[i][a] == sets[j][b]) a++, b++, tot++;
                } 
                double rate = 1.0 * tot / (1.0 * (sets[i].size() + sets[j].size() - tot));
                if (rate >= similarity_rate) num++; 
            } else {
                int tot = 0;
                for (int k=1; k<=hash_number; ++k) {
                    if (dig[i][k] == dig[j][k]) tot++;
                }
                if (1.0*tot >= similarity_rate*hash_number) num++;
            }
            
            // if (1.0*tot/hash_number >= similarity_rate) outFile << i << " - " << j << " : " << 1.0*tot/hash_number << endl;
        }
    }
    outFile << "The number of similar pairs: " << num << endl;
    cerr << endl;  
    return;
}