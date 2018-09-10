// [Auto Archived]
// Submit: 2018-07-23 12:19:47
// Time: 31MS
// Memory: 1432K

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
const int N = 3000 + 5;
struct P { int x, y, idx; };

P a[N];

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        FOR (i, 0, 3 * n) a[i].idx = i + 1;
        FOR (i, 0, 3 * n) scanf("%d%d", &a[i].x, &a[i].y);
        sort(a, a + 3 * n, [](const P& a, const P& b){ return a.x < b.x || (a.x == b.x && a.y < b.y); });
        FOR (i, 0, n) printf("%d %d %d\n", a[i * 3].idx, a[i * 3 + 1].idx, a[i * 3 + 2].idx);
    }
}
