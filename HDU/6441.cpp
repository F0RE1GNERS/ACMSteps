// [Auto Archived]
// Submit: 2018-08-25 12:29:34
// Time: 608MS
// Memory: 2052K

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
const int N = 40000 + 100;
struct P { LL x, y; };
P p[N];

bool check(LL i, LL a, LL b) {
    if (a > b) swap(a, b);
    if ((a + b) % 2 == 0 && (b - a) % 2 == 0) {
        LL m = (a + b) / 2;
        LL n = (b - a) / 2;
        assert(i == m * m - n * n);
        p[i].x = 2 * m * n;
        p[i].y = m * m + n * n;
        return true;
    }
    if (b % 2 == 0) swap(a, b);
    if (a % 2 != 0) return false;
    if (a % 2 == 0) {
        a = a / 2;
        if (a < b) swap(a, b);
        LL m = a;
        LL n = b;
        assert(i == 2 * m * n);
        p[i].x = m * m - n * n;
        p[i].y = m * m + n * n;
        return true;
    }
    return false;
}

int main() {
    FOR (i, 3, N) {
        p[i].x = p[i].y = -1;
        FOR (j, 1, int(sqrt(i + 0.5)) + 1)
            if (i % j == 0)
                if (check(i, j, i / j)) break;
    }
    FOR (i, 3, N) {
//        dbg(i);

//        if (p[i].x == -1)
//        dbg(i, p[i].x, p[i].y);
//        else
            assert(i * i + p[i].x * p[i].x == p[i].y * p[i].y &&
               p[i].x <= 1000000000 && p[i].y <= 1000000000);
    }
    int T; cin >> T;
    while (T--) {
        LL n, a; scanf("%lld%lld", &n, &a);
        if (n > 2 || n == 0) puts("-1 -1");
        else {
            if (n == 1) printf("%lld %lld\n", a, a + a);
            else if (n == 2) {
                printf("%lld %lld\n", p[a].x, p[a].y);
            }
        }
    }
}