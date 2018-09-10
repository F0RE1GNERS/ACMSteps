// [Auto Archived]
// Submit: 2016-07-20 15:39:41
// Time: 280MS
// Memory: 1920K

#include <bits/stdc++.h>
using namespace std;

int mp[60][60],m,n,actid[60][60],mat[2700],vis[2700],ans,tot,t;
vector<int> g[2700];

int dirx[] = {-1,-2,-2,-1,1,2,2,1,-1,0,1,0};
int diry[] = {-2,-1,1,2,2,1,-1,-2,0,1,0,-1};

int ID(int x, int y)
{
    return x * m + y;
}

bool islegal(int x, int y)
{
    return (x >= 0 && x < n && y >= 0 && y < m);
}

int dfs(int u)
{
    for (int i = 0; i < g[u].size(); ++i)
    {
        int v = g[u][i];
        if (!vis[v])
        {
            vis[v] = 1;
            if (mat[v] == -1 || dfs(mat[v]))
            {
                mat[v] = u;
                mat[u] = v;
                return 1;
            }
        }
    }
    return 0;
}

void insert_edge(int u, int v)
{
    for (int i = 0; i < g[u].size(); ++i)
        if (g[u][i] == v)
            return ;
    g[u].push_back(v);
    g[v].push_back(u);
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    #endif
    while (scanf("%d%d",&n,&m) != EOF && n != 0 && m != 0)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                scanf("%d",&mp[i][j]);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                actid[i][j] = ID(i,j);
        tot = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (mp[i][j] != -1)
                {
                    ++tot;
                    int &uid = actid[i][j];
                    int ni,nj;
                    for (int k = 0; k < 12; ++k)
                        if ((1<<k) & mp[i][j])
                        {
                            ni = i+dirx[k];
                            nj = j+diry[k];
                            if (islegal(ni,nj) && mp[ni][nj] != -1)
                                insert_edge(uid,actid[ni][nj]);
                        }
                }
        ans = 0;
        memset(mat,-1,sizeof(mat));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (mp[i][j] != -1 && g[actid[i][j]].size() > 0)
                {
                    memset(vis,0,sizeof(vis));
                    if (mat[actid[i][j]] == -1 && dfs(actid[i][j]))
                        ++ans;
                }
        printf("%d. %d\n",(++t),ans);
        for (int i = 0; i < n*m; ++i)
            g[i].clear();
    }
    return 0;
}

