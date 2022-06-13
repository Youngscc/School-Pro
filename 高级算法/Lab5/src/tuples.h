# ifndef _TUPLES_H_YOUNGSC_
# define _TUPLES_H_YOUNGSC_
# define LL long long
# include <bits/stdc++.h>

using namespace std;

class tuples {

public:

    int pk, fk, data, walkTimes;
    double val;
    vector <int> nxt;
    vector <double> preSum;

    tuples(int _pk, int _data, int _fk) : pk(_pk), data(_data), fk(_fk) {
        val = 0;
        walkTimes = 0;
        nxt.clear();
        preSum.clear();
    }

};

class table {

private:
    char s[20];
public:
    vector <vector <tuples> > w;
    void init(int n) {
        w.clear();
        static vector <tuples> sig;
        for (int i=0; i<=n; ++i) w.push_back(sig);
        int pk, fk, data;
        for (int i=1; i<=n; ++i) {
            sprintf(s, "table/table%d.tab", i);
            freopen(s, "r", stdin);
            cerr << i << " ";
            while (~scanf("%d%d%d", &pk, &data, &fk))
                w[i].push_back(tuples(pk, data, fk));
            if (i != 1) {
                for (auto& x:w[i-1]) {
                    for (int j=0; j<w[i].size(); ++j) {
                        auto y = w[i][j];
                        if (y.pk == x.fk) x.nxt.push_back(j);
                    }
                }
            }
            fclose(stdin);
        }
        w[0].push_back(tuples(0, 0, 0));
        for (int i=0; i<w[1].size(); ++i) {
            w[0][0].nxt.push_back(i);
        }
    }
};

# endif