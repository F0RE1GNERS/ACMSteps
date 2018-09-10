// [Auto Archived]
// Submit: 2018-08-13 12:43:11
// Time: 655MS
// Memory: 1584K

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

const int MOD = 1e9+7;

struct Mat {
    static const LL M = 3;
    LL v[M][M];
    Mat() { memset(v, 0, sizeof v); }
    void eye() { FOR (i, 0, M) v[i][i] = 1; }
    LL* operator [] (LL x) { return v[x]; }
    const LL* operator [] (LL x) const { return v[x]; }
    Mat operator * (const Mat& B) {
        const Mat& A = *this;
        Mat ret;
        FOR (i, 0, M)
            FOR (j, 0, M)
                 FOR (k, 0, M)
                      ret[i][j] = (ret[i][j] + A[i][k] * B[k][j]) % MOD;
        return ret;
    }
    Mat pow(LL n) const {
        Mat A = *this, ret; ret.eye();
        for (; n; n >>= 1, A = A * A)
            if (n & 1) ret = ret * A;
        return ret;
    }
    Mat operator + (const Mat& B) {
        const Mat& A = *this;
        Mat ret;
        FOR (i, 0, M)
            FOR (j, 0, M)
                 ret[i][j] = (A[i][j] + B[i][j]) % MOD;
        return ret;
    }
    void prt() const {
        FOR (i, 0, M)
            FOR (j, 0, M)
                 printf("%lld%c", (*this)[i][j], j == M - 1 ? '\n' : ' ');
    }
};

Mat a, b;

const int N = 1e6;

int tr[N], ct;

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T; scanf("%d", &T);
    FOR(cas, 1, T+1) {
        int A, B, C, D, P, n;
        scanf("%d%d%d%d%d%d", &A, &B, &C, &D, &P, &n);
        if(n<=2) {
            printf("%d\n", n==1?A:B);
            continue;
        }
        ct = 0;
        for(int i = P; i>0; ) {
            tr[ct++] = P/i;
            i = P/(P/i+1);
        }
        //FOR(i, 0, ct) dbg(i, tr[i]);
        dbg(ct);
        a[0][0] = A; a[0][1] = B; a[0][2] = 1;
        b[1][0] = 1;
        b[0][1] = C; b[1][1] = D; /*b[2][1]*/
        b[2][2] = 1;
        static int t; t = 0;
        for(int i = 3; i<=n; ) {
            int x = P/i;
            int nxt = x==0?n+1:(x==1?P+1:(*lower_bound(tr, tr+ct, i))+1);
            int step = min(nxt, n+1)-i;
            //dbg(i, x, nxt, step);
            b[2][1] = x;
            a = a*b.pow(step);
            i += step;
            //if(++t==100)break;
        }
        printf("%d\n", a[0][1]);
    }
    return 0;
}