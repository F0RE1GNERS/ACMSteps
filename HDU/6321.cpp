// [Auto Archived]
// Submit: 2018-07-30 12:53:44
// Time: 3322MS
// Memory: 2420K

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

const int N = 1 << 11;
int n, m, f[N][20];
const int MOD = 1E9 + 7;

int main() {
    // get_phi();
    int T; cin >> T;
    while (T--) {
        memset(f, 0, sizeof f);
        cin >> n >> m;
        FOR (i, 0, 1 << n) f[i][0] = 1;
        while (m--) {
            char op[10];
            int u, v; scanf("%s%d%d", op, &u, &v);
            u--; v--;
            int st = (1 << u) + (1 << v);
            if (op[0] == '+') {
                FOR (vert, 0, 1 << n)
                    FOR (j, 1, n / 2 + 1) {
                        if ((vert & st) == st)
                            (f[vert][j] += f[vert ^ st][j - 1]) %= MOD;
                    }
            } else if (op[0] == '-') {
                FOR (vert, 0, 1 << n)
                    FOR (j, 1, n / 2 + 1) {
                        if ((vert & st) == st)
                            (f[vert][j] += MOD - f[vert ^ st][j - 1]) %= MOD;
                    }
            } else {
                assert (0);
            }
            FOR (j, 1, n / 2 + 1) {
                printf("%d%c", f[(1 << n) - 1][j], j + 1 == _j ? '\n' : ' ');
            }
            // puts("");
        }
    }
    return 0;
}