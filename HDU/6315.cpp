// [Auto Archived]
// Submit: 2018-07-25 12:39:03
// Time: 702MS
// Memory: 5404K

#include <bits/stdc++.h>
 
//#undef zerol

using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cerr << "Debug: " << #args << " -> "; err(args); } while (0)
#define fuck(x) do { printf("fuck@%d\n", x); } while(0)
#else
#define dbg(...)
#define fuck(...)
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

#define lc(x) ((x)*2)
#define rc(x) ((x)*2+1)

const int N = 4e5+10;

struct BIT {
    
    int a[N];
    
    void reset() {
        memset(a, 0, sizeof(a));
    }
    
    void add(int p, int x) {
        while(p<N) {
            a[p]+=x;
            p+=p&-p;
        }
    }
    
    int sum(int p) {
        int ret = 0;
        while(p>0) {
            ret+=a[p];
            p&=p-1;
        }
        return ret;
    }
} bit;

int b[N];

int val[N], tag[N];

void up(int p) {
    val[p] = min(val[lc(p)], val[rc(p)]);
}

void down(int p) {
    if(tag[p]!=0) {
        val[lc(p)]+=tag[p]; tag[lc(p)]+=tag[p];
        val[rc(p)]+=tag[p]; tag[rc(p)]+=tag[p];
        tag[p] = 0;
    }
}

void build(int p, int l, int r) {
    tag[p] = 0;
    if(l==r) {
        val[p] = b[l];
        return;
    }
    int mid = l+r>>1;
    build(lc(p), l, mid);
    build(rc(p), mid+1, r);
    up(p);
}

void work(int p, int l, int r, int ql, int qr) {
    if(ql<=l && r<=qr) {
        --val[p];
        --tag[p];
        return;
    }
    int mid = l+r>>1;
    down(p);
    if(ql<=mid) work(lc(p), l, mid, ql, qr);
    if(qr>mid) work(rc(p), mid+1, r, ql, qr);
    up(p);
}

void fix(int p, int l, int r) {
    if(val[p]>0) return;
    if(l==r) {
        //dbg("fix", l);
        val[p] = b[l];
        bit.add(l, 1);
        return;
    }
    int mid = l+r>>1;
    down(p);
    fix(lc(p), l, mid);
    fix(rc(p), mid+1, r);
    up(p);
}

int main() {
    int n, q;
    while(~scanf("%d%d", &n, &q)) {
        for(int i = 1; i<=n; ++i) scanf("%d", b+i);
        bit.reset();
        build(1, 1, n);
        static char op[10]; int l, r;
        while(q--) {
            scanf("%s%d%d", op, &l, &r);
            if(op[0]=='a') {
                work(1, 1, n, l, r);
                fix(1, 1, n);
            } else {
                printf("%d\n", bit.sum(r)-bit.sum(l-1));
            }
        }
    }
    return 0;
}