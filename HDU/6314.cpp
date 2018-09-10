// [Auto Archived]
// Submit: 2018-07-27 15:13:22
// Time: 873MS
// Memory: 39092K

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
const int N = 3E3 + 100;
const int MOD = 998244353;

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}

LL inv(LL x, LL MOD) { return bin(x, MOD - 2, MOD); }

int n, m, a, b;
LL pu[N], pv[N];
int power2[N * N];

LL invf[N], fac[N];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = inv(fac[n - 1], p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}

void init() {
    power2[0] = 1;
    FOR (i, 1, N * N)
        power2[i] = power2[i - 1] * 2 % MOD;
    fac_inv_init(N, MOD);
}

LL C(int a, int b) {
    return fac[a] * invf[b] % MOD * invf[a - b] % MOD;
}

LL f(int n, int m) {
    LL ret = 0;
    FOR (i, 0, n + 1) FOR (j, 0, m + 1) {
        LL k1 = C(n, i);
        LL k2 = C(m, j);
        LL k = k1 * k2 % MOD * power2[(n - i) * (m - j)] % MOD;
        if ((i + j) % 2) k = MOD - k;
        ret = (ret + k) % MOD;
    }
    return ret;
}

void bf() {
    LL ans = 0;
    FOR (i, a, n + 1) FOR (j, b, m + 1) {
        LL k = f(n - i, m - j) * C(n, i) % MOD * C(m, j) % MOD;
        ans = (ans + k) % MOD;
    }
    cout << ans << endl;
}

int main() {
    init();
    while (~scanf("%d%d%d%d", &n, &m, &a, &b)) {
        // bf();
        LL ans = 0;
        FOR (u, 0, n - a + 1) {
            pu[u] = 0;
            FOR (i, u, n - a + 1) {
                LL t = invf[i - u] * invf[n - i] % MOD;
                if (i & 1) t = MOD - t;
                pu[u] = (pu[u] + t) % MOD;
            }
        }
        FOR (v, 0, m - b + 1) {
            pv[v] = 0;
            FOR (j, v, m - b + 1) {
                LL t = invf[j - v] * invf[m - j] % MOD;
                if (j & 1) t = MOD - t;
                pv[v] = (pv[v] + t) % MOD;
            }
        }
        FOR (u, 0, n - a + 1) FOR (v, 0, m - b + 1) {
            LL k = power2[u * v] * invf[u] % MOD * invf[v] % MOD;
            if ((u + v) & 1) k = MOD - k;
            LL e = pu[u] * pv[v] % MOD;
            ans = (ans + k * e) % MOD;
        }
        ans = (ans * fac[n] % MOD * fac[m] % MOD) % MOD;
        cout << ans << endl;
    }
}