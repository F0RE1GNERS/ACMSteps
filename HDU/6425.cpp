// [Auto Archived]
// Submit: 2018-08-20 12:47:23
// Time: 15MS
// Memory: 1412K

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
const LL MOD = 998244353;
LL bin(LL x, LL n, LL MOD = MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
int main() {

    int T; cin >> T;
    while (T--) {
        LL a, b, c, d; cin >> a >> b >> c >> d;
        LL ans = bin(2, a + b) + bin(2, a + c) + bin(2, a + c) * (b + d) % MOD - bin(2, a) -
                                                                                 bin(2, a) * b % MOD;
        cout << (ans % MOD + MOD) % MOD << endl;
    }
}