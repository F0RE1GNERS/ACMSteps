// [Auto Archived]
// Submit: 2018-07-30 12:17:50
// Time: 358MS
// Memory: 1400K

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

typedef pair<int, int> P;

const int N = 1E3 + 10;

const LL p_max = 1E5 + 100;
LL prime[p_max], p_sz, phi[p_max];
void get_phi() { 
    static bool vis[p_max];
    FOR (i, 2, p_max) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            phi[i] = i - 1;
        }
        static LL d;
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                phi[d] = phi[i] * prime[j];
                break;
            }
            else phi[d] = phi[i] * (prime[j] - 1);
        }
    }
}

int main() {
    // get_phi();
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        if (n <= 1) puts("5");
        else if (n <= 2) puts("7");
        else printf("%d\n", n + 5);
    }
    return 0;
}