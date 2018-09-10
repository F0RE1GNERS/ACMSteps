// [Auto Archived]
// Submit: 2018-08-13 13:47:12
// Time: 982MS
// Memory: 49480K

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

namespace io {
    bool negative;
    bool ok = true;
    char ch;
    
    inline char next_char() {
        static char buf[65536], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 65536, stdin), p1 == p2) ? EOF : *p1++;
    }
     
    inline bool maybe_digit(char c)
    {
        return c >= '0' && c <= '9';
    }
     
    template<typename T>
    inline bool rn(T& _v) {
        negative = false;
        _v = 0;
        while (!maybe_digit(ch = next_char()) && ch != EOF) { negative = ch == '-'; };
        if (ch == EOF)return false;
        do {
            _v = (_v << 1) + (_v << 3) + ch - '0';
        } while (maybe_digit(ch = next_char()));
        if (negative) _v = -_v;
        return true;
    }
     
    template <typename T>
    inline void o(T p)
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
    
    template <typename T>
    inline void oln(T p)
    {
        o(p); putchar('\n');
    }
}

using namespace io;

const int N = 5e5+10;
const int INF = 1e9+7;

typedef pair<int, int> P;
typedef pair<int, P> PP;

vector<PP> E[N];
vector<int> G[N];

set<P> S;

int fa[N], nx, n, m, d[N];
bool inq[N];

int Fa(int x) {
    return fa[x]==x?x:(fa[x] = Fa(fa[x]));
}

int q[N];

bool BF() {
    static int head, tail;
    memset(inq, 0, sizeof(inq[0])*(nx+1));
    d[1] = 0; inq[1] = true; q[head = 0] = 1; tail = 1;
    while(head<tail) {
        int u = q[head++];
        for(auto v: G[u]) {
            if(!inq[v]) {
                d[v] = d[u]+1;
                inq[v] = true;
                q[tail++] = v;
            }
            if(v==n) break;
        }
    }
    return inq[n];
}

void add_edge(int u, int v) {
    //P p(min(u, v), max(u, v));
    //if(S.find(p)==S.end()) {
    //    S.insert(p);
        G[u].push_back(v);
        G[v].push_back(u);
    //}
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    while(rn(n) && rn(m)) {
        iota(fa+n+1, fa+n+m+1, n+1); S.clear(); nx = n+m;
        for(int i = 1; i<=m; ++i) {
            int u, v, w; rn(u); rn(v); rn(w);
            E[u].emplace_back(w, P(v, n+i));
            E[v].emplace_back(w, P(u, n+i));
        }
        for(int i = 1; i<=n; ++i) {
            sort(E[i].begin(), E[i].end());
            for(int j = 0, k, sz = E[i].size(); j+1<sz; ) {
                int id = Fa(E[i][j].second.second);
                for(k = j+1; k<sz && E[i][j].first==E[i][k].first; ++k) {
                    int an = Fa(E[i][k].second.second);
                    if(an!=id) fa[an] = id;
                }
                j = k;
            }
        }
        for(int i = 1; i<=n; ++i) {
            for(auto e: E[i]) {
                add_edge(i, Fa(e.second.second));
            }
        }
        if(!BF()) {
            puts("-1");
        } else {
            printf("%d\n", d[n]/2);
        }
        for(int i = 1; i<=n; ++i) E[i].clear();
        for(int i = 1; i<=nx; ++i) G[i].clear();
    }
    return 0;
}