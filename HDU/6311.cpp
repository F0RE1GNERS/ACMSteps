// [Auto Archived]
// Submit: 2018-07-25 22:57:15
// Time: 2808MS
// Memory: 31940K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "Debug: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
const int N = 1E5 + 10;

struct Edge {
    int u, v;
    int get_other(int one) {
        return u ^ v ^ one;
    }
};

vector<int> path, odd;
deque<int> ep;
int S[N << 1], top;
Edge edges[N << 1];
multimap<pair<int, int>, int> edge_map;
set<int> G[N];
int deg[N], vis[N];
int n, m, mb;
vector<vector<int>> ans;

void DFS(int u) {
    S[top++] = u;
    for (int eid: G[u]) {
        int v = edges[eid].get_other(u);
        G[u].erase(eid);
        G[v].erase(eid);
        DFS(v);
        return;
    }
}

void fleury(int start) {
    int u = start;
    top = 0; path.clear();
    S[top++] = u;
    while (top) {
        u = S[--top];
        if (!G[u].empty())
            DFS(u);
        else path.push_back(u);
    }
}

void init(int);

int get_node(int eid, int idx) {
    // dbg(eid);
    Edge &e = edges[abs(eid) - 1];
    if ((idx == 0) ^ (eid < 0))
        return e.u;
    return e.v;
}

int connection(int u) {
    vis[u] = 1;
    int ret = deg[u] % 2;
    for (int eid: G[u]) {
        int v = edges[eid].get_other(u);
        if (!vis[v]) ret += connection(v);
    }
    return ret;
}

int main() {
    while (cin >> n >> m) {
        init(n);
        FOR (j, 0, m) {
            int u, v; scanf("%d%d", &u, &v);
            edges[j] = {u, v};
            G[u].insert(j); G[v].insert(j);
            edge_map.emplace(make_pair(min(u, v), max(u, v)), (j + 1) * 2 + (u < v));
            deg[u]++; deg[v]++;
        }

        mb = m;
        FOR (i, 1, n + 1) {
            if (deg[i] % 2) odd.push_back(i);
        }
        for (int i = 0; i < int(odd.size()); i += 2) {
            int u = odd[i], v = odd[i + 1];
            edges[m] = {u, v};
            G[u].insert(m); G[v].insert(m);
            m++;
        }
        for (int node = 1; node <= n; ++node) {
            if (vis[node]) continue;
            ep.clear();
            fleury(node);
            for (int i = 0; i + 1 < int(path.size()); ++i) {
                int u = path[i], v = path[i + 1];
                vis[u] = vis[v] = true;
                auto it = edge_map.find({min(u, v), max(u, v)});
                if (it != edge_map.end()) {
                    int id = it->second / 2;
                    int comp = it->second % 2;
                    if ((u < v) ^ comp)
                        ep.push_back(-id);
                    else ep.push_back(id);
                    edge_map.erase(it);
                } else {
                    ep.push_back(0);
                }
            }
            if (find(ep.begin(), ep.end(), 0) != ep.end()) {
                while (ep.front() != 0) {
                    ep.push_back(ep.front());
                    ep.pop_front();
                }
            }
            for (int i = 0; i < int(ep.size()); ) {
                if (ep[i] == 0) { ++i; continue; }
                ans.emplace_back();
                for (; i < int(ep.size()) && ep[i]; ++i)
                    ans.back().push_back(ep[i]);
            }
        }
        
        cout << ans.size() << endl;
        for (auto& a: ans) {
            printf("%d", int(a.size()));
            for (auto& x: a)
                printf(" %d", x);
            puts("");
        }
    }
}

void init(int n) {
    odd.clear();
    memset(deg, 0, sizeof deg);
    memset(vis, 0, sizeof vis);
    FOR (i, 1, n + 1) G[i].clear();
    edge_map.clear();
    ans.clear();
}