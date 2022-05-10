# include <bits/stdc++.h>
# include <ctime>
# include "naive.h"
# include "minhash.h"
# include "lsh.h"
# include "testlib.h"
# include "mix.h"
using namespace std;

int n,m;
ifstream inFile;
ofstream outFile;
vector <vector <int> > sets;

int randit(int n) {
    return rnd.next(n);
}

string getOutName(string s, int way, int number=0, int p=0) {
    int len = s.length();
    for (int i=len-1; i>=0; --i) 
        if (s[i] == '.') {
            s = s.substr(0, i);
            break;
        }
    if (way == 4) s += "_lsh_" +to_string(number)+ "_"+to_string(p) +".ans";
    else if (way == 3) s += "_mix_"+to_string(number)+".ans";
    else if (way == 2) s += "_minhash_"+to_string(number)+".ans";
    else if (way == 1) s += "_naive.ans";
    return s;
}

void init(ifstream &inFile, vector <vector <int> > &sets) {
    vector <pair <int, int> > data;
    int x,y;
    while (!inFile.eof()) {
        inFile >> x >> y;
        data.push_back(make_pair(x,y));
        m = max(m, x);
        n = max(n, y);
    }
    static vector <int> single_set;
    single_set.clear();
    for (int i=0; i<=m; ++i) sets.push_back(single_set);
    sort(data.begin(), data.end());
    data.erase(unique(data.begin(), data.end()),data.end());
    for (auto p:data) {
        sets[p.first].push_back(p.second);
    } 
}

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    string filename = opt <string> ("F");
    int way = opt <int> ("W");
    double rate = opt <double> ("R");
    assert(("The key W must be 1 2 3 or 4", way >= 1 && way <= 4));
    assert(("The similarity rate must be in [0, 1]", rate >= 0 && rate <= 1));
    inFile.open(filename);
    if (way == 2 || way == 3) outFile.open(getOutName(filename, way, opt <int> ("H")));
    else if (way == 4) outFile.open(getOutName(filename, way, opt <int> ("H"), opt <int> ("P")));
    else outFile.open(getOutName(filename, way));
    if (inFile.fail()) {
        cerr << "Input Error\n";
        exit(0);
    }
    if (outFile.fail()) {
        cerr << "Output Error\n";
        exit(0);
    }
    init(inFile, sets);
    long time_0 = clock();
    if (way == 1) naive(rate);
    else if (way == 2) min_hash(rate, opt <int> ("H"));
    else if (way == 3) mix(rate, opt <int> ("H"));
    else if (way == 4) lsh(rate, opt <int> ("H"), opt <int> ("P"));
    long time_1 = clock();
    outFile << "Time cost is " << 1.0 * (time_1 - time_0)/CLOCKS_PER_SEC << " s\n";
    inFile.close();
    outFile.close();
}