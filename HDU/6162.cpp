// [Auto Archived]
// Submit: 2017-08-22 18:27:20
// Time: 936MS
// Memory: 25212K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
vector<int> G[N];
int dp[2 * N][19];
bool vis[N];
int ver[2 * N], d[2 * N], first[N], Last[N], par[N];
int tot, n, m, c[N];

void dfs(int u, int dep) {
    vis[u] = 1;
    ver[++tot] = u;
    first[u] = tot;
    d[tot] = dep;
    for (int v: G[u]) {
        if (!vis[v]) {
            par[v] = u;
            dfs(v, dep + 1);
            ver[++tot] = u;
            d[tot] = dep;
        }
    }
    Last[u] = tot;
    // printf("%d %d %d\n", u, first[u], Last[u]);
}

void ST(int n) {
    for (int i = 1; i <= n; ++i) dp[i][0] = i;
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
            int a = dp[i][j - 1], b = dp[i + (1 << (j - 1))][j - 1];
            dp[i][j] = d[a] < d[b] ? a : b;
        }
    }
}

int RMQ(int l, int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) k++;
    int a = dp[l][k], b = dp[r - (1 << k) + 1][k];
    return d[a] < d[b] ? a : b;
}

int Lca(int u, int v) {
    int x = first[u], y = first[v];
    // printf("%d %d\n", x, y);
    // for (int i = 1; i <= tot; ++i)
    //     printf("%d ", ver[i]);
    // puts("");
    if (x > y) swap(x, y);
    return ver[RMQ(x, y)];
}

int main() {
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; ++i)
            G[i].clear();
        for (int i = 1; i <= n; ++i)
            scanf("%d", &c[i]);
        for (int i = 0; i < n - 1; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        tot = 0;
        memset(ver, 0, sizeof ver);
        memset(d, 0, sizeof d);
        memset(first, 0, sizeof first);
        memset(Last, 0, sizeof Last);
        memset(vis, 0, sizeof vis);
        memset(dp, 0, sizeof dp);
        memset(par, 0, sizeof par);
        dfs(1, 0);
        ST(tot);
        for (int i = 0; i < m; ++i) {
            int s, t, a, b;
            LL sum = 0;
            scanf("%d%d%d%d", &s, &t, &a, &b);
            int lca = Lca(s, t);
            while (s != lca) {
                if (c[s] >= a && c[s] <= b) sum += c[s];
                s = par[s];
            }
            while (t != lca) {
                if (c[t] >= a && c[t] <= b) sum += c[t];
                t = par[t];
            }
            if (c[lca] >= a && c[lca] <= b) sum += c[lca];
            printf("%lld%c", sum, i + 1 == m ? '\n' : ' ');
        }
    }
}
