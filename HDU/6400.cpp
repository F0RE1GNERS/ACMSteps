// [Auto Archived]
// Submit: 2018-08-15 13:23:25
// Time: 15MS
// Memory: 1424K

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
const int N = 200 + 5;
char a[N][N];

int main() {
    int T; cin >> T;
    while (T--) {
        int h, w; cin >> h >> w;
        bool swp = false;
        if (h % 2 == 0 && w % 2 == 0 && h + w - 4 > max(h, w) + min(h, w) / 2 - 1) {
            dbg("1");
            FOR (i, 0, h)
                FOR (j, 0, w) {
                    if (i == 0 || j == 0) a[i][j] = '(';
                    else if (i == h - 1 || j == w - 1) a[i][j] = ')';
                    else if ((i & 1) ^ (j & 1)) a[i][j] = ')'; else a[i][j] = '(';
                }

        } else {
            dbg("2");
            if ((h < w && h % 2 == 0) || w % 2 == 1) { swap(h, w); swp = true; }
            FOR (i, 0, h)
                FOR (j, 0, w) {
//                if ((j < w / 2) ^ (i & 1)) a[i][j] = '('; else a[i][j] = ')';
                    if (j == 0) a[i][j] = '(';
                    else if (j == w - 1) a[i][j] = ')';
                    else if ((i & 1) ^ (j & 1)) a[i][j] = ')'; else a[i][j] = '(';
                }
        }

        if (!swp) {
            FOR (i, 0, h) {
                FOR (j, 0, w)
                    putchar(a[i][j]);
                puts("");
            }
        } else {
            FOR (i, 0, w) {
                FOR (j, 0, h)
                    putchar(a[j][i]);
                puts("");
            }
        }
    }
}