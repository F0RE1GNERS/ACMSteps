// [Auto Archived]
// Submit: 2018-08-22 13:21:12
// Time: 62MS
// Memory: 1512K

#include <bits/stdc++.h>
 
//#undef zerol
using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cerr << "Debug: " << #args << " -> "; err(args); } while (0)
#define fuck(x) do { printf("fuck@%d\n", x); } while(0)
#else
#define dbg(...)
#define fuck(...)9
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

const int INF = 1E9;
const int maxn = 1000;

struct E {
    int from, to, cp, v;
    E() {}
    E(int f, int t, int cp, int v) : from(f), to(t), cp(cp), v(v) {}
};

struct MCMF {
    int n, m, s, t;
    vector<E> edges;
    vector<int> G[maxn];
    bool inq[maxn];     //?????
    int d[maxn];        //Bellman_ford??????
    int p[maxn];        //p[i]??s?i????????????????
    int a[maxn];        //a[i]???s?i?????

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        FOR (i, 0, n + 1) G[i].clear();
        edges.clear(); m = 0;
    }

    void addedge(int from, int to, int cap, int cost) {
        edges.emplace_back(from, to, cap, cost);
        edges.emplace_back(to, from, 0, -cost);
        G[from].push_back(m++);
        G[to].push_back(m++);
    }

    bool BellmanFord(int &flow, int &cost) {
        FOR (i, 0, n + 1) d[i] = INF;
        memset(inq, 0, sizeof inq);
        d[s] = 0, a[s] = INF, inq[s] = true;
        queue<int> Q; Q.push(s);
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = false;
            for (int& idx: G[u]) {
                E &e = edges[idx];
                if (e.cp && d[e.to] > d[u] + e.v) {
                    d[e.to] = d[u] + e.v;
                    p[e.to] = idx;
                    a[e.to] = min(a[u], e.cp);
                    if (!inq[e.to]) {
                        Q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        if (d[t] == INF) return false;
        flow += a[t];
        cost += a[t] * d[t];
        int u = t;
        while (u != s) {
            edges[p[u]].cp -= a[t];
            edges[p[u] ^ 1].cp += a[t];
            u = edges[p[u]].from;
        }
        return true;
    }

    int go() {
        int flow = 0, cost = 0;
        while (BellmanFord(flow, cost)) dbg(flow, cost);
        return cost;
    }
} MM;

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T; scanf("%d", &T);
    while(T--) {
        int n, m, K, W; scanf("%d%d%d%d", &n, &m, &K, &W);
        int s = n*2+1, t = n*2+2;
        MM.init(t+1, s, t);
        while(m--) {
            int S, T, w, op; scanf("%d%d%d%d", &S, &T, &w, &op);
            if(op) {
                MM.addedge(S, T+n, 1, -w);
            } else {
                MM.addedge(S+n, T, 1, -w);
            }
        }
        for(int i = 1; i<n; ++i) {
            MM.addedge(i, i+1, K, 0);
            MM.addedge(i+n, i+n+1, K, 0);
        }
        for(int i = 2; i<n; ++i) {
            MM.addedge(i, i+n, K, W);
            MM.addedge(i+n, i, K, W);
        }
        MM.addedge(s, 1, K, 0); MM.addedge(1, n+1, K, 0);
        MM.addedge(n, t, K, 0); MM.addedge(n+n, n, K, 0);
        int ans = -MM.go();
        printf("%d\n", ans);
    }
    return 0;
}
