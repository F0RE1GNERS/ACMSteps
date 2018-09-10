// [Auto Archived]
// Submit: 2018-07-25 14:06:52
// Time: 639MS
// Memory: 23020K

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
const int N = 2500 + 5;
int a[N][N];
int n, k;

inline int get(int x, int y) { return x  + y * k; }

int main() {
    n = 2000; k = 47;
    // n = 5; k = 2;
    cout << n << endl;
    FOR (d, 0, k)
        FOR (i, 0, k) {
        int c = d * k + i;
        // dbg(c, d, i);
            FOR (t, 0, k)
                a[get(t, (i + d * t) % k)][c] = 1;
    }
    int cnt = 0;
    FOR (i, 0, n) {
        FOR (j, 0, n) {
            if (a[i][j]) ++cnt;
        printf("%d", a[i][j]);
        }
        puts("");
        }

    dbg(cnt);
}
