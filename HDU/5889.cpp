// [Auto Archived]
// Submit: 2016-09-17 20:10:24
// Time: 15MS
// Memory: 2288K

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from,to,cap,flow;
    Edge(int u=0, int v=0, int c=0, int f=0)
        :from(u),to(v),cap(c),flow(f) { }
};

int n,m,u,v,w,esz;
Edge edges[22000];
vector<int> g[3000],h[3000];
int a[3000];
int p[3000];
int dis[3000];
int vis[3000];

int max_flow(int s, int t)
{
    int flow = 0;
    for (;;) {
        memset(a,0,sizeof(a));
        queue<int> Q;
        Q.push(s);
        a[s] = 1e9+7;
        while (!Q.empty())
        {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < g[x].size(); ++i)
            {
                Edge &e = edges[g[x][i]];
                if (!a[e.to] && e.cap > e.flow)
                {
                    p[e.to] = g[x][i];
                    a[e.to] = min(a[x],e.cap-e.flow);
                    Q.push(e.to);
                }
            }
            if (a[t]) break;
        }
        if (!a[t]) break;
        for (int u = t; u != s; u = edges[p[u]].from)
        {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
        }
        flow += a[t];
    }
    return flow;
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    int t;
    scanf("%d",&t);
    while ((t--) && (~scanf("%d%d",&n,&m)))
    {
        for (int i = 0; i <= n; ++i)
        {
            h[i].clear();
            g[i].clear();
        }
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d%d",&u,&v,&w);
            edges[2*i] = Edge(u,v,w,0);
            edges[2*i+1] = Edge(v,u,w,0);
            h[u].push_back(2*i);
            h[v].push_back(2*i+1);
        }

        queue<int> q;
        memset(vis,0,sizeof(vis));
        memset(dis,-1,sizeof(dis));
        q.push(1);
        dis[1] = 0;
        vis[1] = 1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < h[u].size(); ++i)
            {
                Edge &e = edges[h[u][i]];
                if (!vis[e.to])
                {
                    vis[e.to] = 1;
                    dis[e.to] = dis[u] + 1;
                    q.push(e.to);
                }
            }
        }

        // for (int i = 1; i <= n; ++i)
        //     printf("%d ",dis[i]);
        // printf("\n");
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j < h[i].size(); ++j)
            {
                Edge &e = edges[h[i][j]];
                if (dis[e.to] != -1 && dis[e.to] == dis[i] + 1)
                {
                    //printf("(%d,%d),",e.from,e.to);
                    g[e.from].push_back(h[i][j]);
                    //g[e.to].push_back(h[i][j]^1);
                }
            }
        //printf("\n");
        // q.push(1);
        // memset(vis,0,sizeof(vis));
        // while (!q.empty())
        // {
        //     int u = q.front();
        //     q.pop();
        //     for (int i = 0; i < h[u].size(); ++i)
        //     {
        //         Edge &e = edges[h[u][i]];
        //         if (!vis[h[u][i]] && dis[e.to] != -1 && dis[e.to] == dis[u] + 1)
        //         {
        //             q.push(e.to);
        //             vis[h[u][i]] = 1;
        //             vis[h[u][i]^1] = 1;
        //             g[e.from].push_back(h[u][i]);
        //             g[e.to].push_back(h[u][i]^1);
        //         }
        //     }
        // }

        printf("%d\n",max_flow(1,n));
    }
    return 0;
}