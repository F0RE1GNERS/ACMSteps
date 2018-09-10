// [Auto Archived]
// Submit: 2018-08-14 16:24:24
// Time: 0MS
// Memory: 1408K

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
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

const int M = 20, MOD = 998244353;

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

LL invf[M], fac[M];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = bin(fac[n - 1], p - 2, p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}

LL n, l[M], r[M];
LL neg, pos;

void init() {
    neg = (MOD - invf[n + 1]) % MOD;
    pos = invf[n + 1];
}

LL eval(LL x) {
    if (x > 0) return pos * bin(x, n + 1, MOD) % MOD;
    else return neg * bin(x % MOD + MOD, n + 1, MOD) % MOD;
}

int main() {
    fac_inv_init(M, MOD);
    cin >> n;
    FOR (i, 0, n) { cin >> l[i] >> r[i]; }
    init();
    LL ans = 0;
    FOR (i, 0, 1 << n) {
        bool sig = true; LL s = 0;
        FOR (j, 0, n) {
            if ((1 << j) & i) s += r[j];
            else { s += l[j]; sig = !sig; }
        }
        LL v = eval(s);
        // dbg(i, s, sig, v);
        if (sig) ans += v;
        else ans -= v;
    }
    ans = (ans % MOD + MOD) % MOD;
    FOR (i, 0, n) {
        ans = ans * get_inv(r[i] - l[i], MOD) % MOD;
    }
    cout << ans << endl;
}
