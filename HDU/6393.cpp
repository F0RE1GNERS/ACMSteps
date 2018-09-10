// [Auto Archived]
// Submit: 2018-08-13 13:41:32
// Time: 1419MS
// Memory: 41484K

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

typedef pair<int, int> P;
const int N = 2E5 + 100;
vector<P> G[N];

int fa[N], dep[N], idx[N], out[N], ridx[N];
const int maxnode = N * 4;

struct IntervalTree {
#define lson o * 2, l, m
#define rson o * 2 + 1, m + 1, r
    LL setv[maxnode], sumv[maxnode];
    void init() { memset(setv, -1, sizeof setv); memset(sumv, 0, sizeof sumv); }
    void maintain(int o, int l, int r) {
        if (l < r) {
            int lc = o * 2, rc = o * 2 + 1;
            sumv[o] = sumv[lc] + sumv[rc];
        }
        if (setv[o] >= 0) sumv[o] = (r - l + 1) * setv[o];
    }
    void pushdown(int o) {
        if (setv[o] >= 0) {
            int lc = o * 2, rc = o * 2 + 1;
            setv[lc] = setv[rc] = setv[o];
            setv[o] = -1;
        }
    }
    void update(int p, int q, int o, int l, int r, LL v) {
        if (p <= r && l <= q)
        if (p <= l && r <= q) setv[o] = v;
        else {
            pushdown(o);
            int m = (l + r) / 2;
            update(p, q, lson, v); update(p, q, rson, v);
        }
        maintain(o, l, r);
    }
    LL query(int p, int q, int o, int l, int r) {
        if (p > r || l > q) return 0;
        if (setv[o] >= 0) return setv[o] * (min(r, q) - max(l, p) + 1);
        if (p <= l && r <= q) return sumv[o];
        int m = (l + r) / 2;
        return query(p, q, lson) + query(p, q, rson);
    }
} IT;

namespace hld {
    int sz[N], son[N], top[N], clk;
    LL weight[N];
    void predfs(int u, int d) {
        dep[u] = d; sz[u] = 1;
        int& maxs = son[u] = -1;
        for (P& e: G[u]) {
            int v = e.first; int w = e.second;
            if (v == fa[u]) continue;
            fa[v] = u; weight[v] = e.second;
            predfs(v, d + 1);
            sz[u] += sz[v];
            if (maxs == -1 || sz[v] > sz[maxs]) maxs = v;
        }
    }
    void dfs(int u, int tp) {
        top[u] = tp; idx[u] = ++clk; ridx[clk] = u;
        if (son[u] != -1) dfs(son[u], tp);
        for (P& e: G[u]) {
            int v = e.first;
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
        if (u != v) f(idx[v] + 1, idx[u]);
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

int pa[N];
int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }
void join(int x, int y) { int fx = find(x), fy = find(y); pa[fx] = fy; }

int n;

LL solve(int u, int v) {
    dbg(u, v);
    LL ans = 0;
    auto f = [&](int s, int t) {
        ans += IT.query(s, t, 1, 1, n);
    };
    hld::go(u, v, f);
    return ans;
}

int eu[N], ev[N], ew[N];

int main() {
    int T; cin >> T;
    while (T--) {
        int q;
        cin >> n >> q;  
        iota(pa, pa + n + 1, 0);
        int A = -1, B = -1, C = -1;
        FOR (i, 1, n + 1) G[i].clear();
        FOR (i, 0, n) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            eu[i + 1] = u; ev[i + 1] = v; ew[i + 1] = w;
            if (find(u) == find(v)) { A = u, B = v; C = w; continue; }
            G[u].emplace_back(v, w); G[v].emplace_back(u, w);
            join(u, v);
        }
        assert (A != -1);
        hld::clk = 0;
        hld::predfs(1, 0);
        hld::dfs(1, 1);
        IT.init();
        FOR (i, 1, n + 1) {
            using namespace hld;
            assert (idx[i] >= 1 && idx[i] <= n);
            IT.update(idx[i], idx[i], 1, 1, n, weight[i]);
        }
        while (q--) {
            using namespace hld;
            int op, x, y; scanf("%d%d%d", &op, &x, &y);
            if (op == 0) {
                int u = eu[x], v = ev[x];
                if (fa[u] == v) { IT.update(idx[u], idx[u], 1, 1, n, y); }
                else if (fa[v] == u) { IT.update(idx[v], idx[v], 1, 1, n, y); }
                else { C = y; }
            } else {
                LL ans1 = solve(x, y);
                LL ans2 = solve(x, A) + C + solve(B, y);
                LL ans3 = solve(x, B) + C + solve(A, y);
                dbg(ans1, ans2, ans3);
                LL ans = min(ans1, min(ans2, ans3));
                cout << ans << endl;
            }
        }
    }
}