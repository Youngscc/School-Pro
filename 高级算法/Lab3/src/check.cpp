# include <bits/stdc++.h>
using namespace std;

int main(){
    int line = 0;
    ifstream f1, f2;
    ofstream outFile;
    f1.open("BloomFilter.txt");
    f2.open("ArraySet.txt");
    outFile.open("checkResult.txt");
    if (f1.fail() && f2.fail()) {
        cerr << "Input Error";
        exit(0);
    }
    string s1,s2;
    while (f1 >> s1 && f2 >> s2) {
        if (s1 == s2) {
            if (s1 == "Found") line++;
            continue;
        }
        outFile << "Found difference at line " << (line+1) << endl;
        if (s1 == "NOT") f1 >> s1;
        else f2 >> s1;
    }
    outFile << "OVER!";
} 