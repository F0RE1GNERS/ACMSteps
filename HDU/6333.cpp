// [Auto Archived]
// Submit: 2018-08-01 15:24:31
// Time: 764MS
// Memory: 6320K

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
const int M = 1E5 + 100;
const LL MOD = 1E9 + 7, INV2 = (MOD + 1) / 2;
int B = 333;

LL pown(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return pown(x, p - 2, p); }
LL invf[M], fac[M];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = pown(fac[n - 1], p - 2, p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}
inline LL C(LL m, LL n) { // m >= n >= 0
    return m < n || n < 0 ? 0 : fac[m] * invf[n] % MOD * invf[m - n] % MOD;
}

struct P { int n, m, b, idx; };
LL ans[M];
vector<P> query;
int n = 1, m = 0;
LL v = 1;

void mvn(int d) {
    if (d == 1) v = v * 2 - C(n - 1, m);
    else v = (v + C(n, m)) * INV2;
    v = (v % MOD + MOD) % MOD;
    dbg(n, m, v);
}
void mvm(int d) {
    if (d == 1) v = v + C(n, m);
    else v = v - C(n, m + 1);
    v = (v % MOD + MOD) % MOD;
    dbg(n, m, v);
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    fac_inv_init(M, MOD);
    int Qn; cin >> Qn;
    FOR (i, 0, Qn) {
        int n, m; scanf("%d%d", &n, &m);
        query.push_back({n, m, n / B, i});
        dbg(n, m);
    }
    sort(query.begin(), query.end(), [](const P& a, const P& b){
        if (a.b != b.b) return a.b < b.b;
        return a.m < b.m;
    });

    for (P& p: query) {
        while (n > p.n) { n--; mvn(-1); }
//        dbg(n, m, v);
        while (m < p.m) { m++; mvm(1); }
//        dbg(n, m, v);
        while (n < p.n) { n++; mvn(1); }
//        dbg(n, m, v);
        while (m > p.m) { m--; mvm(-1); }
//        dbg(n, m, v);


        ans[p.idx] = v;
    }
    FOR (i, 0, Qn) printf("%lld\n", ans[i]);
}