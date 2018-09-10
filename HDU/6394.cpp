// [Auto Archived]
// Submit: 2018-08-13 13:26:53
// Time: 826MS
// Memory: 26192K

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
const int N = 1E5 + 100;
vector<int> G[N];

namespace hld {
    int fa[N], dep[N], idx[N], out[N], ridx[N];
    int sz[N], son[N], top[N], clk;
    void predfs(int u, int d) {
        dep[u] = d; sz[u] = 1;
        int& maxs = son[u] = -1;
        for (int& v: G[u]) {
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
        for (int& v: G[u])
            if (v != fa[u] && v != son[u]) dfs(v, v);
        out[u] = clk;
    }
    int up(int u, int d) {
        if (dep[u] < d) return 0;
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

namespace lct {
    extern struct P* const null;
    struct P {
        P *fa, *ls, *rs;
        int v, sz;
        bool rev;

        bool has_fa() { return fa->ls == this || fa->rs == this; }
        bool d() { return fa->ls == this; }
        P*& c(bool x) { return x ? ls : rs; }
        void do_rev() {
            if (this == null) return;
            rev ^= 1;
            swap(ls, rs);
        }
        P* up() {
            sz = ls->sz + rs->sz + 1;
            return this;
        }
        void down() {
            if (rev) {
                rev = 0;
                ls->do_rev(); rs->do_rev();
            }
        }
        void all_down() { if (has_fa()) fa->all_down(); down(); }
    } *const null = new P, pool[N], *pit = pool;


    void rot(P* o) {
        bool dd = o->d();
        P *f = o->fa, *t = o->c(!dd);
        if (f->has_fa()) f->fa->c(f->d()) = o; o->fa = f->fa;
        if (t != null) t->fa = f; f->c(dd) = t;
        o->c(!dd) = f->up(); f->fa = o;
    }
    void splay(P* o) {
        o->all_down();
        while (o->has_fa()) {
            if (o->fa->has_fa())
                rot(o->d() ^ o->fa->d() ? o : o->fa);
            rot(o);
        }
        o->up();
    }
    void access(P* u, P* v = null) {
        if (u == null) return;
        splay(u); u->rs = v;
        access(u->up()->fa, u);
    }
    void make_root(P* o) {
        access(o); splay(o); o->do_rev();
    }
    void split(P* o, P* u) {
        make_root(o); access(u); splay(u);
    }
    void link(P* u, P* v) {
        make_root(u); u->fa = v;
    }
    void cut(P* u, P* v) {
        split(u, v);
        u->fa = v->ls = null; v->up();
    }
    bool adj(P* u, P* v) {
        split(u, v);
        return v->ls == u && u->ls == null && u->rs == null;
    }
    bool linked(P* u, P* v) {
        split(u, v);
        return u == v || u->fa != null;
    }
    P* findrt(P* o) {
        access(o); splay(o);
        while (o->ls != null) o = o->ls;
        return o;
    }
}


void init(int);
lct::P* a[N];
int cur[N];
int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        init(n);
        FOR (u, 2, n + 1) {
            int v; scanf("%d", &v);
            G[u].push_back(v); G[v].push_back(u);
        }
        hld::predfs(1, 0); hld::dfs(1, 1);
        FOR (i, 1, n + 1) {
            int k; scanf("%d", &k);
            lct::link(a[i], a[cur[i] = hld::up(i, k)]);
            dbg(i, cur[i]);
        }
        int Qn; cin >> Qn;
        while (Qn--) {
            int tp; scanf("%d", &tp);
            dbg(tp);
            if (tp == 1) {
                int u; scanf("%d", &u);
                lct::make_root(a[0]); lct::access(a[u]); lct::splay(a[u]);
                printf("%d\n", a[u]->sz - 1);
            } else {
                int u, k; scanf("%d%d", &u, &k);
                lct::cut(a[u], a[cur[u]]);
                lct::link(a[u], a[cur[u] = hld::up(u, k)]);
            }
        }
    }
}
void init(int n) {
    FOR (i, 1, n + 1) G[i].clear();
    hld::clk = 0;
    using namespace lct;
    lct::pit = lct::pool;
    FOR (i, 0, n + 1) a[i] = new (pit++) P{null, null, null, i, 1, false};
}