// [Auto Archived]
// Submit: 2016-10-04 21:53:37
// Time: 608MS
// Memory: 2076K

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6+10;
int t,n,m,q,ans;
int a[maxn],b[maxn];
int tt[maxn],ttsz;
int f[maxn];

void getFail(int *P, int* f, int psz) {
    f[0] = 0;
    f[1] = 0;
    for (int i = 1; i < psz; ++i)
    {
        int j = f[i];
        while (j && P[i]!=P[j]) j = f[j];
        f[i+1] = P[i]==P[j] ? j+1 : 0;
    }
}

void find(int* T, int* P, int *f, int tsz, int psz) {
    int j = 0;
    for (int i = 0; i < tsz; ++i)
    {
        while (j && P[j]!=T[i]) j = f[j];
        if (P[j] == T[i]) j++;
        if (j == psz) ++ans;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
#endif
    scanf("%d",&t);
    for (int testc = 1; testc <= t; ++testc)
    {
        scanf("%d%d%d",&n,&m,&q);
        for (int i = 0; i < n; ++i)
            scanf("%d",&a[i]);
        for (int i = 0; i < m; ++i)
            scanf("%d",&b[i]);
        ans = 0;
        b[m] = -1;
        getFail(b,f,m);
        for (int i = 0; i < q; ++i)
        {
            ttsz = 0;
            for (int j = i; j < n; j += q)
                tt[ttsz++] = a[j];
            tt[ttsz] = -1;
            find(tt,b,f,ttsz,m);
        }
        printf("Case #%d: %d\n",testc,ans);
    }
    return 0;
}
