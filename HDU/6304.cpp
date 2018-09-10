// [Auto Archived]
// Submit: 2018-07-23 15:25:29
// Time: 592MS
// Memory: 1416K

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
const LL MOD = 1E9 + 7;
const LL N = 62;
LL cnt[N];
LL ans[N];


LL go(LL x) {
    if (!x) return 0;
    LL k = upper_bound(cnt, cnt + N, x) - cnt - 1;
    LL t = x - cnt[k];
    LL ret = go(t) + ans[k] + t % MOD * ((1LL << k) % MOD) % MOD;
    return ret % MOD;
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    cnt[0] = 1; ans[0] = 1;
    FOR (i, 1, N) cnt[i] = cnt[i - 1] * 2 + 1;
    FOR (i, 1, N) ans[i] = (
            ans[i - 1] * 2 + cnt[i - 1] % MOD * ((1LL << (i - 1)) % MOD) % MOD + (1LL << i) % MOD
        ) % MOD;
    int T; cin >> T;
    while (T--) {
        LL n; cin >> n;
        cout << (go(n - 1) + 1) % MOD << endl;
    }
}
