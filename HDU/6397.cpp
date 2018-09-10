// [Auto Archived]
// Submit: 2018-08-15 12:41:08
// Time: 78MS
// Memory: 6108K

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
const int M = 3E5 + 100;
const LL MOD = 998244353;
LL pown(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
LL invf[M], fac[M];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = pown(fac[n - 1], p - 2, p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}
inline LL C(LL n, LL m) { // m >= n >= 0
    return m < n || n < 0 ? 0 : fac[m] * invf[n] % MOD * invf[m - n] % MOD;
}
int main() {
    fac_inv_init(M, MOD);
    int T; cin >> T;
    LL n, m, k;
    while (cin >> n >> m >> k) {
        LL ans = C(m - 1, k + m - 1);
        dbg(ans);
        FOR (i, 1, m + 1) {
            LL sgn = (i & 1) ? -1 : 1;
            dbg(i, sgn, C(m - 1, k + m - 1 - i * n) * C(i, m) % MOD);
            ans += sgn * C(m - 1, k + m - 1 - i * n) * C(i, m) % MOD;
        }
        cout << (ans % MOD + MOD) % MOD << endl;
    }
}