// [Auto Archived]
// Submit: 2016-10-06 20:19:04
// Time: 0MS
// Memory: 5148K

#include <bits/stdc++.h>
using namespace std;

int kases,r,c,n,W,H,cp;
int x[300],y[300],w[300],h[300];
int subdis[300];
int vertex[300][300],vis[300][300];
long long ans[50000];

bool is_not_empty(int i, int j)
{
    return w[j]>1||h[i]>1||vertex[i][j]==0;
}

void flood_fill(int i, int j)
{
    vis[i][j] = cp;
    if (i+1 < H && !vis[i+1][j] && (w[j]>1||vertex[i+1][j]==0) && is_not_empty(i+1,j))
        flood_fill(i+1,j);
    if (i-1 >= 0 && !vis[i-1][j] && (w[j]>1||vertex[i][j]==0) && is_not_empty(i-1,j))
        flood_fill(i-1,j);
    if (j+1 < W && !vis[i][j+1] && (h[i]>1||vertex[i][j+1]==0) && is_not_empty(i,j+1))
        flood_fill(i,j+1);
    if (j-1 >= 0 && !vis[i][j-1] && (h[i]>1||vertex[i][j]==0) && is_not_empty(i,j-1))
        flood_fill(i,j-1);
}

int discrete(int *from, int *to, int max_len)
{
    memcpy(subdis,from,sizeof(subdis));
    subdis[n] = max_len;
    subdis[n+1] = 1;
    sort(subdis,subdis+n+2);
    int len = unique(subdis,subdis+n+2)-subdis;
    for (int i = 0; i < len-1; ++i)
        to[i] = subdis[i+1]-subdis[i];
    to[len-1] = 1;
    for (int i = 0; i < n; ++i)
        from[i] = lower_bound(subdis,subdis+len,from[i])-subdis;
    return len;
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase)
    {
        scanf("%d%d",&r,&c);
        scanf("%d",&n);
        for (int i = 0; i < n; ++i)
            scanf("%d%d",&x[i],&y[i]);
        memset(vertex,0,sizeof(vertex));
        memset(vis,0,sizeof(vis));
        memset(ans,0,sizeof(ans));
        memset(w,0,sizeof(w));
        memset(h,0,sizeof(h));
        H = discrete(x,h,r);
        W = discrete(y,w,c);
        cp = 0;
        for (int i = 0; i < n; ++i)
            vertex[x[i]][y[i]] = 1;
        // for (int i = 0; i < H; ++i)
        // {
        //     for (int j = 0; j < W; ++j)
        //         cout << vertex[i][j];
        //     cout << endl;
        // }
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                if (!vis[i][j] && is_not_empty(i,j))
                {
                    ++cp;
                    flood_fill(i,j);
                }
        for (int i = 0; i < H; ++i)
            for (int j = 0; j < W; ++j)
                ans[vis[i][j]] += (long long)h[i]*w[j]-vertex[i][j];
        printf("Case #%d:\n",kase);
        sort(ans+1,ans+cp+1);
        reverse(ans+1,ans+cp+1);
        while (cp > 0 && ans[cp] == 0) --cp;
        reverse(ans+1,ans+cp+1);
        printf("%d\n",cp);
        for (int i = 1; i <= cp; ++i)
            printf("%lld%c",ans[i],i==cp?'\n':' ');
    }
    return 0;
}