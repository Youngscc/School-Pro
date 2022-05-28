# ifndef _GRAPH_H_
# define _GRAPH_H_
# include <bits/stdc++.h>
# include "testlib.h"

using namespace std;

struct zx {

    int u,v;
    double val;

    zx (int _u, int _v, double _val) {
        u = _u; v = _v; val = _val;
    }

};

vector <zx> makeGraph_uniform (int n) {
    vector <zx> ret;
    ret.clear();
    for (int i=0; i<n; ++i)
        for (int j=i+1; j<n; ++j)
            ret.push_back(zx(i,j,rnd.next()));
    return ret;
}

double getnext(int o){
    double p1, p2, t1, t2, t3;
    if (o == 1) {
        return rnd.next();
    } else if (o == 2) {
        p1 = 0.4, p2 = 0.8;
        t1 = 0.2, t2 = 0.4, t3 = 0.4;
    } else if (o == 3) {
        p1 = 0.4, p2 = 0.8;
        t1 = 0.2, t2 = 0.6, t3 = 0.2;
    } else if (o == 4) {
        p1 = 0.4, p2 = 0.8;
        t1 = 0.8, t2 = 0.1, t3 = 0.1;
    }
    double p = rnd.next();
    if (p < t1) return rnd.next(p1);
    else if (p < t1+t2) return rnd.next(p1, p2);
    else return rnd.next(p2, 1.0);
}

vector <zx> makeGraph (int n, int o) {
    vector <zx> ret;
    ret.clear();
    for (int i=0; i<n; ++i)
        for (int j=i+1; j<n; ++j)
            ret.push_back(zx(i, j, getnext(o)));
    return ret;
}

# endif