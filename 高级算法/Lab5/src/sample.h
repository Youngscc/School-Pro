# ifndef _SAMPLE_H_YOUNGSC_
# define _SAMPLE_H_YOUNGSC_
# define LL long long
# include <bits/stdc++.h>
# include "test.h"
# include "tuples.h"

using namespace std;

class sampling {

private:

    bool Accept(double x, double y) {
        if (x <= y) return true;
        // cerr << x << "\n";
        double now = rnd.next(x);
        return now < y;
    }

    vector <int> getit(table& data, int n) {
        int now = 0;
        vector <int> ret{};
        for (int i=0; i<n; ++i){
            if (!data.w[i][now].preSum.size() || !Accept(data.w[i][now].val, *(data.w[i][now].preSum.end()-1))) return ret;
            double rd = rnd.next(*(data.w[i][now].preSum.end()-1));
            now = data.w[i][now].nxt[upper_bound(data.w[i][now].preSum.begin(), data.w[i][now].preSum.end(), rd) - data.w[i][now].preSum.begin()];
            ret.push_back(now);
        }
        return ret;
    }

    virtual void getW(table& data, int n) = 0;

    vector <int> sample(table& data, int n) {
        vector <int> ret{};
        do {
            times++;
            ret = getit(data, n);
        } while (ret.size() != n);
        return ret;
    }

public:
    
    int times;

    void Main(table &data, test& tt, int n, int o) {

        for (int i=0; i<n; ++i)
            for (auto &x:data.w[i])
                x.preSum.clear();

        cerr << "Getting weight now...\n";
        LL time_1 = clock();
        getW(data, n);
        LL time_2 = clock();
        cerr << "Getting weight over with time cost " << 1.0*(time_2 - time_1)/CLOCKS_PER_SEC << "s "<< endl;
        
        for (int i=0; i<n; ++i)
            for (auto &x:data.w[i]) {
                double sum = 0;
                for (auto j:x.nxt) {
                    auto y = data.w[i+1][j];
                    sum += y.val;
                    x.preSum.push_back(sum);
                }
            }

        // cerr << data.w[0][0].val << " " << *(data.w[0][0].preSum.end()-2) << "\n";
        LL tot = 1;
        if (o == 1) {
            for (auto x:data.w) tot *= data.w.size();
            tot *= 1000000;
        } else tot = 1000000;
        time_1 = clock();
        cerr << "Start sampling...\n";
        LL ti = tot/100;
        for (LL i=1; i<=tot; ++i) {
            if (i % ti == 0) cerr << i/ti << " ";
            auto sam = sample(data, n);
            tt.insert(sam);
        }
        cerr << "\n" << data.w[0][0].val << " " << times << '\n';
        time_2 = clock();
        cerr << "\nSampling over with time cost each time " << 1.0*(time_2 - time_1)/CLOCKS_PER_SEC << "s "<< endl;
        
        // cerr << data.w[0][0].val << " " << tt.pt();
    }
};

class ExactWeight : public sampling {

private:

    void getW(table& data, int n) {
        for (auto& x:data.w[n]) x.val = 1.0;
        for (int i=n-1; i>=0; --i) {
            for (auto& x:data.w[i]) {
                x.val = 0;
                for (auto j:x.nxt) {
                    auto y = data.w[i+1][j];
                    x.val += y.val;
                }
            }
        }
    }

};

class ExtendedOlken : public sampling{

private:
    void getW(table& data, int n) {
        times = 0;
        for (auto& x:data.w[n]) x.val = 1.0;
        for (int i=n-1; i>=0; --i) {
            double mx = 0;
            for (auto x:data.w[i]) mx = max(mx, 1.0 * x.nxt.size());
            mx *= data.w[i+1][0].val;
            for (auto& x:data.w[i]) x.val = mx;
        }
    }

};

class OnlineExploration : public sampling {

private:
    int randomWalkTimes;
    const int theta = 13;

    bool randomWalk(table& data, int n) {
        int now = 0;
        vector <int> walk{0};
        for (int i=0; i<n; ++i) {
            if (data.w[i][now].nxt.size() == 0) return false;
            int rd = rnd.next(data.w[i][now].nxt.size());
            now = data.w[i][now].nxt[rd];
            walk.push_back(now);
        }
        for (int i=n-1; i>=0; --i) {
            auto& x = data.w[i][walk[i]];
            x.walkTimes++;
            x.val = ((x.walkTimes-1) * x.val + data.w[i+1][walk[i+1]].val * x.nxt.size()) / x.walkTimes;
        }
        return true;
    }

private:

    void getW(table& data, int n) {
        times = 0;
        for (auto& x:data.w[n]) x.val = 1;
        int m = 0;
        for (auto x:data.w) m += x.size();
        randomWalkTimes = m/n*100;
        // cerr << randomWalkTimes << "\n";
        for (int i=1; i<=randomWalkTimes; ++i)  while(!randomWalk(data, n)) ;
        for (int i=n-1; i; --i) {
            for (auto& x:data.w[i]) {
                if (x.walkTimes >= theta) continue;
                x.val = 0;
                for (auto j:x.nxt) {
                    auto y = data.w[i+1][j];
                    x.val += y.val;
                }
            }
        }
    }

};

# endif