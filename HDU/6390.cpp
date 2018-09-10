// [Auto Archived]
// Submit: 2018-08-13 12:57:16
// Time: 592MS
// Memory: 34324K

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

const int M = 1E6 + 100;

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

const LL p_max = 1E6 + 100;
LL prime[p_max], p_sz, mu[p_max], phi[p_max];
bool p_vis[p_max];
vector<pair<LL, int>> mu_comp;
void get_mu() {
    mu[1] = 1;
    phi[1] = 1;
    FOR (i, 2, p_max) {
        if (!p_vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        static LL d;
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            p_vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                phi[d] = phi[i] * prime[j];
                break;
            }
            else {
                phi[d] = phi[i] * (prime[j] - 1);
                mu[d] = -mu[i];
            }
        }
    }
    // FOR (i, 1, p_max) if (mu[i]) mu_comp.emplace_back(i, mu[i]);
}

LL f[M];

LL inv[M];
void inv_init(LL n, LL p) {
    inv[1] = 1;
    FOR (i, 2, n)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

int main() {
    get_mu();
    int T; cin >> T;
    while (T--) {
        LL m, n, p; cin >> m >> n >> p;
        LL ans = 0;

        // FOR (a, 1, m + 1) FOR (b, 1, n + 1) {
        //     LL g = __gcd(a, b);
        //     ans += g * get_inv(phi[g], p);
        //     dbg(a, b, ans);
        // }
        LL q = min(m, n);
        inv_init(q + 10, p);
        FOR (t, 1, q + 1) f[t] = (m / t) * (n / t) % p;
        FOR (g, 1, q + 1) {
            LL w = 0;
            for (int i = 1, t = g; t <= q; ++i, t += g) {
                if (mu[i] > 0) w += f[t];
                else if (mu[i] < 0) w -= f[t];
                // dbg(w);
            }
            // dbg(g, w);
            w = (w % p + p) % p;
            w = w * g % p * inv[phi[g]] % p;
            ans = (ans + w) % p;
        }
        dbg(ans % p);
        cout << ans << endl;
    }
}