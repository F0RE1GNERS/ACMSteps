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
vector<int> g[N];
int deg[N];
vector<pair<int, int>> es;
vector<int> d[N];
bool clique[N];
int n, m, inside[N], outside[N];

int main() {
    #ifdef zerol
    freopen("F.in", "r", stdin);
    #endif // zerol
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        fill(deg, deg + n + 1, 0);
        fill(inside, inside + n + 1, 0);
        fill(outside, outside + n + 1, 0);
        fill(clique, clique + n + 1, 0);

        int clique_size = 0;
        FOR (i, 1, n + 1) g[i].clear();
        FOR (i, 1, n + 1) d[i].clear();
        es.clear();
        FOR (i, 0, m) {
            int u, v; scanf("%d%d", &u, &v);
            g[u].push_back(v); g[v].push_back(u);
            es.push_back({u, v}); es.push_back({v, u});
            deg[u]++; deg[v]++;
        }

        FOR (i, 1, n + 1)
            d[deg[i]].push_back(i);
        FORD (dd, n, -1) {
            bool fail = false;
            for (int& v: d[dd]) {
                int cnt = 0;
                for (int &x: g[v]) {
                    if (clique[x]) cnt++;
                }
                if (cnt == clique_size) { clique[v] = 1; clique_size++; }
                else fail = true;
            }
            //v if (fail) break;
        }
        // dbg(clique);
        // FOR (i, 1, n + 1) dbg(i, clique[i]);

        LL ans1 = 1, ans2 = 1;

        for (auto& e: es) {
            int u = e.first, v = e.second;
            if (clique[u] && !clique[v]) {
                outside[v]++;
                inside[u]++;
            }
        }

        FOR (v, 1, n + 1) {
            if (clique[v]) continue;
            if (outside[v] == clique_size - 1)
                ans1++;
        }

        LL c0 = 0, c1 = 0;
        FOR (v, 1, n + 1) {
            if (!clique[v]) continue;
            // if (inside[v] == 0) get_avail = 1;
            c0 += inside[v] == 0;
            c1 += inside[v] == 1;
        }
        if (c0) ans2 = c0;
        else ans2 = c1 + 1;

        printf("%lld %lld\n", ans1, ans2);
    }
    return 0;
}
 
