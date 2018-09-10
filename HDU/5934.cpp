// [Auto Archived]
// Submit: 2016-10-30 15:40:15
// Time: 187MS
// Memory: 11680K

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
vector<int> G[maxn],G2[maxn];
vector<int> S;
int vis[maxn],sccno[maxn],scc_cnt;
int scccost[maxn],sccidg[maxn];
int x[maxn],y[maxn],r[maxn],c[maxn];
int kases,n;
long long ans;

void dfs1(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = 0; i < G[u].size(); ++i)
        dfs1(G[u][i]);
    S.push_back(u);
}

void dfs2(int u) {
    if (sccno[u]) return;
    sccno[u] = scc_cnt;
    for (int i = 0; i < G2[u].size(); ++i)
        dfs2(G2[u][i]);
}

void find_scc(int n) {
    scc_cnt = 0;
    S.clear();
    memset(sccno,0,sizeof(sccno));
    memset(vis,0,sizeof(vis));
    for (int i = 0; i < n; ++i)
        dfs1(i);
    for (int i = n-1; i >= 0; --i)
        if (!sccno[S[i]]) {
            scc_cnt++;
            dfs2(S[i]);
        }
}

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++i)
            scanf("%d%d%d%d",&x[i],&y[i],&r[i],&c[i]);
        for (int i = 0; i < maxn; ++i) {
            G[i].clear();
            G2[i].clear();
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (j != i && 1LL*r[i]*r[i] >=
                    1LL*(x[j]-x[i])*(x[j]-x[i])+1LL*(y[j]-y[i])*(y[j]-y[i])) {
                    G[i].push_back(j);
                    G2[j].push_back(i);
                    //printf("%d %d\n",i,j);
                }
            }
        find_scc(n);
        memset(sccidg,0,sizeof(sccidg));
        ans = 0;
        // for (int i = 0; i < n; ++i)
        //     printf("%d\n",sccno[i]);
        for (int i = 1; i <= scc_cnt; ++i)
            scccost[i] = 1e9;
        for (int i = 0; i < n; ++i)
            scccost[sccno[i]] = min(scccost[sccno[i]],c[i]);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < G[i].size(); ++j)
                if (sccno[i] != sccno[G[i][j]])
                    sccidg[sccno[G[i][j]]]++;
        for (int i = 1; i <= scc_cnt; ++i)
            if (sccidg[i] == 0)
                ans += scccost[i];
        printf("Case #%d: %lld\n",kase,ans);
    }
    return 0;
}