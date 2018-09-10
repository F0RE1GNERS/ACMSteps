// [Auto Archived]
// Submit: 2018-08-21 17:02:38
// Time: 639MS
// Memory: 11140K

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
    int h, l, r, w;
};

struct Q {
    int x, y;
    bool operator < (const Q& u) const {
        return 1LL * x * u.y < 1LL * y * u.x;
    }
    bool operator == (const Q& u) const {
        return 1LL * x * u.y == 1LL * y * u.x;
    }
};

map<Q, int> R;

const int N = 1E3 + 100, INF = 1E9 + 7;
int n, m, cost[N]; P a[N];
Q st[N], ed[N], b[N];
int stw[N], edw[N];
vector<int> v[N];
LL dp[N][N];

LL go(int l, int r) {
    if (l > r) return 0;
    LL &ret = dp[l][r];
    if (ret >= 0) return ret;
    ret = 1E18;
    int max_cost = 0;
    FOR (i, 0, n) {
        if (l <= stw[i] && edw[i] <= r)
            max_cost = max(max_cost, a[i].w);
    }
    // dbg(l, r, max_cost);
    FOR (i, l, r + 1)
        ret = min(ret, max_cost + go(l, i - 1) + go(i + 1, r));
    return ret;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        m = 0;
        FOR (i, 0, n) {
            cin >> a[i].h >> a[i].l >> a[i].r >> a[i].w;
            st[i] = {a[i].l, a[i].h};
            ed[i] = {a[i].r, a[i].h};
            b[m++] = st[i]; b[m++] = ed[i];
        }
        sort(b, b + m); m = unique(b, b + m) - b;
        // dbg(m);
        memset(cost, 0, sizeof cost);

        FOR (i, 0, m) R[b[i]] = i;
        FOR (i, 0, n) {
            stw[i] = R[st[i]];
            edw[i] = R[ed[i]];
        }

        memset(dp, -1, sizeof dp);
        cout << go(0, m - 1) << endl;
    }
}

