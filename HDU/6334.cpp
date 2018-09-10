// [Auto Archived]
// Submit: 2018-08-02 11:15:46
// Time: 436MS
// Memory: 25944K

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
const int N = 3E5 + 100;
const int MOD = 1E9 + 7;
typedef pair<int, int> P;

vector<int> G[N];
int parent[N], color[N];

class DSU {
public:
    int fa[N], sz[N];
    void init(int n) {
        iota(fa, fa + n + 1, 0);
        fill(sz, sz + n + 1, 1);
        sz[0] = 0;
    }

    int& find_sz(int root) { return root == fa[root] ? sz[root] : sz[find(root)]; }
    int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
    void join(int x, int y) {
        int fx = find(x), fy = find(y);
        fa[fx] = fy; sz[fy] += sz[fx]; sz[fx] = 0;
    }
};

class DSU1: public DSU {
public:
    int three[N];  // total sz of linked **DSU** nodes 
    void init(int n) {
        iota(fa, fa + n + 1, 0);
        fill(sz, sz + n + 1, 1);
        fill(three, three + n + 1, 0);
        sz[0] = 0;
    }

    int& find_three_son(int root) { return root == fa[root] ? three[root] : three[find(root)]; }
    void join(int x, int y) {
        int fx = find(x), fy = find(y);
        fa[fx] = fy; sz[fy] += sz[fx]; sz[fx] = 0;
        three[fy] += three[fx]; three[fx] = 0;
    }
};

DSU two;
DSU1 one;
map<P, int> pm;

void turn_3_to_2(int u, int pa) {
    int u_root = two.find(u), pa_root = two.find(pa);
    int new_block_size = two.find_sz(u_root);
    dbg(u, pa, u_root, pa_root, new_block_size);
    two.join(u_root, pa_root);
    if (parent[pa_root]) one.find_three_son(parent[pa_root]) += new_block_size;
    pa_root = one.find(pa);
    one.find_three_son(pa_root) -= new_block_size;
}

void turn_2_to_1(int u, int pa) {
    int u_root = one.find(u), pa_root = one.find(pa);
    one.join(u_root, pa_root);
}

void predfs(int u, int fa) {
    parent[u] = fa;
    for (int v: G[u]) {
        if (v == fa) continue;
        predfs(v, u);
    }
}

void dfs(int u) {
    for (int v: G[u]) {
        if (v == parent[u]) continue;
        dfs(v);
        if (color[v] == 3)
            one.find_three_son(one.find(u)) += two.find_sz(two.find(v));
    }
}

int ans1(int s, int t) {
    dbg(s, t, two.find(s), two.find(t));
    if (two.find(s) == two.find(t)) return 1;
    if (one.find(parent[two.find(t)]) == one.find(s)) return 1;
    if (two.find(parent[one.find(s)]) == two.find(t)) return 1;
    return 0;
}

int ans2(int s) {
    int res1 = one.find_three_son(one.find(s));
    int res2 = two.find_sz(two.find(s));
    int res3 = color[one.find(s)] == 3 ? two.find_sz(two.find(parent[one.find(s)])) : 0;
    dbg(res1, res2, res3);
    return res1 + res2 + res3;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n, m; cin >> n >> m;
        two.init(n); one.init(n);
        pm.clear();
        FOR (i, 1, n + 1) G[i].clear();
        FOR (i, 0, n - 1) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            G[u].push_back(v); G[v].push_back(u);
            pm[{u, v}] = c; pm[{v, u}] = c;
        }
        predfs(1, 0);
        FOR (i, 2, n + 1) {
            color[i] = pm[{parent[i], i}];
            if (color[i] <= 2) two.join(i, parent[i]);
            if (color[i] == 1) one.join(i, parent[i]);
        }
        dfs(1);

        while (m--) {
            int a, b, s, t;
            scanf("%d%d%d%d", &a, &b, &s, &t);
            if (parent[b] == a) swap(a, b);
            if (color[a] == 3) {
                color[a] = 2;
                turn_3_to_2(a, b);
            } else if (color[a] == 2) {
                color[a] = 1;
                turn_2_to_1(a, b);
            }
            printf("%d %d\n", ans1(s, t), ans2(s));

        }
    }
}