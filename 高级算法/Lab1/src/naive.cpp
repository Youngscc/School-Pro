# include <bits/stdc++.h>
# include "naive.h"

using namespace std;

extern ofstream outFile;
extern int n, m;
extern vector <vector <int> > sets;

void naive(double similarity_rate) {
    int tt = m/100;
    int num = 0;
    for (int i=1; i<=m; ++i) {
 	if(i%tt == 0) cerr << i/tt << " ";
        for (int j=i+1; j<=m; ++j) {
            if (sets[i].size() < sets[j].size() * similarity_rate || 
                sets[j].size() < sets[i].size() * similarity_rate)
                continue;
            int a=0, b=0;
            int tot = 0;
            while (a < sets[i].size() && b < sets[j].size()) {
                if (sets[i][a] < sets[j][b]) a++;
                else if (sets[i][a] > sets[j][b]) b++;
                else if (sets[i][a] == sets[j][b]) a++, b++, tot++;
            } 
            double rate = 1.0 * tot / (1.0 * (sets[i].size() + sets[j].size() - tot));
            if (rate >= similarity_rate) num++;
            // if (rate >= similarity_rate) outFile << i << " - " << j << " : " << rate << endl;
        }
    }
    outFile << "The number of similar pairs: " << num << endl; 
    cerr << endl;
}
