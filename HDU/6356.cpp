// [Auto Archived]
// Submit: 2018-08-06 12:57:38
// Time: 2433MS
// Memory: 15476K

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

#define rand sdfjsdkljfs

struct Rand {
    unsigned x, y, z;
    unsigned gen() {
        x = x ^ (x<<11);
        x = x ^ (x>>4);
        x = x ^ (x<<5);
        x = x ^ (x>>14);
        unsigned w = x^(y^z);
        x = y;
        y = z;
        z = w;
        return z;
    }
    void reset() {
        scanf("%u%u%u", &x, &y, &z);
    }
} rand;

template <typename T>
void o(T p)
{
    static int stk[70], tp;
    if (p == 0)
    {
        putchar('0');
        return;
    }
    if (p < 0)
    {
        p = -p;
        putchar('-');
    }
    while (p) stk[++tp] = p % 10, p /= 10;
    while (tp) putchar(stk[tp--] + '0');
}

typedef pair<int, int> P;

const unsigned MASK = (1<<30)-1;

const int N = 1e5+10;
const int M = 18;

P a[N][M];

void up(P& p, const P& q) {
    if(q.second>p.second) p = q;
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m; scanf("%d%d", &n, &m); rand.reset();
        fill(a[0], a[n+1]+M, P(m, 0));
        for(int i = m-1; i>=0; --i) {
            int l = rand.gen()%n+1, r = rand.gen()%n+1, v = rand.gen()&MASK;
            //dbg(l, r, v);
            if(l>r) swap(l, r);
            int t = r-l+1, tt = 0;
            tt = 31 - __builtin_clz(t); t = 1<<tt;
            P x = P(i, v);
            up(a[l][tt], x);
            up(a[r-t+1][tt], x);
        }
        fuck(0);
        for(int i = M-1; i>0; --i) {
            int t = (1<<i-1);
            for(int j = 1; j<=n; ++j) {
                //dbg(i, j, a[j][i].first, a[j][i].second);
                up(a[j][i-1], a[j][i]);
                if(j+t<=n) up(a[j+t][i-1],a[j][i]);
            }
        }
        __int128 ans = 0, t;
        for(int i = 1; i<=n; ++i) {
            t = a[i][0].second;
            ans ^= i*t; 
        }
        o(ans); puts("");
    }
    return 0;
}