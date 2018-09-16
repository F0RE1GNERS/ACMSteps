#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "Debug: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
const LL N = 2E5 + 100;
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using Tree = tree<LL, null_type, less<LL>, rb_tree_tag, tree_order_statistics_node_update>;
Tree t[N];
int belong[N], L[N], R[N], sz, cnt[N];
LL a[N], hh[N];
multiset<LL> _ans;

inline LL f(LL x) { return x >> 20; }

int build(int l, int r) {
    FOR (i, l, r + 1) belong[i] = sz;
    hh[sz] = 0;
    FOR (i, l, r + 1) {
        t[sz].insert(a[i]);
        hh[sz] += t[sz].size() - t[sz].order_of_key((f(a[i]) + 1) << 20);
    }
    L[sz] = l; R[sz] = r;
    // _ans.insert(hh[sz]);
    return sz++;
}

void sub(int tt, int l, int r) {
    Tree& x = t[tt];
    FOR (i, l, r + 1) x.erase(a[i]);
}



int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        _ans.clear();
        FOR (i, 1, n + 1) {
            t[i].clear();
            hh[i] = cnt[i] = 0;
        }
        FOR (i, 1, n + 1) scanf("%lld", &a[i]);
        FOR (i, 1, n + 1) a[i] = (a[i] << 20) | (++cnt[a[i]]);

        FOR (i, 1, n + 1) belong[i] = 1;
        L[1] = 1; R[1] = n; sz = 2;
        FOR (i, 1, n + 1) {
            hh[1] += t[1].size() - t[1].order_of_key((f(a[i]) + 1) << 20);
            t[1].insert(a[i]);
        }
        dbg(hh[1]);
        vector<LL> Ans;
        Ans.push_back(hh[1]);

        _ans.insert(hh[1]);
        FOR (_, 0, n) {
            LL p; scanf("%lld", &p); p ^= Ans.back();
            dbg(p);
            int pp = belong[p], l = L[pp], r = R[pp];
            //dbg(pp, l, r);
            int tl, tr;
            int m = (l + r) / 2;
            if (p < m) {
                tl = build(l, p - 1); tr = pp;
                 dbg("+", hh[tl]); _ans.insert(hh[tl]);
                sub(pp, l, p); L[pp] = p + 1;
            } else {
                tr = build(p + 1, r); tl = pp;
                 dbg("+", hh[tr]); _ans.insert(hh[tr]);
                sub(pp, p, r); R[pp] = p - 1;
            }
            dbg("-", hh[pp]);
            assert(_ans.find(hh[pp]) != _ans.end());
            _ans.erase(_ans.find(hh[pp]));
            //dbg(t[tl].size(), t[tr].size());
            #ifdef zerol
            //for (auto& x: t[tl]) dbg("tl", f(x), x);
            //for (auto& x: t[tr]) dbg("tr", f(x), x);
            #endif // zerol


            hh[pp] -= t[tr].order_of_key(f(a[p]) << 20) + t[tl].size() - t[tl].order_of_key((f(a[p]) + 1) << 20);

            if (p < m) {
                FOR (i, l, p) {
                    hh[pp] -= t[tr].order_of_key(f(a[i]) << 20);
                }
                hh[pp] -= hh[tl];
            } else {
                FOR (i, p + 1, r + 1) {
                    hh[pp] -= t[tl].size() - t[tl].order_of_key((f(a[i]) + 1) << 20);
                    dbg(i, f(a[i]));
                }
                hh[pp] -= hh[tr];
            }
            _ans.insert(hh[pp]);
            dbg("+", hh[pp]);
            Ans.push_back(*_ans.rbegin());
            dbg(Ans.back());
             #ifdef zerol
            for (auto&x: _ans) dbg("ans", x);
            #endif // zerol
        }
        Ans.pop_back();
        FOR (i, 0, (int)Ans.size()) printf("%lld%c", Ans[i], i == _i - 1 ? '\n' : ' ');
    }
}
 
