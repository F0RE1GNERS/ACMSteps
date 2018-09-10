// [Auto Archived]
// Submit: 2018-08-22 14:20:23
// Time: 1107MS
// Memory: 9920K

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
// -----------------------------------------------------------------------------
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
// ------------------------------------------------------------------
const int N = 1E5 + 100;
int K;

namespace kd {
    const int M = N;
    const int inf = 1E9 + 100;
    struct P {
        int d[5];
        int l[5], r[5];
        int val, maxv;
        P *ls, *rs;
        P* up() {
            maxv = max(val, max(ls->maxv, rs->maxv));
            FOR (i, 0, K) {
                l[i] = min(d[i], min(ls->l[i], rs->l[i]));
                r[i] = max(d[i], max(ls->r[i], rs->r[i]));
            }
            return this;
        }
    } pool[M], *null = new P, *pit = pool;
    static P *tmp[M], **pt;
    void init() {
        null->ls = null->rs = null;
        FOR (i, 0, K) null->l[i] = inf, null->r[i] = -inf;
        null->maxv = null->val = -inf;
    }
    P* build(P** l, P** r, int d = 0) { // [l, r)
        if (d == K) d = 0;
        if (l >= r) return null;
        P** m = l + (r - l) / 2;
        nth_element(l, m, r, [&](const P* a, const P* b){
            return a->d[d] < b->d[d];
        });
        P* o = *m;
        o->ls = build(l, m, d + 1); o->rs = build(m + 1, r, d + 1);
        return o->up();
    }
    LL test(P* o, int d[]) {
        LL ret = 0;
        FOR (i, 0, K) ret += max(abs(o->l[i] - d[i]), abs(o->r[i] - d[i]));
        return ret + o->maxv;
    }
    LL S;
    LL query(P* o, int d[]) {
        if (o == null) return 0;
        LL cur = o->val;
        FOR (i, 0, K) cur += abs(d[i] - o->d[i]);
        S = max(S, cur);
        LL mdl = test(o->ls, d), mdr = test(o->rs, d);
        if (mdl > mdr) {
            if (S < mdl) S = max(S, query(o->ls, d));
            if (S < mdr) S = max(S, query(o->rs, d));
        } else {
            if (S < mdr) S = max(S, query(o->rs, d));
            if (S < mdl) S = max(S, query(o->ls, d));
        }
        return S;
    }
    P* Build() {
        pt = tmp; FOR (it, pool, pit) *pt++ = it;
        return build(tmp, pt);
    }
}
using namespace kd;

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    K = 5; init();
    int T; rn(T);
    while (T--) {
        pit = pool;
        int n, m; rn(n); rn(m); rn(K);
        dbg(n, m);
        int MaxS = 0;
        static int mind[5], maxd[5];
        memset(mind, 0, sizeof mind);
        memset(maxd, 0, sizeof maxd);
        FOR (_, 0, n) {
            rn(pit->val); MaxS = max(MaxS, pit->val);
            FOR (i, 0, K) rn(pit->d[i]);
            FOR (i, 0, K) {
                mind[i] = min(mind[i], pit->d[i]),
                maxd[i] = max(maxd[i], pit->d[i]);
            }
            pit++;
        }
        P* rt = Build();
        dbg(rt->l[0], rt->r[0]);
        LL ans = 0;
        FOR (_, 0, m) {
            static int d[5];
            int s = 0; rn(s);
            FOR (i, 0, K) rn(d[i]);
            S = MaxS;
            FOR (i, 0, K) S = max(S, (LL)max(d[i] - mind[i], maxd[i] - d[i]));
            ans = max(ans, s + query(rt, d));
        }
        printf("%lld\n", ans);
    }
}