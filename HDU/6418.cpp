// [Auto Archived]
// Submit: 2018-08-20 13:31:03
// Time: 109MS
// Memory: 1400K

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

LL a, b, c, d, e, f;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> a >> b >> c >> d >> e >> f;
        LL n = (a + b + c);
        LL p = a * e + b * f + c * d - a * f - b * d - c * e;
        LL g = abs(__gcd(n, p));
        LL p1 = p / g;
        LL p2 = n / g;
        if (p2 == 1) printf("%lld\n", p1);
        else printf("%lld/%lld\n", p1, p2);
    }
}
