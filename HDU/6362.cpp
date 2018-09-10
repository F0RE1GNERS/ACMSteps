// [Auto Archived]
// Submit: 2018-08-08 12:39:32
// Time: 0MS
// Memory: 1444K

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
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

void output(double r) {
    char s[50]; memset(s, 0, sizeof s);
    sprintf(s, "%.7f", r);
    int len = strlen(s);
    s[len - 1] = 0;
    printf("%s\n", s);
    // printf("%.6f\n", r);
}

int main() {
    int T; cin >> T;
    while (T--) {
        double a, b; cin >> a >> b;
        double r = -1.0;
        double res = acos(r) * a + 2 * b;
        output(res);
    }
}