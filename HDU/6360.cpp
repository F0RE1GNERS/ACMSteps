// [Auto Archived]
// Submit: 2018-08-08 23:59:33
// Time: 936MS
// Memory: 1632K

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

LL MOD = 1E9 + 7;
const int N = 60;
const int batch[] = {3, 5, 2, 1};
const int cnt[] = {20, 24, 15, 1};
LL f[N<<1][N<<1], C[N<<1][N<<1];

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

void initC() {
    FOR (i, 0, N<<1) {
        C[i][0] = 1 % MOD;
        FOR (j, 1, i + 1) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}

LL mul(LL u,LL v, LL p) {
    return (u * v - LL((long double) u * v / p) * p + p) % p;
}

int main() {
    // LL res = (bin(2, 20, MOD) * 20 + bin(2, 12, MOD) * 24 + bin(2, 30, MOD) * 15 + bin(2, 60, MOD) * 1) % MOD;
    // res = res * get_inv(60, MOD) % MOD;
    // cout << res << endl;

    int T; cin >> T;
    while (T--) {
        LL n; cin >> n >> MOD;
        MOD *= N;
        initC();
        vector<LL> v(n + 1);
        FOR (i, 1, n + 1) cin >> v[i];
        LL res = 0;
        FOR (test, 0, 4) {
            int b = batch[test], c = cnt[test], d = N / b;
            // dbg(b, c, d, n);
            memset(f, 0, sizeof f);
            f[0][0] = 1;
            FOR (i, 1, n + 1) {
                int minb = (v[i] + b - 1) / b;
                FOR (j, 0, d + 1) {
                    for (int k = minb; j + k <= d; ++k) {
                        (f[i][j + k] += mul(f[i - 1][j], C[d - j][k], MOD)) %= MOD;
                        // dbg(d-j, j, i, k, f[i][j+k], f[i-1][j], C[d-j][k]);
                    }
                }
            }
            // dbg(f[n][d]);
            (res += mul(f[n][d], c, MOD)) %= MOD;
        }
        res = res / N;
        cout << res << endl;
    }
}
