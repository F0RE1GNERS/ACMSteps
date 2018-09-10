// [Auto Archived]
// Submit: 2016-10-11 00:13:00
// Time: 280MS
// Memory: 2160K

#include <bits/stdc++.h>
using namespace std;

const int nmax = 1e5+10;
int C[nmax],M;
int A[nmax],n,kases,x,y;
char str[30];

int query(int pos)
{
    int ret = 0;
    while (pos)
    {
        ret += C[pos];
        pos -= (pos&-pos);
    }
    return ret;
}

int update(int pos, int v)
{
    while (pos <= M)
    {
        C[pos] += v;
        pos += (pos&-pos);
    }
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase)
    {
        scanf("%d",&n);
        for (int i = 1; i <= n; ++i)
            scanf("%d",&A[i]);
        memset(C,0,sizeof(C));
        M = n;
        for (int i = 1; i <= n; ++i)
            update(i,A[i]);
        printf("Case %d:\n",kase);
        while (~scanf("%s",str) && strcmp(str,"End") != 0)
        {
            scanf("%d%d",&x,&y);
            if (strcmp(str,"Query") == 0)
                printf("%d\n",query(y)-query(x-1));
            else {
                if (strcmp(str,"Add") == 0)
                    update(x,y);
                else update(x,-y);
            }
        }
    }
    return 0;
}