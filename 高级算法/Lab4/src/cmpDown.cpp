# include <bits/stdc++.h>
# include "testlib.h"
# include "Graph.h"
using namespace std;

double didit(vector <zx> G, int n) {
    sort(G.begin(), G.end(), [&](const zx &a, const zx &b){
        return a.val < b.val;
    });
    double ans = 0;
    for (int i=0; i<n-1; ++i) {
        ans += G[i].val;
    }
    return ans;
}

int main(int argc, char** argv) {
    ofstream outFile("data.txt", ios::app);
    registerGen(argc, argv, 1);
    // ofstream outFile;
    // outFile.open("data.txt");
    int n = opt<int>("n");
    int o = opt<int>("o");
    cerr << "n = " << n << "   o = " << o << endl;
    long long t = 200000000/(n*n);
    double ans = 0;
    double tt = 1.0*t/100;
    int last = -1;
    for (long long i=1; i<=t; ++i){
        int d = (int)(1.0 * i / tt);
        if (d != last) {
            cerr << d << " ";
            last = d;
        }
        vector <zx> G = makeGraph(n, o);
        ans += didit(G, n);
    }
    cerr << "\n";
    outFile << n << " " << ans/t << endl;
    return 0;
}