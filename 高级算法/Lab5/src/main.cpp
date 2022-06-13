# include <bits/stdc++.h>
# include "testlib.h"
# include "test.h"
# include "sample.h"
# define LL long long
using namespace std;

table data;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    rnd.setSeed(time(0));
    int n = opt<int>("n");
    int o = opt<int>("o");
    cerr << "Initializing...\n";
    data.init(n);
    test tt(data.w);

    cerr << "\n\n";
    sampling* EW = new ExactWeight();
    cerr << "Exact weight sampling now....\n";
    EW -> Main(data, tt, n, o);
    if (o == 1) tt.printRes((char*)"ResultEW.txt");
    tt.clear();

    cerr << "\n\n";
    sampling* EO = new ExtendedOlken();
    cerr << "Extend Olken sampling now....\n";
    EO -> Main(data, tt, n, o);
    if (o == 1) tt.printRes((char*)"ResultEO.txt");
    tt.clear();

    cerr << "\n\n";
    sampling* OE = new OnlineExploration();
    cerr << "Online exploration sampling now....\n";
    OE -> Main(data, tt, n, o);
    if (o == 1) tt.printRes((char*)"ResultOE.txt");
    tt.clear();
} 