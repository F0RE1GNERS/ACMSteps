// [Auto Archived]
// Submit: 2018-08-06 13:15:28
// Time: 405MS
// Memory: 1388K

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

const int INF = 2E9;
const int N = 20;
int dig[N], sz, K;
int minans, maxans;

void dfs(int dep, int now, int num) {
    if (now > K) return;
    if (dep == sz) {
        minans = min(minans, num);
        maxans = max(maxans, num);
        return;
    }
    FOR (i, dep, sz) {
        if (dep == 0 && dig[i] == 0) continue;
        swap(dig[dep], dig[i]);
        // dbg(dep, i);
        dfs(dep + 1, now + (dep != i), num * 10 + dig[dep]);
        swap(dig[dep], dig[i]);
    }
}

void solve(int n, int k) {
    K = k;
    sz = 0;
    while (n) {
        dig[sz++] = n % 10;
        n /= 10;
    }
    reverse(dig, dig + sz);
    // FOR (i, 0, sz) copy(dig, dig + sz, mink);
    // FOR (i, 0, sz) copy(dig, dig + sz, maxk);
    // sort(maxk, maxk + sz, greater<int>());
    minans = INF; maxans = 0;
    dfs(0, 0, 0);
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n, k; scanf("%d%d", &n, &k);
        solve(n, k);
        printf("%d %d\n", minans, maxans);
    }
}