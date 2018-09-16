#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

struct Edge {
    int to, cost;
};

const int N = 2E5 + 100;
int n, m, q;
int r[N], K, V[N], mark[N];
vector<Edge> G[N];

LL fa[N], dep[N], idx[N], out[N], ridx[N], dis[N], close[N];
namespace hld {
    int sz[N], son[N], top[N], clk;
    void predfs(int u, int d) {
        dep[u] = d; sz[u] = 1;
        int& maxs = son[u] = -1;
        for (Edge& e: G[u]) {
            int v = e.to;
            if (v == fa[u]) continue;
            fa[v] = u;
            predfs(v, d + 1);
            sz[u] += sz[v];
            if (maxs == -1 || sz[v] > sz[maxs]) maxs = v;
        }
    }
    void dfs(int u, int tp) {
        top[u] = tp; idx[u] = ++clk; ridx[clk] = u;
        if (son[u] != -1) dfs(son[u], tp);
        for (Edge& e: G[u]) {
            int v = e.to;
            if (v != fa[u] && v != son[u]) dfs(v, v);
        }
        out[u] = clk;
    }
    template<typename T>
    int go(int u, int v, T&& f = [](int, int) {}) {
        int uu = top[u], vv = top[v];
        while (uu != vv) {
            if (dep[uu] < dep[vv]) { swap(uu, vv); swap(u, v); }
            f(idx[uu], idx[u]);
            u = fa[uu]; uu = top[u];
        }
        if (dep[u] < dep[v]) swap(u, v);
        // f(idx[v], idx[u]);
        // if (u != v) f(idx[v] + 1, idx[u]);
        return v;
    }
    int up(int u, int d) {
        while (d) {
            if (dep[u] - dep[top[u]] < d) {
                d -= dep[u] - dep[top[u]];
                u = top[u];
            } else return ridx[idx[u] - d];
            u = fa[u]; --d;
        }
        return u;
    }
}

LL dfs(int u, int red) {
    close[u] = red;
    for (Edge &e: G[u]) {
        if (e.to == fa[u]) continue;
        dis[e.to] = dis[u] + e.cost;
        if (r[e.to]) dfs(e.to, e.to);
        else dfs(e.to, red);
    }
}

int check(LL ans) {
    auto f = [](int, int) {};
    LL lca = -1;
    FOR (i, 0, K) {
        int v = V[i];
        if (dis[v] - dis[close[v]] > ans) {
            mark[v] = 1;
            if (lca == -1) lca = v;
            else lca = hld::go(lca, v, f);
        } else mark[v] = 0;
    }
    if (lca == -1) return 1;
    FOR (i, 0, K) if (mark[V[i]]) {
        int v = V[i];
        if (dis[v] - dis[lca] > ans) return 0;
    }
    return 1;
}

int main() {
    #ifdef zerol
    freopen("B.in", "r", stdin);
    #endif // zerol
    int T; cin >> T;
    while (T--) {
        scanf("%d%d%d", &n, &m, &q);
        fill(r, r + n + 1, 0);
        FOR (i, 1, n + 1) G[i].clear();
        FOR (i, 1, m + 1) {
            int t; scanf("%d", &t); r[t] = 1;
        }
        FOR (i, 0, n - 1) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            G[u].push_back({v, w});
            G[v].push_back({u, w});
        }
        hld::clk = 0;
        hld::predfs(1, 0);
        hld::dfs(1, 1);
        dfs(1, 1);
        while (q--) {
            scanf("%d", &K); FOR (i, 0, K) scanf("%d", &V[i]);
            LL l = 0, r = 0; FOR (i, 0, K) r = max(r, dis[V[i]] - dis[close[V[i]]]);
            while (l < r) {
                LL mid = (l + r) / 2;
                if (check(mid)) r = mid;
                else l = mid + 1;
            }
            printf("%lld\n", l);
        }
    }
    return 0;
}
