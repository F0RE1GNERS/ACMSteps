// [Auto Archived]
// Submit: 2018-08-15 15:37:51
// Time: 1201MS
// Memory: 145528K

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
LL pown(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return pown(x, p - 2, p); }

const int M = 6E5 + 100;
const int MOD = 1E9 + 7;
int t[M][26], len[M] = {-1}, fa[M], sz = 2, last = 1;
set<int> S[M];
vector<int> V[M];
LL all[M];
void ins(int ch, int pp) {
    int p = last, np = 0, nq = 0, q = -1;
    if (!t[p][ch]) {
        np = sz++;
        len[np] = len[p] + 1;
        for (; p && !t[p][ch]; p = fa[p]) t[p][ch] = np;
    }
    if (!p) fa[np] = 1;
    else {
        q = t[p][ch];
        if (len[p] + 1 == len[q]) fa[np] = q;
        else {
            nq = sz++; len[nq] = len[p] + 1;
            memcpy(t[nq], t[q], sizeof t[0]);
            fa[nq] = fa[q];
            fa[np] = fa[q] = nq;
            for (; t[p][ch] == q; p = fa[p]) t[p][ch] = nq;
        }
    }
    last = np ? np : nq ? nq : q;
//    dbg(last, v[last], val);
//    v[last] = v[last] * val % MOD;
    V[last].push_back(pp);
}
int c[M] = {1}, a[M];
void rsort() {
    FOR (i, 1, sz) c[i] = 0;
    FOR (i, 1, sz) c[len[i]]++;
    FOR (i, 1, M) c[i] += c[i - 1];
    FOR (i, 1, sz) a[--c[len[i]]] = i;
}

string s[M];
LL w[M];

namespace bit {
    LL c[M], cc[M];
    inline int lowbit(int x) { return x & -x; }
    void add(int x, LL v) {
        for (int i = x; i < M; i += lowbit(i)) {
            c[i] += v; cc[i] += x * v;
            c[i] %= MOD; cc[i] %= MOD;
        }
    }
    inline void add(int l, int r, LL v) {
        add(l, v); add(r + 1, -v);
        dbg(l, r, v);
    }
    LL sum(int x) {
        LL ret = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            ret += (x + 1) * c[i] - cc[i];
            ret %= MOD;
        }
        return ret;
    }
    inline LL sum(int l, int r) { return sum(r) - sum(l - 1); }
}



int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int n; cin >> n;
    FOR (i, 0, n) cin >> s[i];
    FOR (i, 0, n) cin >> w[i];
    FOR (i, 0, n) {
        dbg("!");
        last = 1;
        FOR (j, 0, s[i].length()) ins(s[i][j] - 'a', i);
    }
    rsort();
//    FOR (i, 1, sz) {
//        int u = a[i];
//        dbg(u);
//
//    }

//    int hhh = t[1][1];
//    dbg(hhh, v[hhh], len[hhh], len[fa[hhh]]);
    fill(all, all + sz, 1);
    FORD (i, sz - 1, 1) {
        int u = a[i];
        dbg(u, fa[u]);
        dbg(V[u]);
        for (int& x: V[u]) {
            if (!S[u].count(x)) { S[u].insert(x); all[u] = all[u] * w[x] % MOD; }
        }
        dbg(u, len[u], len[fa[u]] + 1, all[u], S[u].size());
        bit::add(len[fa[u]] + 1, len[u], all[u]);
        if (S[u].size() > S[fa[u]].size()) {
            swap(S[u], S[fa[u]]);
            swap(all[u], all[fa[u]]);
        }
        for (auto& x: S[u]) {
            if (!S[fa[u]].count(x)) {
                S[fa[u]].insert(x);
                all[fa[u]] = all[fa[u]] * w[x] % MOD;
            }
        }
    }

//    FOR (i, 2, sz)

    int Qn; cin >> Qn;
    while (Qn--) {
        int x; cin >> x;
        dbg(bit::sum(1, min(x, M - 1)));
        LL t = (pown(26, x + 1, MOD) - 26 + MOD) % MOD;
        cout << (bit::sum(1, min(x, M - 1)) * 25 % MOD * get_inv(t, MOD) % MOD
                 + MOD) % MOD << endl;
    }
}