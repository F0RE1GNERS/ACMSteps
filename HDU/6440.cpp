// [Auto Archived]
// Submit: 2018-08-25 12:50:08
// Time: 3572MS
// Memory: 1376K

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
// -----------------------------------------------------------------------------


int main() {
    int T; cin >> T;
    while (T--) {
        int p; scanf("%d", &p);
        FOR (i, 0, p)
            FOR (j, 0, p)
                 printf("%d%c", (i + j) % p, j == _j - 1 ? '\n' : ' ');

        FOR (i, 0, p)
            FOR (j, 0, p)
                printf("%d%c", (i * j) % p, j == _j - 1 ? '\n' : ' ');
    }
}