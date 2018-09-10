// [Auto Archived]
// Submit: 2016-10-11 00:01:45
// Time: 390MS
// Memory: 6468K

#include <bits/stdc++.h>
using namespace std;

const int nmax = 1e5+10;
struct Node {
    int left,right,val;
};
Node tr[nmax<<2];
int A[nmax],n,kases,x,y;
char str[30];
const int root = 1;

int build_tree(int x, int L, int R)
{
    tr[x].left = L;
    tr[x].right = R;
    if (L == R)
        return tr[x].val = A[L];
    int M = (L+R)/2;
    int X = build_tree(2*x,L,M);
    int Y = build_tree(2*x+1,M+1,R);
    return tr[x].val = X+Y;
}

int query(int x, int L, int R)
{
    if (R < tr[x].left || L > tr[x].right)
        return 0;
    if (L <= tr[x].left && R >= tr[x].right)
        return tr[x].val;
    int X = query(2*x,L,R);
    int Y = query(2*x+1,L,R);
    return X+Y;
}

int update(int x, int pos, int v)
{
    if (pos < tr[x].left || pos > tr[x].right)
        return tr[x].val;
    if (tr[x].left == tr[x].right && pos == tr[x].left)
        return tr[x].val = v;
    int X = update(2*x,pos,v);
    int Y = update(2*x+1,pos,v);
    return tr[x].val = X+Y;
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
        memset(tr,0,sizeof(tr));
        build_tree(root,1,n);
        printf("Case %d:\n",kase);
        while (~scanf("%s",str) && strcmp(str,"End") != 0)
        {
            scanf("%d%d",&x,&y);
            if (strcmp(str,"Query") == 0)
                printf("%d\n",query(root,x,y));
            else {
                if (strcmp(str,"Add") == 0)
                    A[x] += y;
                else A[x] -= y;
                update(root,x,A[x]);
            }
        }
    }
    return 0;
}