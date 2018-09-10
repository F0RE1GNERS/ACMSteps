// [Auto Archived]
// Submit: 2016-10-04 22:11:15
// Time: 15MS
// Memory: 1572K

#include <bits/stdc++.h>
using namespace std;

int t,n,a[200],ans[20],cnt;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("main.txt","r",stdin);
    #endif
    scanf("%d",&t);
    ans[1] = 0;
    ans[2] = 0;
    for (int tes = 3; tes <= 20; ++tes)
    {
        memset(a,0,sizeof(a));
        a[0] = 1;
        a[1] = 2;
        cnt = 2;
        for (int i = 2; i <= tes; ++i)
        {
            if (a[cnt-1]+a[cnt-2] <= i)
                a[cnt++] = i;
        }
        ans[tes] = tes-cnt;
        //printf("%d %d\n",tes,ans[tes]);
    }
    for (int testc = 1; testc <= t; ++testc)
    {
        scanf("%d",&n);
        printf("Case #%d: %d\n",testc,ans[n]);
    }
    return 0;
}