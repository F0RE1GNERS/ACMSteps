// [Auto Archived]
// Submit: 2018-07-23 12:56:55
// Time: 1185MS
// Memory: 6492K

#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cerr << "Debug: " << #args << " -> "; err(args); } while (0)
#define fuck(x) do { printf("fuck@%d\n", x); } while(0)
#else
#define dbg(...)
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

using namespace std;

typedef pair<int, int> P;

const int N = 1e5+10;

int a[N];

P b[N], e[N];

multiset<int> S;

int c[N], cnt[N];

int d[N];

void add(int p, int v) {
    while(p<N) {
        d[p]+=v;
        p+=p&-p;
    }
}

int find() {
    int p = 1<<16, ans = 0;
    while(p>0) {
        if(d[ans+p]==p) ans+=p;
        p>>=1;
    }
    return ans+1;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        memset(cnt, 0, sizeof(cnt));
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 0; i<m; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            b[i] = P(x, y);
            e[i] = P(y, x);
        }
        sort(b, b+m);
        sort(e, e+m);
        int p = 0, q = 0, last = 1;
        for(int i = 1; i<=n; ++i) {
            while(p<m && b[p].first==i) {
                S.insert(i);
                ++p;
            }
            a[i] = find();
            if(++cnt[a[i]]==1) {
                add(a[i], 1);
            }
            while(q<m && e[q].first==i) {
                S.erase(S.find(e[q].second));
                ++q;
            }
            int nxt = S.size()==0? i+1: *S.begin();
            while(last<nxt) {
                if(--cnt[a[last]]==0) add(a[last], -1);
                ++last;
            }
        }
        for(int i = 1; i<=n; ++i) printf("%d%c", a[i], i==n?'\n':' ');
        //fuck(0);
    }
    return 0;
}