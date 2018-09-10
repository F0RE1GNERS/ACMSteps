// [Auto Archived]
// Submit: 2018-08-25 12:26:57
// Time: 483MS
// Memory: 10112K

#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, int> P;

const int N = 1e5+10;
const int MOD = 1e9+7;

vector<P> E[N];

int n, t;
int ans;

int dfs(int p, int _f) {
    int sz = 1;
    for(auto pr: E[p]) {
        if(pr.first==_f) continue;
        int ret = dfs(pr.first, p);
        ans = (ans + 1LL*ret*(n-ret)%MOD*pr.second)%MOD;
        sz+=ret;
    }
    return sz;
}

int main()
{
    while(~scanf("%d", &n)) {
        t = 2; ans = 0;
        for(int i = 1; i<n; ++i) {
            t = 1LL*t*i%MOD;
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            E[u].emplace_back(v, w);
            E[v].emplace_back(u, w);
        }
        dfs(1, 0);
        ans = 1LL*ans*t%MOD;
        printf("%d\n", ans);
        for(int i = 1; i<=n; ++i) E[i].clear();        
    }
}
