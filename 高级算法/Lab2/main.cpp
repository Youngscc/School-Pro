# include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int n = 1000000;
int A[1000010];
char s[200];
ifstream inFile;
ofstream outFile;

namespace solve1 {
    int Rand_Partition(int *A, int p, int r) {
        int i = rnd.next(p, r);
        swap(A[r], A[i]);
        int x = A[r];
        i = p-1;
        for (int j=p; j<r; ++j) {
            if (A[j] <= x) {
                i++;
                swap(A[i], A[j]);
            }
        }
        swap(A[i+1],A[r]);
        return i+1;
    }

    void QuickSort(int *A, int p, int r) {
        if (p < r) {
            int q = Rand_Partition(A, p, r);
            QuickSort(A, p, q-1);
            QuickSort(A, q+1, r);
        }
    }
}

namespace solve2 {
    int Rand_Partition(int *A, int p, int r) {
        int i = rnd.next(p, r);
        int x = A[i];
        swap(A[i], A[r]);
        int first = p;
        int last = r-1;
        while (1) {
            while (A[first] < x) first++;
            while (A[last] > x) last--;
            if (first >= last) {
                swap(A[first], A[r]);
                return first;
            }
            swap(A[first], A[last]);
            first++;
            last--;
        } 
    }

    void QuickSort(int *A, int p, int r) {
        if (p < r) {
            int q = Rand_Partition(A, p, r);
            QuickSort(A, p, q-1);
            QuickSort(A, q+1, r);
        }
    }
}

namespace solve3 {
    void QuickSort(int *A, int p, int r) {
        sort(A+p, A+r+1);
    }
}

int main(int argc, char** argv){
    registerGen(argc, argv, 1);
    int o = opt<int>("N");
    sprintf(s,"testData/date_%d.txt",o);
    outFile.open(s);
    if (outFile.fail()) {
        cerr << "Output Error\n";
        exit(0);
    }
    for (int t=0; t<=10; ++t) {
        sprintf(s,"testData/%d.txt",t);
        inFile.open(s);
        if (inFile.fail()) {
            cerr << "Input Error\n";
            exit(0);
        }
        for (int i=0; i<n; ++i) inFile >> A[i];
        int clk = clock();
        if (o == 1) solve1::QuickSort(A, 0, n-1);
        else if (o == 2) solve2::QuickSort(A, 0, n-1);
        else if (o == 3) solve3::QuickSort(A, 0, n-1);
        else cerr << "Error ! \n";
        clk = clock()-clk;
        for (int i=1; i<n; ++i) assert(A[i] >= A[i-1]);
        cerr << "Test " << t << " OK ! \n";
        outFile << "Test data " << t << " Time: " << 1.0*clk/CLOCKS_PER_SEC << endl;
        inFile.close();
    }
    return 0;
}
