// [Auto Archived]
// Submit: 2016-10-04 20:57:52
// Time: 187MS
// Memory: 1668K

#include <bits/stdc++.h>
using namespace std;

int n,t,k;
int p[15000],ans[15000];
int anscnt;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
#endif
    scanf("%d",&t);
    for (int testc = 1; testc <= t; ++testc)
    {
        memset(p,0,sizeof(p));
        anscnt = 0;
        scanf("%d%d",&n,&k);
        for (int i = 1; i <= k; ++i)
        {
            ans[anscnt++] = 2*i;
            p[2*i] = 1;
        }
        for (int i = 1; i <= n; ++i)
            if (!p[i]) ans[anscnt++] = i;
        printf("Case #%d: ",testc);
        for (int i = 0; i < n; ++i)
            printf("%d%c",ans[i],i==n-1?'\n':' ');
    }
    return 0;
}
