# include <bits/stdc++.h>
# include "BloomFilter.h"
# include "ArraySet.h"

# define LL long long
using namespace std;

ifstream inFile;
ofstream outFile;
long time_3;
int number = 0;

void solve1(int n, double p) {
    BloomFilter bf(n, p);
    int o; LL x;
    cerr << "Initialize over!\n";
    int t = 0;
    while (inFile >> o >> x) {
        number++;
        if (number == n/2) time_3 = clock();
        if (o == 1) bf.insert(x);
        else if (o == 0) bf.remove(x);
        else {
            if (bf.find(x) == true) outFile << "Found Element " << x << endl;
            else outFile << "NOT Found Element " << x << endl;
        } 
    }
}

void solve2(int n) {
    ArraySet ast(n);
    int o; LL x;
    cerr << "Initialize over!\n";
    int t = 0;
    while (inFile >> o >> x) {
        number++;
        if (number == n/2) time_3 = clock();
        if (o == 1) ast.insert(x);
        else if (o == 0) ast.remove(x);
        else {
            if (ast.find(x) != -1) outFile << "Found Element " << x << endl;
            else outFile << "NOT Found Element " << x << endl;
        } 
    }
}

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int n = opt <int> ("n");
    int w = opt <int> ("w");
    double p = opt <double> ("p");
    // inFile.open("data1.txt");
    inFile.open("data.txt");
    assert(w >= 1 && w <= 2 && "w is 1 or 2.");
    assert(n <= 1000000 && "n should not more than 1000000.");
    assert(p > 0 && p < 1 && "p should be in (0, 1).");
    if (w == 1) outFile.open("BloomFilter.txt");
    else outFile.open("ArraySet.txt");
    if (inFile.fail()) {
        cerr << "Input error\n";
        exit(0);
    }
    if (outFile.fail()) {
        cerr << "Output error\n";
        exit(0);
    }
    long time_0 = clock();
    if (w == 1) solve1(n, p);
    else solve2(n);
    long time_1 = clock();
    outFile << "Time cost is " << 1.0 * (time_1 - time_0)/CLOCKS_PER_SEC << " s\n";
    // outFile << "Time cost of INSERT is " << 1.0 * (time_3 - time_0)/CLOCKS_PER_SEC << " s\n";
    // outFile << "Time cost of FIND is " << 1.0 * (time_1 - time_3)/CLOCKS_PER_SEC << " s\n";
    inFile.close();
    outFile.close();
}