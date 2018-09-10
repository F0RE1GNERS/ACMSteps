// [Auto Archived]
// Submit: 2018-08-06 16:27:01
// Time: 670MS
// Memory: 95916K

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

const int INF = 1E9;
const int N = 1E5 + 100;
const int M = 10;
int suffix[N][M], nxt[N][M];
pair<int, int> f[N][M][M + 1];
int a[N]; char s[N];
int n;

template<typename T>
void update(T &x, const T &y) {
    x = max(x, y);
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; scanf("%d", &n);
        scanf("%s", s);
        if (n == 1) {
            // puts("1");
            puts("1 1 1");
            continue;
        }
        a[n + 1] = 0;
        FOR (i, 0, n) a[i + 1] = s[i] - '0';
        // FOR (i, 0, n + 2) FOR (j, 0, 10) {
        //     up[i][j] = suffix[i][j] = down[i][j] = 0;
        // }
        FOR (i, 0, n + 3) FOR (j, 0, M) suffix[i][j] = nxt[i][j] = 0;
        FOR (i, 0, n + 3) FOR (j, 0, M) f[i][j][M] = {0, 0};
        FOR (i, 0, n + 3) FOR (j, 0, M) FOR (k, 0, M) f[i][j][k] = {-INF, 0};
        FORD (i, n, 0) {
            FOR (j, 0, M) { suffix[i][j] = suffix[i + 1][j]; }
            update(suffix[i][a[i]], suffix[i + 1][a[i]] + 1);
            FORD (j, a[i], 0) update(suffix[i][j - 1], suffix[i][j]);
        }
        // FOR (i, 1, n) FOR (j, 0, M) dbg(i, j, suffix[i][j]);

        FOR (j, 0, M) nxt[n][j] = n + 1;
        FORD (i, n, 0) {
            FOR (j, 0, M) nxt[i - 1][j] = nxt[i][j];
            nxt[i - 1][a[i]] = i;
        }
        FOR (i, 0, n) {
            FOR (j, 0, M) FOR (k, 0, M + 1) {
                // dbg(i, j, k, f[i][j][k].first, f[i][j][k].second);
                if (k == M) {
                    FOR (c, a[i], M) {
                        int pos = nxt[i][c];
                        update(f[pos][c][k], {f[i][j][k].first + 1, f[i][j][k].second});
                        update(f[pos][j][c], {f[i][j][k].first + 1, pos});
                    }
                } else {
                    FORD (c, a[i], j - 1) {
                        int pos = nxt[i][c];
                        update(f[pos][j][k], {f[i][j][k].first + 1, f[i][j][k].second});
                    }
                }
            }
        }
        pair<int, pair<int, int>> ans;
        FOR (i, 1, n + 1) {
            FOR (j, 0, M) FOR (k, 0, M)
                ans = max(ans, {f[i][j][k].first + suffix[i + 1][k], make_pair(f[i][j][k].second, i)});
        }
        // printf("%d\n", ans.first);
        printf("%d %d %d\n", ans.first, ans.second.first, ans.second.second);
    }
}