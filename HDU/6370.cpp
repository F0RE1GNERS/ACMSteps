// [Auto Archived]
// Submit: 2018-08-08 13:01:25
// Time: 358MS
// Memory: 12624K

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
typedef pair<int, int> P;

vector<P> E2;
vector<int> E[N];

int fa[N];
int Fa(int x) {
    return fa[x]==x?x:(fa[x] = Fa(fa[x]));
}

int ans;

void dfs(int u) {
    ++ans;
    for(auto v: E[u]) {
        dfs(v);
    }
}

char s[100];
int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        iota(fa+1, fa+n+1, 1);
        FOR (u, 1, n + 1) {
            int v; scanf("%d%s", &v, s);
            if (s[0] == 'w') E2.emplace_back(u, v);
            else {
                fa[Fa(u)] = Fa(v);
                E[v].emplace_back(u);
            }
        }
        ans = 0;
        for(auto pr: E2) {
            if(Fa(pr.first)==Fa(pr.second)) {
                dfs(pr.second);
            }
        }
        E2.clear();
        FOR(i, 1, n+1) E[i].clear();
        printf("0 %d\n", ans);
    }
}
