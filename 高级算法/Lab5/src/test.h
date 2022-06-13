# ifndef _TEST_H_YOUNGSC_
# define _TEST_H_YOUNGSC_
# include <bits/stdc++.h>
# include "tuples.h"
# define LL long long
using namespace std;
map <vector<int>, int> mp;

class test{

private:
    vector <int> ans;
    bool flag;
    vector <vector <tuples> > w;
    map <vector<int>, int> mp;

    void dfs(int now, int c, int n) {
        if (now == n-1) {
            mp[ans] = 0;
            // for (auto x:ans) cerr << x << " ";
            // cerr << endl;
            return;
        }
        for (int i=0; i<w[now+1].size(); ++i) {
            auto x = w[now+1][i];
            if (x.pk != w[now][c].fk) continue;
            ans.push_back(x.data);
            dfs(now+1, i, n);
            ans.pop_back();
        }
    }

public:

    int pt() {
        return mp.size();
    }

    test(vector <vector <tuples> > &data) {
        mp.clear();
        ans.clear();
        w.clear();
        flag = false;
        int tot = 0;
        for (auto x:data) tot += x.size();
        if (tot <= 200) flag = true;
        else return;
        w = data;
        int n = w.size();
        dfs(0, 0, n);
    }

    void insert(vector <int> now) {
        if (flag == false) return;
        mp[now]++;
    }

    void printRes(char *s) {
        freopen(s, "w", stdout);
        for (auto x:mp) printf("%d\n", x.second);
        fclose(stdout);
    }

    void clear() {
        for (auto& x:mp) x.second = 0;
    }
};

# endif