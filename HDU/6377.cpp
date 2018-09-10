// [Auto Archived]
// Submit: 2018-08-12 12:05:16
// Time: 702MS
// Memory: 9684K

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
const int N = 1E3 + 100;
const int M = 1E4 + 100;
const int MOD = 998244353;

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

LL invf[M], fac[M], C[N][N];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = bin(fac[n - 1], p - 2, p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}

void init() {
    FOR (i, 0, N) {
        C[i][0] = 1;
        FOR (j, 1, i + 1) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}

LL ans[M], ans2[M];

int main() {
    int n, d;
    fac_inv_init(M, MOD);
    init();

    while (cin >> n >> d) {
        LL bin2 = 1;
        FOR (k, 0, n + 1) {
            ans[k] = C[n][k] * bin2 % MOD * fac[2 * n - k] % MOD;
            bin2 = bin2 * 2 % MOD;
        }
        FOR (k, 0, n + 1) dbg(k, ans[k]);
        FOR (j, 0, n + 1) {
            for (int k = j + 1; k <= n; k += 2)
                ans[j] -= ans[k] * C[k][j] % MOD;
            for (int k = j + 2; k <= n; k += 2)
                ans[j] += ans[k] * C[k][j] % MOD;
            ans[j] = (ans[j] % MOD + MOD) % MOD;
        }

        // FORD (k, n - 1, 0) ans[k] = (ans[k] - ans[k + 1] + MOD) % MOD;
        // ans2[n] = ans[0];
        // FOR (k, 0, n) ans2[k] = ans[0] - ans[k + 1];

        LL res = 0;
        FORD (k, n, -1) res = (res * d + ans[k]) % MOD; 

        FOR (k, 0, n + 1) dbg(k, ans[k]);
        cout << res << endl;
    }
}