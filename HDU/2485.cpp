// [Auto Archived]
// Submit: 2017-11-18 19:25:58
// Time: 109MS
// Memory: 2180K

#include <bits/stdc++.h>
using namespace std;

const int maxn = 200;
const int INF = 1e9;

struct Edge {
    Edge() {}

    Edge(int from, int to, int cap, int flow) : from(from), to(to), cap(cap), flow(flow) {}

    int from, to, cap, flow;
};

struct Dinic {
    int n, m, s, t;
    vector <Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];

    void init(int n, int s, int t) {
        this->n = n, this->s = s, this->t = t;
        for (int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = true;
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < (int) G[x].size(); i++) {
                Edge &e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = true;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x, int a) {
        if (x == t || a == 0)return a;
        int flow = 0, f;
        for (int &i = cur[x]; i < (int) G[x].size(); i++) {
            Edge &e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }

    int Maxflow() {
        int flow = 0;
        while (BFS()) {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
} DC;

int n, m, K;
int mat[maxn][maxn];
int active[maxn][maxn];

int main() {
    cin.tie(0);
    while (cin >> n >> m >> K && n + m + K > 0) {
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                mat[i][j] = i == j ? 0 : INF;
        memset(active, 0, sizeof active);
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            mat[u][v] = 1;
            active[u][v] = 1;
        }
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
        DC.init(2 * n + 10, 2 * 1 + 1, 2 * n);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j) {
                if (i == j) continue;
                if (mat[1][i] + mat[i][j] + mat[j][n] <= K && active[i][j]) {
                    // printf("%d %d\n", i, j);
                    DC.AddEdge(2 * i + 1, 2 * j, INF);
                }
            }
        for (int i = 1; i <= n; ++i)
            DC.AddEdge(2 * i, 2 * i + 1, 1);
        cout << DC.Maxflow() << endl;
    }
}