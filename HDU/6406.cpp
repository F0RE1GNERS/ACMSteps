// [Auto Archived]
// Submit: 2018-08-15 12:33:08
// Time: 202MS
// Memory: 9848K

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

typedef pair<int, int*> P;

const int N = 1e5+10;

int a[N], b[N], top, ans[N], ct[N];

vector<P> Q[N];

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T; rn(T);
    while(T--) {
        int n, m; rn(n), rn(m);
        for(int i = 0; i<n; ++i) rn(a[i]);
        for(int i = 0; i<m; ++i) {
            int p, q; rn(p); rn(q);
            Q[p-1].emplace_back(q, ans+i);
        }
        for(int i = 0; i<n; ++i)
            for(auto pr: Q[i]) dbg(i, pr.first);
        int h = 0, c = 0;
        for(int i = 0; i<n; ++i) {
            for(auto &pr: Q[i]) {
                if(pr.first<=h) {
                    pr.first = h;
                    *pr.second = c;
                } else {
                    *pr.second = c+1;
                }
            }
            if(a[i]>h) {
                h = a[i];
                ++c;
            }
        }
        for(int i = 0; i<n; ++i)
            for(auto pr: Q[i]) dbg(i, pr.first);
        top = 0;
        for(int i = n-1; i>=0; --i) {
            FOR(j, 0, top) dbg(j, b[j]);
            for(auto pr: Q[i]) {
                auto p = lower_bound(b, b+top, pr.first, greater<int>());
                *pr.second += p-b;
            }
            while(top>0 && a[i]>=b[top-1]) --top;
            b[top++] = a[i];
        }
        for(int i = 0; i<m; ++i) printf("%d\n", ans[i]);
        for(int i = 0; i<n; ++i) Q[i].clear();
    }
    return 0;
}