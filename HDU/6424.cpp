// [Auto Archived]
// Submit: 2018-08-20 19:30:33
// Time: 202MS
// Memory: 1420K

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

struct P {
    LL base, exp;
};

const LL INF = 2E9;
int n, m;
LL a[10], b[10];
P x[10], y[10];

void take_log(LL *a, int len, P *res) {
    if (len == 1) {
        res[0] = {a[0] + 1, INF};
        res[1] = {INF, INF};
    } else if (len == 2) {
        res[0] = {a[0] + 1, INF};
        res[1] = {a[1], INF};
    } else {
        res[0] = {a[1], a[2]};
        res[1] = {a[0] + 1, INF};
    }
}

int compare_integer(LL x, LL y) {
    if (x < y) return 1;
    if (x > y) return -1;
    return 0;
}

int compare(P a, P b) {
    // x0 exponent x1 base y0 exp y1 base
    LL p[] = {min(a.base + 1, INF), a.exp};
    LL q[] = {min(b.base + 1, INF), b.exp};
    sort(p, p + 2); sort(q, q + 2);
    int x = compare_integer(p[0], q[0]);
    int y = compare_integer(p[1], q[1]);
    if (x == 0) return y;
    return x;
}

int main() {
    int T; cin >> T;
    int cas = 0;
    while (T--) {
        cas++;
        int n, m;
        scanf("%d%d", &n, &m);
        FOR (i, 0, n) scanf("%lld", a + i);
        FOR (i, 0, m) scanf("%lld", b + i);
        if (max(n, m) == 1) {
            if (a[0] < b[0]) puts("1");
            else if (a[0] > b[0]) puts("-1");
            else puts("0");
        } else {
            // take log
            take_log(a, n, x);
            take_log(b, m, y);
            if (compare(x[0], x[1]) < 0) swap(x[0], x[1]);
            if (compare(y[0], y[1]) < 0) swap(y[0], y[1]);
            int c1 = compare(x[0], y[0]);
            int c2 = compare(x[1], y[1]);
            if (c1 == 0) {
                printf("%d\n", c2);
            } else {
                printf("%d\n", c1);
            }
        }
    }
}
