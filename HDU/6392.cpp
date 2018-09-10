// [Auto Archived]
// Submit: 2018-08-19 10:47:49
// Time: 2792MS
// Memory: 3084K

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

const int N = 210;
const int N4 = N * 4;

int n, s[N][N];

struct DisjointSet {
    int fa[N4];
    int& operator[] (const int &x) { return fa[x]; }
    int operator[] (const int &x) const { return fa[x]; }
    int find(int x) { return fa[x] == x ? fa[x] : fa[x] = find(fa[x]); }
    int join(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx > fy) swap(fx, fy);
        if (fx == fy) return 0;
        fa[fy] = fx; return 1;
    }
};

ostream& operator << (ostream &os, const DisjointSet &d) {
    os << "[";
    FOR (i, 0, 2 * n) os << d[i] << " ";
    os << "]"; return os;
}

struct IntervalTree {
    DisjointSet d[N4];
    int cnt[N4][2];

#define lson o * 2 + 1, l, mid
#define rson o * 2 + 2, mid + 1, r

    void tree_node(int o, int l) {
        cnt[o][0] = cnt[o][1] = 0;
        FOR (i, 0, n) cnt[o][s[l][i]]++;
        FOR (i, 0, 2 * n) d[o][i] = i;
        FOR (i, 0, n - 1) if (s[l][i] == s[l][i + 1])
            cnt[o][s[l][i]] -= d[o].join(i, i + 1);
        FOR (i, 0, n) d[o].join(i, n + i);
        dbg(o, l, cnt[o][0], cnt[o][1], d[o]);
    }

    void maintain(int o, int l, int r) {
        int lc = o * 2 + 1, rc = o * 2 + 2, mid = (l + r) / 2;
        FOR (i, 0, 2) cnt[o][i] = cnt[lc][i] + cnt[rc][i];
        FOR (i, 0, 2 * n) d[o][i] = d[lc][i];
        FOR (i, 0, 2 * n) d[o][2 * n + i] = d[rc][i] + 2 * n;
        FOR (i, 0, n) if (s[mid][i] == s[mid + 1][i])
            cnt[o][s[mid][i]] -= d[o].join(n + i, 2 * n + i);
        vector<int> v(n, 0);
        FOR (i, 3 * n, 4 * n) {
            int rt = d[o].find(i);
            if (rt < n) v[i - 3 * n] = rt;
            else if (rt >= 3 * n) v[i - 3 * n] = rt - 2 * n;
            else {
                d[o][rt] = d[o][i] = i;
                v[i - 3 * n] = i - 2 * n;
            }
        }
        FOR (i, 0, n) d[o][i + n] = v[i];
        dbg(o, l, r, cnt[o][0], cnt[o][1], d[o]);
    }

    void update(int x, int o, int l, int r) {
        if (l == r) { tree_node(o, l); return; }
        int mid = (l + r) / 2;
        if (x <= mid) update(x, lson);
        if (x > mid) update(x, rson);
        maintain(o, l, r);
    }

    void build(int o, int l, int r) {
        if (l == r) { tree_node(o, l); return; }
        int mid = (l + r) / 2;
        build(lson); build(rson);
        maintain(o, l, r);
    }

    void update(int x) { return update(x, 0, 0, n - 1); }

    pair<int, int> query() {
        DisjointSet v = d[0];
        int ans[] = { cnt[0][0], cnt[0][1] };
        FOR (i, 0, n) if (s[0][i] == s[n - 1][i])
            ans[s[0][i]] -= v.join(i, n + i);
        return { ans[0], ans[1] };
    }
} IT;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR (i, 0, n) FOR (j, 0, n)
            cin >> s[i][j];
        FOR (i, 0, n) FOR (j, i + 1, n)
            swap(s[i][j], s[j][i]);
        IT.build(0, 0, n - 1);
        int q; cin >> q;
        while (q--) {
            int t, x; scanf("%d", &t);
            if (t == 1) {
                scanf("%d", &x); x--;
                FOR (i, 0, n) s[x][i] = !s[x][i];
            } else {
                int y; scanf("%d%d", &y, &x); x--; y--;
                s[x][y] = !s[x][y];
            }
            IT.update(x);
            auto res = IT.query();
            printf("%d %d\n", res.first, res.second);
        }
    }
}