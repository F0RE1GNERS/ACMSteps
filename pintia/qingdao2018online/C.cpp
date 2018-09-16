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
const int N = 1E4 + 100, M = 256, MASK = 255;
struct P { int tp, v, k; };
P a[N];
bool vis[N][M];
char s[100];
bool solved, flag;
int n;

void go(int cur, int v) {
    // dbg(cur, v);
    if (cur == n) { solved = true; flag = true; }
    else if (vis[cur][v]) { solved = true; }
    if (solved) return;
    vis[cur][v] = 1;

    if (a[cur].tp == 0) go(cur + 1, (v + a[cur].v) % M);
    else if (a[cur].tp == 1) {
        if (v == a[cur].v) go(a[cur].k, v); else go(cur + 1, v);
    } else if (a[cur].tp == 2) {
        if (v != a[cur].v) go(a[cur].k, v); else go(cur + 1, v);
    } else if (a[cur].tp == 3) {
        if (v < a[cur].v) go(a[cur].k, v); else go(cur + 1, v);
    } else if (a[cur].tp == 4) {
        if (v > a[cur].v) go(a[cur].k, v); else go(cur + 1, v);
    }
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR (i, 0, n) {
            int v; scanf("%s%d", s, &v);
            if (s[0] == 'a') a[i] = {0, v, -1};
            else {
                int k; scanf("%d", &k); --k;
                if (s[1] == 'e') a[i] = {1, v, k};
                if (s[1] == 'n') a[i] = {2, v, k};
                if (s[1] == 'l') a[i] = {3, v, k};
                if (s[1] == 'g') a[i] = {4, v, k};
            }
        }
        memset(vis, 0, (sizeof vis[0]) * (n + 1));
        solved = flag = false;
        go(0, 0);
        puts(flag ? "Yes" : "No");
    }
}
