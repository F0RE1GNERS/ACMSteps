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
string s;
LL n, dp[N][2];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> s;
        n = s.length();
        dp[n][0] = dp[n][1] = 0;
        LL ans = 0;
        FORD (i, n - 1, -1) {
            int t;
            t = s[i] == '0' ? 2 : 1;
            dp[i][0] = dp[i + 1][t % 2] + (n - i) * t;
            t = s[i] == '1' ? 2 : 1;
            dp[i][1] = dp[i + 1][(t + 1) % 2] + (n - i) * t;
            dbg(i, dp[i][0], dp[i][1]);
            ans += dp[i][0];
        }
        cout << ans << endl;
    }
    return 0;
}

 
