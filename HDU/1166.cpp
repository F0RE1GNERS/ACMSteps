// [Auto Archived]
// Submit: 2016-10-11 17:43:29
// Time: 265MS
// Memory: 9608K

#include <bits/stdc++.h>
using namespace std;
#define LSON(i) ((i)*2)
#define RSON(i) ((i)*2+1)

const int nmax = 5e5+10;
const int root = 1;
int kases,n,A[nmax],x,y;
char str[30];
int val[nmax<<2];

int build_tree(int o, int L, int R)
{
    if (L == R)
        return val[o] = A[L];
    int M = (L+R)/2;
    int x = build_tree(LSON(o),L,M);
    int y = build_tree(RSON(o),M+1,R);
    return (val[o] = x+y);
}

int update(int o, int L, int R, int pos, int v)
{
    if (pos < L || pos > R) return val[o];
    if (L == R && pos == L) return (val[o] = v);
    int M = (L+R)/2;
    int x = update(LSON(o),L,M,pos,v);
    int y = update(RSON(o),M+1,R,pos,v);
    return val[o] = x+y;
}

int query(int o, int L, int R, int ql, int qr)
{
    if (qr < L || ql > R) return 0;
    if (ql <= L && qr >= R) return val[o];
    int M = (L+R)/2;
    int x = query(LSON(o),L,M,ql,qr);
    int y = query(RSON(o),M+1,R,ql,qr);
    return x+y;
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
        memset(val,0,sizeof(val));
        build_tree(root,1,n);
        printf("Case %d:\n",kase);
        while (~scanf("%s",str) && strcmp(str,"End") != 0)
        {
            scanf("%d%d",&x,&y);
            if (strcmp(str,"Query") == 0)
                printf("%d\n",query(root,1,n,x,y));
            else {
                if (strcmp(str,"Add") == 0)
                    A[x] += y;
                else A[x] -= y;
                update(root,1,n,x,A[x]);
            }
        }
    }
    return 0;
}
