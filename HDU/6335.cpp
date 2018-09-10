// [Auto Archived]
// Submit: 2018-08-01 13:06:45
// Time: 15MS
// Memory: 1436K

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
int n, a[N], b[N];
LL now;

int main() {
#ifdef zerol
    //freopen("in", "r", stdin);
#endif
    int T; cin >> T;
    while (T--) {
        LL n, m; cin >> n >> m;
        FOR (i, 0, n) cin >> a[i] >> b[i];
        LL s = 0;
        FOR (i, 0, n) {
            LL q = m / (a[i] + b[i]), r = m - q * (a[i] + b[i]);
            LL t = q * a[i] + max(r - b[i], 0LL);
            s += t;
        }
        int ans2 = (s - 1 + m) / m;
        sort(b, b + n);
        now = 1;
        int ans = 0;
        FOR (i, 0, n) {
            now *= b[i] + 1;
            if (now <= m) { ans = i + 1; }
            else break;
        }
        if(ans2>ans) while(1);
        dbg(ans, ans2);
        cout << ans << endl;
    }
}