// [Auto Archived]
// Submit: 2018-08-20 16:44:58
// Time: 187MS
// Memory: 1412K

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
    LL x1, x0;
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

int compare(P a, P b) {
    // x0 exponent x1 base y0 exp y1 base
    LL x0 = a.x0, x1 = a.x1, y0 = b.x0, y1 = b.x1;
    LL z0 = x1 + 1, z1 = x0 - 1;
    if (z1 > x1) {
        swap(x1, z1);
        swap(x0, z0);
    }
    // dbg(x0, x1, y0, y1, z0, z1);
    if ((y0 == x0 && y1 == x1) || (y0 == z0 && y1 == z1))
        return 0;
    if ((y0 == x0 && y1 > x1) || (y1 == z1 && y0 > z0) || (y0 > x0 && y1 > z1))
        return 1;
    return -1;
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
        // if (cas == 16) {
        //     FOR (i, 0, n) printf("%lld ", a[i]);
        //     puts("");
        //     FOR (i, 0, m) printf("%lld ", b[i]);
        //     puts("");
        //     return 0;
        // }
    }
}
