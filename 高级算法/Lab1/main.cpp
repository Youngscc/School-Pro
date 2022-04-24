# include <bits/stdc++.h>
# include <ctime>
# include "naive.h"
# include "minhash.h"
# include "lsh.h"
using namespace std;

int n,m;
ifstream inFile;
ofstream outFile;
vector <vector <int> > sets;

char* getOutName(char *s,char *way) {
    int len = strlen(s);
    for (int i=len-1; i>=0; --i) 
        if (s[i] == '.') {
            s[i] = '\0';
            break;
        }
    static char outName[50];
    if (way[1] == 'l') sprintf(outName, "%s_l.ans", s);
    else if (way[1] == 'm') sprintf(outName, "%s_m.ans", s);
    else if (way[1] == 'n') sprintf(outName, "%s_n.ans", s);
    return outName;
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
    int lastid = data[0].first;
    
    for (auto p:data) {
        sets[p.first].push_back(p.second);
    } 
}

int main(int argc, char **argv) {
    if (argc != 4 && argc != 5) {
        cerr << "Error!\n";
        exit(0);
    }
    if (argv[3][1] == 'n' && argc != 4) {
        cerr << "Error!\n";
        exit(0);
    }
    if (argv[3][1] == 'm' && argc != 5) {
        cerr << "Error!\n";
        exit(0);
    }
    inFile.open(argv[1]);
    outFile.open(getOutName(argv[1], argv[3]));
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
    if (argv[3][1] == 'n') naive(strtod(argv[2], NULL));
    else if (argv[3][1] == 'm') min_hash(strtod(argv[2], NULL), atoi(argv[4]));
    else if (argv[3][1] == 'l') lsh(strtod(argv[2], NULL), atoi(argv[4]));
    long time_1 = clock();
    outFile << "Time cost is " << 1.0 * (time_1 - time_0)/CLOCKS_PER_SEC << " s\n";
    inFile.close();
    outFile.close();
}