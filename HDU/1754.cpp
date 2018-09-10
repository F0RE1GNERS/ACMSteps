// [Auto Archived]
// Submit: 2016-10-11 18:59:00
// Time: 936MS
// Memory: 11796K

#include <bits/stdc++.h>
using namespace std;
#define LSON(i) ((i)*2)
#define RSON(i) ((i)*2+1)

struct Node {
    int left,right,val;
};

const int NEG_INF = -1e9;
const int nmax = 2e5+10;
const int root = 1;
int n,q,A[nmax],x,y;
char str[30];
Node tr[nmax<<2];

int build_tree(int o, int L, int R)
{
    tr[o].left = L;
    tr[o].right = R;
    if (L == R)
        return tr[o].val = A[L];
    int M = (L+R)/2;
    int X = build_tree(LSON(o),L,M);
    int Y = build_tree(RSON(o),M+1,R);
    return tr[o].val = max(X,Y);
}

int update(int o, int pos, int v)
{
    if (pos < tr[o].left || pos > tr[o].right)
        return NEG_INF;
    if (tr[o].left == tr[o].right)
        return tr[o].val = v;
    return tr[o].val = max(update(LSON(o),pos,v),update(RSON(o),pos,v));
}

int query(int o, int L, int R)
{
    if (R < tr[o].left || L > tr[o].right)
        return NEG_INF;
    if (L <= tr[o].left && R >= tr[o].right)
        return tr[o].val;
    return max(query(LSON(o),L,R),query(RSON(o),L,R));
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    std::ios::sync_with_stdio(false);
    while (~scanf("%d%d",&n,&q))
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d",&A[i]);
        memset(tr,0,sizeof(tr));
        build_tree(root,1,n);
        while (q--)
        {
            scanf("%s%d%d",str,&x,&y);
            if (str[0] == 'Q')
                printf("%d\n",query(root,x,y));
            else update(root,x,y);
        }
    }
    return 0;
}
