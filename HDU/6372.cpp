// [Auto Archived]
// Submit: 2018-08-08 17:04:26
// Time: 421MS
// Memory: 6052K

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
const int MOD = 1E9 + 7;

const LL p_max = 3E6 + 100;
LL prime[p_max], p_sz;
void get_prime() {
    static bool vis[p_max];
    FOR (i, 2, p_max) {
        if (!vis[i]) prime[p_sz++] = i;
        FOR (j, 0, p_sz) {
            if (prime[j] * i >= p_max) break;
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}

LL inv(LL x, LL MOD) { return bin(x, MOD - 2, MOD); }

int main() {
    int T; cin >> T;
    get_prime();
    // dbg(p_sz);
    while (T--) {
        LL N, C, K; cin >> C >> N >> K; C--;
        assert (N <= 1000000000 && N >= 1 && K <= 100000 && K >= 1 && C >= 0 && C < 100000);
        LL p = prime[C] % MOD;
        LL b = p;
        LL ans = 0;
        FOR (k, 1, K + 1) {
            b = b * (p + k) % MOD * inv(k + 1, MOD) % MOD;
            if (b != 1)
                ans = (ans + (bin(b, N + 1, MOD) - b + MOD) % MOD * inv(b + MOD - 1, MOD) % MOD) % MOD;
            else ans = (ans + b * N) % MOD;
        }
        cout << ans << endl;
    }
}