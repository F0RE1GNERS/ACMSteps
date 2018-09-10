// [Auto Archived]
// Submit: 2016-10-12 20:29:15
// Time: 46MS
// Memory: 1624K

#include <bits/stdc++.h>
using namespace std;

const int nmax = 6000;
int tmp[nmax],a[nmax],b[nmax],n,ret,ans;

int inverse_num(int *A, int p, int q)
{
    if (p == q)
        return 0;
    int m = (p+q)/2;
    int ret = inverse_num(A,p,m)+inverse_num(A,m+1,q);
    int p1 = p, p2 = m+1;
    for (int p3 = 0; p3 <= q-p; ++p3)
    {
        if (p1 <= m && p2 <= q)
        {
            if (A[p1] > A[p2])
            {
                tmp[p3] = A[p2];
                p2++;
            }
            else {
                tmp[p3] = A[p1];
                ret += p2-m-1;
                p1++;
            }
        }
        else if (p2 > q)
        {
            tmp[p3] = A[p1];
            ret += q-m;
            p1++;
        }
        else
        {
            tmp[p3] = A[p2];
            p2++;
        }
    }
    memcpy(A+p,tmp,sizeof(int)*(q-p+1));
    return ret;
}

// int inverse_num_2(int *A, int p, int q)
// {
//     int ret = 0;
//     for (int i = p; i <= q; ++i)
//         for (int j = i+1; j <= q; ++j)
//             if (A[i] > A[j])
//                 ret++;
//     return ret;
// }

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    while (~scanf("%d",&n))
    {
        ans = 1e9+7;
        for (int i = 0; i < n; ++i)
            scanf("%d",&a[i]);
        memcpy(b,a,sizeof(a));
        ans = inverse_num(b,0,n-1);
        //int ans2 = inverse_num_2(a,0,n-1);
        //printf("%d %d\n",ans,ans2);
        ret = ans;
        for (int i = 0; i < n; ++i)
        {
            ret -= a[i];
            ret += n-1-a[i];
            if (ans > ret)
                ans = ret;
        }
        printf("%d\n",ans);
    }
    return 0;
}
