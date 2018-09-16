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

const int N = 32;

int ans[N];

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int n, x;
        scanf("%d", &n);
        memset(ans, 0, sizeof(ans));
        while(n--) {
            scanf("%d", &x); int t = 0;
            while(x>0) {
                x>>=1; ++t;
            }
            ++ans[t];
        }
        printf("%d\n", *max_element(ans, ans+N));
    }
}
 
