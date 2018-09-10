// [Auto Archived]
// Submit: 2018-07-30 13:45:18
// Time: 4040MS
// Memory: 269328K

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

const int N = 1e7+10;

int fa[N], hi[N], a[N];

int head[N], nxt[N], val[N], cnt;

void add(int u, int v) {
    nxt[cnt] = head[u];
    val[cnt] = v;
    head[u] = cnt++;
}

int Fa(int x) {
    int u = x;
    while(fa[u]!=u) {
        u = fa[u];
    }
    while(x!=u) {
        int t = fa[x];
        fa[x] = u;
        x = t;
    }
    return u;
}

int p, q, r, MOD;

int NEXT(int last, int pos) {
    return (1LL*p*last+1LL*q*pos+r)%MOD;
}

int stk[N], pos[N], top;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m, k;
        scanf("%d%d%d%d%d%d%d", &n, &m, &k, &p, &q, &r, &MOD);
        iota(fa+1, fa+n+2, 1); top = 0; hi[n+1] = 0; cnt = 1;
        fill(head, head+n+2, 0);
        for(int i = 1; i<=k; ++i) scanf("%d", a+i);
        for(int i = k+1; i<=n; ++i) a[i] = NEXT(a[i-1], i);
        for(int i = n; i>=1; --i) {
            while(top>0 && a[i]>=stk[top-1]) --top;
            int tr;
            if(top==0) {
                tr = n+1;
            } else {
                tr = pos[top-1];
            }
            pos[top] = i; stk[top++] = a[i];
            hi[i] = hi[tr]+1;
            add(tr, i);
        }
        for(int i = 1; i<m; ++i) {
            for(int e = head[i]; e>0; e = nxt[e]) {
                fa[Fa(val[e])] = i;
            }
        }
        LL A = 0, B = 0;
        for(int i = m; i<=n; ++i) {
            for(int e = head[i]; e>0; e = nxt[e]) {
                fa[Fa(val[e])] = i;
            }
            int tar = Fa(i-m+1);
            int ma = a[tar];
            int cnt = hi[i-m+1]-hi[tar]+1;
            dbg(i, ma, cnt);
            A+=ma^(i-m+1);
            B+=cnt^(i-m+1);
        }
        printf("%lld %lld\n", A, B);
    }
    return 0;
}