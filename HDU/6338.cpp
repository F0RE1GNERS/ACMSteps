// [Auto Archived]
// Submit: 2018-08-01 16:54:02
// Time: 1934MS
// Memory: 79824K

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
const int N = 1E6 + 100;
const int MOD = 1E9 + 7;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using Tree = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;


LL pown(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
LL invf[N], fac[N];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = pown(fac[n - 1], p - 2, p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}
LL inv[N];
void inv_init(LL n, LL p) {
    inv[1] = 1;
    FOR (i, 2, n)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

vector<int> G[N];
int a[N];
LL S;
LL ans;
int clk;
int son[N];
bool flag;

void go(int u, int fa) {
    ++clk;
    dbg(u, fa);
    if (~fa) S = S * inv[son[fa]--] % MOD;
    dbg(S);
    Tree t;
    for (int& v: G[u]) if (v != fa) t.insert(v);
    do {
        if (t.empty()) break;
        dbg(a[clk]);
        int c = t.order_of_key(a[clk]);
        dbg(u, c, S, son[u]);
        ans = (ans + c * S % MOD * invf[son[u]] % MOD * fac[son[u] - 1] % MOD) % MOD;
        dbg(ans);
        auto it = t.find(a[clk]);
        if (it == t.end()) {  break; }
        else {
            dbg("go", a[clk], u);
            t.erase(it);
            go(a[clk], u);
            if (flag) return;
        }
    } while (1);
    if (!t.empty()) { flag = true; }
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    fac_inv_init(N, MOD);
    inv_init(N, MOD);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        ans = 0; clk = 0;
        flag = false;
        FOR (i, 1, n + 1) G[i].clear();

        FOR (i, 0, n) scanf("%d", &a[i]);
        FOR (_, 1, n) {
            int u, v; scanf("%d%d", &u, &v);
            G[u].push_back(v); G[v].push_back(u);
        }
        LL s = 1;
        FOR (i, 1, n + 1) s = s * fac[G[i].size() - 1] % MOD;

        FOR (i, 1, a[0])
            ans += s * G[i].size() % MOD;
        dbg(ans);
        S = s * G[a[0]].size() % MOD;

        FOR (i, 1, n + 1) son[i] = G[i].size() - 1;
        son[a[0]]++;

        go(a[0], -1);
        cout << ans % MOD << endl;
    }
}