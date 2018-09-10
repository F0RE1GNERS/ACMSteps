// [Auto Archived]
// Submit: 2016-10-12 17:41:11
// Time: 904MS
// Memory: 7860K

#include <bits/stdc++.h>
using namespace std;
#define LSON(i) ((i)*2)
#define RSON(i) ((i)*2+1)
typedef long long ll;
typedef pair<int,int> Interval;

struct Node {
    int left,right,sum,setval;
};

const int nmax = 1e5+10;
int n,q,A[nmax],x,y,z,kases;
ll Asum[nmax];

struct SegmentTree {
    Node tr[nmax<<2];
    const int root = 1;

    int build_tree(int o, int L, int R)
    {
        tr[o].left = L;
        tr[o].right = R;
        tr[o].setval = -1;
        if (L < R)
        {
            int M = (L+R)/2;
            int X = build_tree(LSON(o),L,M);
            int Y = build_tree(RSON(o),M+1,R);
            return tr[o].sum = X+Y;
        } else {
            return tr[o].sum = 1;
        }
    }

    void init(int n)
    {
        memset(tr,0,sizeof(tr));
        for (int i = 0; i < ((n+5)<<2); ++i)
            tr[i].setval = -1;
        build_tree(root,1,n);
    }

    void maintain(int o)
    {
        if (tr[o].setval >= 0)
            tr[o].sum = tr[o].setval * (tr[o].right - tr[o].left + 1);
        else if (tr[o].left < tr[o].right)
            tr[o].sum = tr[LSON(o)].sum + tr[RSON(o)].sum;
    }

    void pushdown(int o)
    {
        int lson = LSON(o), rson = RSON(o);
        if (tr[o].setval >= 0) {
            tr[lson].setval = tr[rson].setval = tr[o].setval;
            tr[o].setval = -1;
        }
    }

    void update(int o, int L, int R, int val)
    {
        if (L <= tr[o].left && R >= tr[o].right)
            tr[o].setval = val;
        else {
            pushdown(o);
            int M = (tr[o].left + tr[o].right) / 2;
            if (L <= M) update(LSON(o),L,R,val);
            else maintain(LSON(o));
            if (R > M) update(RSON(o),L,R,val);
            else maintain(RSON(o));
        }
        maintain(o);
        //printf("%d %d %d\n",tr[o].left,tr[o].right,tr[o].sum);
    }

    int query(int o, int L, int R)
    {
        if (tr[o].setval >= 0)
            return tr[o].setval * (min(tr[o].right,R)-max(tr[o].left,L));
        else if (L <= tr[o].left && R >= tr[o].right)
            return tr[o].sum;
        else {
            int M = (tr[o].left + tr[o].right) / 2;
            int retsum = 0;
            if (L <= M) retsum += query(LSON(o),L,R);
            if (R > M) retsum += query(RSON(o),L,R);
            return retsum;
        }
    }

    void update(int L, int R, int val) { update(root,L,R,val); }
    int query(int L, int R) { return query(root,L,R); }
};

SegmentTree st;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase)
    {
        scanf("%d%d",&n,&q);
        st.init(n);
        while (q--)
        {
            scanf("%d%d%d",&x,&y,&z);
            st.update(x,y,z);
        }
        printf("Case %d: The total value of the hook is %d.\n",kase,st.query(1,n));
    }
    return 0;
}
