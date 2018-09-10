// [Auto Archived]
// Submit: 2016-10-30 15:04:51
// Time: 31MS
// Memory: 1736K

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from,to,cap,flow;
};

const int maxn = 2000;
const int divide = 990;
vector<Edge> edges;
vector<int> g[maxn];
int kases,n,s;
int a[maxn],p[maxn];
const int INF = 1e9;

void addEdge(int from, int to, int cap) {
    //printf("%d %d %d\n",from,to,cap);
    edges.push_back((Edge){from,to,cap,0});
    edges.push_back((Edge){to,from,0,0});
    int m = edges.size();
    g[from].push_back(m-2);
    g[to].push_back(m-1);
}

int max_flow(int s, int t) {
    int ret = 0;
    for (;;) {
        memset(a,0,sizeof(a));
        a[s] = INF;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < g[u].size(); ++i) {
                Edge &e = edges[g[u][i]];
                if (!a[e.to] && e.flow < e.cap) {
                    a[e.to] = min(e.cap-e.flow,a[u]);
                    q.push(e.to);
                    p[e.to] = g[u][i];
                }
            }
            if (a[t]) break;
        }
        if (!a[t]) break;
        for (int u = t; u != s; u = edges[p[u]].from) {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
        }
        ret += a[t];
    }
    return ret;
}

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase) {
        scanf("%d%d",&n,&s);
        printf("Case #%d: ",kase);
        if (s == 0)
            printf("Yes\n");
        else {
            if (s < n) {
                int tmp = n;
                n = s;
                s = tmp;
            }
            if (n >= 890)
                printf("No\n");
            else {
                for (int i = 0; i < maxn; ++i)
                    if (!g[i].empty()) g[i].clear();
                edges.clear();
                for (int i = 1; i <= n; ++i)
                    for (int j = 1; j <= n; ++j)
                        if ((s + j) % i == 0)
                            addEdge(i,j+900,1);
                for (int i = 1; i <= n; ++i) {
                    addEdge(0,i,1);
                    addEdge(i+900,1900,1);
                }
                if (max_flow(0,1900) == n)
                    printf("Yes\n");
                else printf("No\n");
            }
        }
    }
    return 0;
}