# ifndef _KRUSKAL_H_
# define _KRUSKAL_H_
# include "Graph.h"
# include <bits/stdc++.h>

using namespace std;

vector <int> fa;

int find(int x) {
    return fa[x] = x == fa[x] ? x : find(fa[x]);
}

double kruskal(vector <zx> G, int n) {

    double ret = 0;
    
    for (int i=0; i<n; ++i) fa.push_back(i);

    sort(G.begin(), G.end(), [&](const zx &a, const zx &b){
        return a.val < b.val;
    });
    
    for (auto ed:G) {
        int p = find(ed.u), q = find(ed.v);
        if (p == q) continue;
        fa[p] = q;
        ret += ed.val;
    }

    fa.clear();

    return ret;
}

# endif