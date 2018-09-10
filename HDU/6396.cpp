// [Auto Archived]
// Submit: 2018-08-13 14:04:44
// Time: 405MS
// Memory: 9320K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
inline char next_char() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
inline bool maybe_digit(char c) {
    return c >= '0' && c <= '9';
}
template <typename T>
void rn(T& _v) {
    static char ch;
    static bool negative = false;
    _v = 0;
    while (!maybe_digit(ch)) {
        negative = ch == '-';
        ch = next_char();
    }
    do _v = (_v << 1) + (_v << 3) + ch - '0';
    while (maybe_digit(ch = next_char()));
    if (negative) _v = -_v;
}

template <typename T>
void o(T p) {
    static int stk[70], tp;
    if (p == 0) {
        putchar('0');
        return;
    }
    if (p < 0) { p = -p; putchar('-'); }
    while (p) stk[++tp] = p % 10, p /= 10;
    while (tp) putchar(stk[tp--] + '0');
}
// -----------------------------------------------------------------------------
const int N = 1E5 + 100, K = 5 + 2;
int a[N][K], b[N][K];
int f[K][N];
struct cmp {
    int k;
    bool operator () (const int& x, const int& y) { return a[x][k] < a[y][k]; }
};
int cur[K], p[K], cnt[N];
int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    int T; rn(T);
    while (T--) {
        int n, k; rn(n); rn(k);

        fill(cnt, cnt + n, 0); FOR (i, 0, k) p[i] = 0;
        FOR (i, 0, n) FOR (j, 0, k) f[j][i] = i;

        FOR (i, 0, k) rn(cur[i]);
        FOR (i, 0, n) {
            FOR (j, 0, k) rn(a[i][j]);
            FOR (j, 0, k) rn(b[i][j]);
        }

        FOR (i, 0, k) sort(f[i], f[i] + n, cmp{i});

        int ans = 0;
        while (1) {
            bool GG = true;
            FOR (i, 0, k)
                while (p[i] < n && a[f[i][p[i]]][i] <= cur[i]) {
                    int t = f[i][p[i]++];
                    if (++cnt[t] == k) {
                        ++ans;
                        GG = false;
                        FOR (j, 0, k) cur[j] += b[t][j];
                    }
                }
            if (GG) break;
        }
        cout << ans << endl;
        FOR (i, 0, k) printf("%d%c", cur[i], i == _i - 1 ? '\n' : ' ');
    }
}