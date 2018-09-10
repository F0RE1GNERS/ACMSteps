// [Auto Archived]
// Submit: 2018-08-25 15:03:56
// Time: 249MS
// Memory: 2780K

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
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "" << endl; }
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
// -----------------------------------------------------------------------------
const int N = 5E4 + 100;
LL a[N], x[N];
int n, k; LL s, m;

LL go(int start) {
    int p = 0;
    int cur = start;
    do {
        x[++p] = a[cur];
        cur = (cur + k) % n;
    } while (cur != start);
    LL all = accumulate(x + 1, x + p + 1, 0LL);
//    dbg(p, all);
    LL ans = 0;
    LL circle = m / p, remain = m - circle * p;
    if (all > 0 && circle > 1) {
        ans += (circle - 1) * all;
        circle = 1;
    } else if (all <= 0) circle = min(circle, 1LL);
    remain += circle * p;
    assert(remain > 0);
    FOR (i, 1, p + 1) x[i + p] = x[i + p + p] = x[i];
    p *= 3;
    dbg(p, remain);
    FOR (i, 1, p + 1) x[i] += x[i - 1];
//    FOR (i, 0, p) dbg(i, x[i]);
    LL maxS = 0;
    static multiset<LL> S; S.clear();
    FOR (i, 1, remain + 1) S.insert(x[i]);

    FOR (i, remain + 1, p + 1) {
        maxS = max(maxS, *S.rbegin() - x[i - remain - 1]);
        S.erase(S.find(x[i - remain])); S.insert(x[i]);
    }

    return ans + maxS;
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    int T; rn(T);
    FOR (Ca, 1, T + 1) {
        rn(n); rn(s); rn(m); rn(k);
        FOR (i, 0, n) rn(a[i]);

        LL ans = 0;
        FOR (i, 0, __gcd(k, n))
            ans = max(ans, go(i));
        dbg(ans);
        printf("Case #%d: ", Ca);
        cout << max(s - ans, 0LL) << endl;
    }
}