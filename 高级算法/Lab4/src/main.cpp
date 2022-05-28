# include <bits/stdc++.h>
# include "testlib.h"
# include "Graph.h"
# include "kruskal.h"
using namespace std;

int main(int argc, char** argv) {
    ofstream outFile("data.txt", ios::app);
    registerGen(argc, argv, 1);
    // ofstream outFile;
    // outFile.open();
    int n = opt<int>("n");
    int o = opt<int>("o");
    cerr << "n = " << n << "   o = " << o << endl;
    long long t = 200000000/(n*n);
    double ans = 0;
    double tt = 1.0*t/100;
    int last = -1;
    long time_0 = clock();
    for (long long i=1; i<=t; ++i){
        int d = (int)(1.0 * i / tt);
        if (d != last) {
            cerr << d << " ";
            last = d;
        }
        vector <zx> G = makeGraph(n, o);
        ans += kruskal(G, n);
    }
    long time_1 = clock();
    cerr << "\n";
    outFile << "Time cost is " << 1.0 * (time_1 - time_0)/CLOCKS_PER_SEC/t*1000   << " ms\n";
    outFile << n << " " << ans/t << endl;
    return 0;
}