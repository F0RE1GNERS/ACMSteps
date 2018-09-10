// [Auto Archived]
// Submit: 2018-07-23 16:33:32
// Time: 140MS
// Memory: 3876K

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
const int N = 1E5 + 100;
struct P { 
    int l, r;
};
char s[N];
P a[N];
int ans;

P go(char* s) {
    int x = 0, y = 0;
    FOR (i, 0, strlen(s)) {
        if (s[i] == '(') ++x;
        else { if (x) --x, ++ans; else ++y; }
    }
    return {y, x};
}

int main() {
    int T; cin >> T;
    while (T--) {
        ans = 0;
        int n; cin >> n;
        FOR (i, 0, n) {
            scanf("%s", s);
            a[i] = go(s);
        }
        int x;

        vector<P> positive;
        vector<P> negative;
        for (int i = 0; i < n; ++i) {
            if (a[i].r - a[i].l > 0)
                positive.push_back(a[i]);
            else negative.push_back(a[i]);
        }
        sort(positive.begin(), positive.end(), [](const P& a, const P& b) {
            return a.l < b.l;
        });
        sort(negative.begin(), negative.end(), [](const P& a, const P& b) {
            return a.r > b.r;
        });

        x = 0;
        for (P& i: positive) a[x++] = i;
        for (P& i: negative) a[x++] = i;

        x = 0;
        FOR (i, 0, n) {
            int t = min(a[i].l, x);
            x -= t; ans += t;
            x += a[i].r;
        }

        printf("%d\n", ans * 2);
    }
}