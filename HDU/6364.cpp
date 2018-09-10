// [Auto Archived]
// Submit: 2018-08-08 16:12:16
// Time: 889MS
// Memory: 56228K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "DEBUG: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
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
 
template <typename T>
inline void rn(T& _v)
{
    negative = false;
    _v = 0;
    while (!maybe_digit(ch))
    {
        negative = ch == '-';
        ch = next_char();
    }
    do
    {
        _v = (_v << 1) + (_v << 3) + ch - '0';
    } while (maybe_digit(ch = next_char()));
    if (negative) _v = -_v;
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

const int N = 1E6+10;

int a[N], b[N], c[N];
LL g[N], f[N];
int n, l, m; 

inline int ID(int x) {
    return lower_bound(c, c+m, x)-c+1;
}

typedef pair<int, int> P;

LL L[2], R[2], D[N*2][2];

int main() {
    #ifdef zerol
    freopen("in", "r", stdin);
    #endif
    
    int T; rn(T);
    while (T--) {
        memset(f, 0, sizeof(f));
        memset(g, 0, sizeof(g));
        memset(D, 0, sizeof(D));
        rn(n); rn(l); m = 0;
        FOR(i, 0, n) rn(a[i]);
        FOR(i, 0, n) rn(b[i]);
        
        for(int p = 0, q = 0; p<n || q<n; ) {
            int t = p<n?a[p]:b[q];
            if(q<n && b[q]<t) t = b[q];
            c[m] = t; ++m; f[m] = f[m-1];
            while(p<n && a[p] == t) {
                ++p;
                ++f[m];
            }
            while(q<n && b[q] == t) {
                ++q;
                --f[m];
            }
        }
        c[m] = c[0]+l;
        L[0] = L[1] = R[0] = R[1] = 0;
        FOR(i, 1, m+1) {
            g[i] = f[i] * (c[i]-c[i-1]); dbg(c[i-1], f[i], g[i]);
            D[N+f[i]][0]+=c[i]-c[i-1];
            D[N+f[i]][1]+=g[i];
            L[0]+=c[i]-c[i-1];
            L[1]+=g[i];
        }
        LL ans = 1E18, cur;
        FOR(level, -n, n+1) {
            cur = (R[0]*level - R[1]) + (L[1] - level*L[0]);
            if(cur<ans) ans = cur; dbg(cur);
            LL x = D[N+level][0], y = D[N+level][1];
            L[0]-=x;
            L[1]-=y;
            R[0]+=x;
            R[1]+=y;
        }
        o(ans); putchar('\n');
    }
    return 0;
}
