// [Auto Archived]
// Submit: 2018-07-25 12:14:12
// Time: 577MS
// Memory: 2988K

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
const int N = 1E5 + 100;
int a[N], t[N];

LL c[N];
inline LL lowbit(LL x) { return x & -x; }
void add(LL x, LL v) {
    for (; x < N; x += lowbit(x))
        c[x] += v;
}
LL sum(LL x) {
    LL ret = 0;
    for (; x > 0; x -= lowbit(x))
        ret += c[x];
    return ret;
}

int main() {
    int n, x, y;
    while (cin >> n >> x >> y) {
        memset(c, 0, sizeof c);

        FOR (i, 0, n) {
            scanf("%d", &a[i]);
            t[i] = a[i];
        }
        sort(t, t + n);
        int lent = unique(t, t + n) - t;
        FOR (i, 0, n) a[i] = lower_bound(t, t + lent, a[i]) - t + 1;
        reverse(a, a + n);
        LL s = 0;
        FOR (i, 0, n) {
            s += sum(a[i] - 1);
            add(a[i], 1);
        }
        dbg(s);
        cout << s * min(x, y) << endl;
    }
}
