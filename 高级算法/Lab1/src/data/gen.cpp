# include <bits/stdc++.h>
using namespace std;

unordered_set <int> s[1000010];
map <int, int>t;

int main() {
    int a,b;
    while (~scanf("%d%d",&a,&b)) {
        s[a].insert(b);
    }
    for (auto x:s) {
        t[x.size()]++;
    }
    for (auto x:t) printf("%d -- %d\n",x.first,x.second);
}