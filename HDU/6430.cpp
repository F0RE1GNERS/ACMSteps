// [Auto Archived]
// Submit: 2018-08-22 13:18:35
// Time: 1170MS
// Memory: 16324K

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
vector<int> G[N];
using BS = bitset<N>;
int ans[N], w[N];
vector<int> t[N];

int merge(BS& a, BS&& b) {
    int ret = N - (a & b)._Find_first();
    a |= b;
    dbg(ret);
    return ret == 0 ? -1 : ret;
}

BS go(int u) {
    BS ret;
    for (int& v: G[u])
        ans[u] = max(ans[u], merge(ret, go(v)));
    for (int& xx: t[w[u]]) {
        int x = N - xx;
        dbg(w[u], x);
        if (ret.test(x)) ans[u] = max(ans[u], xx);
        else ret.set(x);
    }
    return ret;
}


int main() {
    memset(ans, -1, sizeof ans);
    FOR (i, 1, N)
        for (int j = i; j < N; j += i)
            t[j].push_back(i);
    dbg("!");
    int n; cin >> n;
    FOR (u, 2, n + 1) {
        int v; scanf("%d", &v);
        G[v].push_back(u);
    }
    FOR (i, 1, n + 1) scanf("%d", &w[i]);
    go(1);
    FOR (i, 1, n + 1) printf("%d\n", ans[i]);
}