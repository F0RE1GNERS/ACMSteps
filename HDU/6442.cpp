// [Auto Archived]
// Submit: 2018-08-25 14:50:15
// Time: 2043MS
// Memory: 17048K

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

LL MOD;
typedef unsigned long long ULL;
struct P {
    LL a, b, c;
    P(LL x = 0, LL y = 0, LL z = 0) : a(x), b(y), c(z) { }
    P operator * (const P& x) {
        P res; assert (x.c == c); res.c = c;
        res.a = (a * x.a + b * x.b % MOD * c) % MOD;
        res.b = (a * x.b + b * x.a) % MOD;
        return res;
    }
    P operator + (const P& x) {
        P res = *(this);
        (res.a += x.a) %= MOD;
        (res.b += x.b) %= MOD;
        return res;
    }
    P operator - (const P& x) {
        P res = *(this);
        (res.a += (MOD - x.a % MOD)) %= MOD;
        (res.b += (MOD - x.b % MOD)) %= MOD;
        return res;
    }
};

P bin(P x, LL n) {
    x.a %= MOD; x.b %= MOD; P ret;
    ret.c = x.c; ret.a = 1 % MOD; ret.b = 0;
    for ( ; n; n >>= 1, x = x * x)
        if (n & 1) ret = ret * x;
    return ret;
}

LL a, b, n;
const int N = 1E6 + 100;
LL sq[N], sqr[N];

void init() {
    for (int i = 1; i * i < N; ++i) {
        int k = i * i;
        for (int j = k; j < N; j += k)
            sq[j] = k, sqr[j] = i;
    }
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        cin >> a >> b >> n >> MOD; MOD *= 2;
        P x1(a % MOD, 1 % MOD, b);
        P x2(a % MOD, (MOD - 1) % MOD, b);
        P res = bin(x1, n) - bin(x2, n);
        // dbg(x1.a, x1.b, x1.c);
        // dbg(x2.a, x2.b, x2.c);
        // P r1 = bin(x1, n);
        // dbg(r1.a, r1.b, r1.c);
        // dbg(res.a, res.b, res.c);
        LL b = res.b, c = res.c;
        b = b * sqr[c] % MOD;
        c /= sq[c];
        assert (b % 2 == 0);
        printf("1 %lld %lld\n", b / 2, c);
    }
    return 0;
}
