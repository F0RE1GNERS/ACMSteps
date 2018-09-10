// [Auto Archived]
// Submit: 2018-08-25 12:36:22
// Time: 1419MS
// Memory: 6512K

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

const int N = 1E5 + 100;
struct P {
    int x, y, v;
    bool operator < (const P &u) const {
        return x < u.x || (x == u.x && y > u.y);
    }
} a[N];
int n;

const int maxnode = N * 4;
struct IntervalTree {
#define lson o * 2, l, m
#define rson o * 2 + 1, m + 1, r
    int setv[maxnode], maxv[maxnode];
    void init() { memset(setv, -1, sizeof setv); memset(maxv, 0, sizeof maxv); }
    void maintain(int o, int l, int r) {
        if (l < r) {
            int lc = o * 2, rc = o * 2 + 1;
            maxv[o] = max(maxv[lc], maxv[rc]);
        }
        if (setv[o] >= 0) maxv[o] = max(setv[o], maxv[o]);
    }
    void pushdown(int o) {
        if (setv[o] >= 0) {
            int lc = o * 2, rc = o * 2 + 1;
            setv[lc] = setv[rc] = setv[o];
            setv[o] = -1;
        }
    }
    void update(int p, int q, int o, int l, int r, int v) {
        if (p <= r && l <= q)
        if (p <= l && r <= q) setv[o] = v;
        else {
            pushdown(o);
            int m = (l + r) / 2;
            update(p, q, lson, v); update(p, q, rson, v);
        }
        maintain(o, l, r);
    }
    int query(int p, int q, int o, int l, int r) {
        if (p > r || l > q) return 0;
        if (setv[o] >= 0) return maxv[o];
        if (p <= l && r <= q) return maxv[o];
        int m = (l + r) / 2;
        return max(query(p, q, lson), query(p, q, rson));
    }
} IT;

void discrete() {
    vector<int> V(n, 0);
    FOR (i, 0, n) V[i] = a[i].y;
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    FOR (i, 0, n) a[i].y = lower_bound(V.begin(), V.end(), a[i].y) - V.begin() + 1;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR (i, 0, n) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].v);
        sort(a, a + n);
        discrete();
        IT.init();
        FOR (i, 0, n) {
            dbg(a[i].x, a[i].y, a[i].v);
            int v = IT.query(0, a[i].y - 1, 1, 0, n) + a[i].v;
            int raw = IT.query(a[i].y, a[i].y, 1, 0, n);
            if (v > raw) IT.update(a[i].y, a[i].y, 1, 0, n, v);
        }
        printf("%d\n", IT.query(0, n, 1, 0, n));
    }
    return 0;
}
