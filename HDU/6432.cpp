// [Auto Archived]
// Submit: 2018-08-22 12:42:56
// Time: 0MS
// Memory: 2176K

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

const int N = 1E5 + 5;
LL a[N] = {1, 0, 0, 1, 1, 8};
int main() {
    FOR (i, 6, N) {
         a[i] = (i - 2) * a[i - 1] % MOD + (i - 1) * a[i - 2] % MOD - (i & 1 ? -1 : 1) + MOD;
         a[i] %= MOD;
    }
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        cout << a[n] << endl;
    }
}