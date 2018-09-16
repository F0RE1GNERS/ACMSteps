#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "Debug: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

const int N = 2e6+10;

LL f[N];

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        LL v, t;
        int a, b, c, d, n = 0;
        scanf("%d%d%d%d%lld%lld", &a, &b, &c, &d, &v, &t);
        FOR(i, 0, a) f[n++] = 1LL*i*c;
        FOR(i, 0, c) f[n++] = 1LL*i*a;
        LL per = 1LL*a*c;
        sort(f, f+n); f[n++] = per;
        LL ans = (t+a)/a*b + (t+c)/c*d-1;
        dbg(ans);
        LL nx = 0;
        FOR(i, 1, n) {
            if(f[i-1]+v<f[i]) {
                dbg(i, f[i-1], f[i]);
                ++nx;
            }
        }
        LL tt = t/per;
        ans-=nx*tt;
        dbg(nx, tt);
        t%=per;
        FOR(i, 1, n) {
            if(f[i-1]+v<f[i] && f[i]<=t) --ans;
        }
        printf("%lld\n", ans);
    }
}
 
