// [Auto Archived]
// Submit: 2018-08-18 19:08:04
// Time: 998MS
// Memory: 1460K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "DEBUG: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

const int M = 50, MOD = 19260817;

LL inv[M], C[M][M], f[M][M];
void inv_init(LL n, LL p) {
    inv[1] = 1;
    FOR (i, 2, n)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

void comb_init() {
    FOR (i, 0, M) {
        C[i][0] = 1;
        FOR (j, 1, i + 1) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
}

int main() {
    inv_init(M, MOD);
    comb_init();
    LL n, m, cas = 0;
    while ((cin >> n >> m) && n + m) {
        string s, t; cin >> s >> t;
        int cnt = 0;
        FOR (i, 0, n) if (s[i] != t[i]) cnt++;
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        FOR (i, 1, m + 1) FOR (j, 0, n + 1) {
            if (j + 1 <= n) f[i][j] += f[i - 1][j + 1] * C[j][1] % MOD * C[n - j][2] % MOD;
            if (j + 3 <= n) f[i][j] += f[i - 1][j + 3] * C[n - j][3] % MOD;
            if (j - 1 >= 0) f[i][j] += f[i - 1][j - 1] * C[j][2] % MOD * C[n - j][1] % MOD;
            if (j - 3 >= 0) f[i][j] += f[i - 1][j - 3] * C[j][3] % MOD;
            if (i >= 2) f[i][j] -= f[i - 2][j] * (C[n][3] - (i - 2)) % MOD;
            f[i][j] = (f[i][j] % MOD + MOD) % MOD;
            f[i][j] = f[i][j] * inv[i] % MOD;
        }
        printf("Case #%d: ", ++cas);
        printf("%lld\n", f[m][cnt]);
    }
}