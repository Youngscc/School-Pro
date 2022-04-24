# include <bits/stdc++.h>
# include "naive.h"

using namespace std;

extern ofstream outFile;
extern int n, m;
extern vector <vector <int> > sets;

void naive(double similarity_rate) {
    for (int i=1; i<=m; ++i) {
 	if(i%999 == 0) cerr << i/999 << " ";
        for (int j=i+1; j<=m; ++j) {
            int a=0, b=0;
            int tot = 0;
            while (a < sets[i].size() && b < sets[j].size()) {
                if (sets[i][a] < sets[j][b]) a++;
                else if (sets[i][a] > sets[j][b]) b++;
                else if (sets[i][a] == sets[j][b]) a++, b++, tot++;
            } 
            double rate = 1.0 * tot / (1.0 * (sets[i].size() + sets[j].size() - tot));
            // if (rate >= similarity_rate) printf("%d - %d : %lf\n",ID[i],ID[j], rate);
            if (rate >= similarity_rate) outFile << i << " - " << j << " : " << rate << endl;
        }
    }
    cerr << endl;
}
