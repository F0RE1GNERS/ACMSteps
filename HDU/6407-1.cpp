// [Auto Archived]
// Submit: 2018-08-15 17:54:13
// Time: 6879MS
// Memory: 118984K

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

const int M = 13;
const int N = 25;
const int P = 550000;
int m, n;
LL f[N][P];
char _s[N][N], s[N][N];
int _now[P][M + 1];
int xp[M]; int* now;
LL fac[N], ans[N];

void init_xp() {
    xp[0] = 1; fac[0] = 1;
    FOR (i, 1, M) xp[i] = xp[i - 1] * 3;
    FOR (i, 1, M) fac[i] = i * fac[i - 1];
}

void pre_now() {
    FOR (i, 0, P) {
        int x = i, j = 0;
        while (x) {
            _now[i][j++] = x % 3;
            x /= 3;
        }
    }
}

inline void init_now(int x) {
    now = _now[x];
}

template <typename T>
void o(T p) {
    static int stk[70], tp;
    if (p == 0) {
        putchar('0');
        return;
    }
    if (p < 0) { p = -p; putchar('-'); }
    while (p) stk[++tp] = p % 10, p /= 10;
    while (tp) putchar(stk[tp--] + '0');
}

int main() {
    int T; cin >> T;

    init_xp();
    pre_now();

    while (T--) {
        int K;
        scanf("%d%d%d", &m, &n, &K);
        FOR (i, 0, m) scanf("%s", _s[i]);
        FOR (i, 0, m) FOR (j, 0, n) s[j][i] = _s[i][j];
        FOR (i, 0, n) dbg(s[i]);

        FOR (i, 0, n + 1) FOR (j, 0, xp[m]) f[i][j] = 0;

        memset(ans, 0, sizeof ans);
        f[0][0] = 1;
        FOR (row, 0, n) {
            FOR (st, 0, xp[m]) {
                if (f[row][st] == 0) continue;
                init_now(st);

                // choose nothing
                int y = st;
                FOR (j, 0, m) {
                    if (now[j]) continue;
                    if (s[row][j] == 'Q') y += (2 - now[j]) * xp[j];
                }
                f[row + 1][y] += f[row][st];
                dbg("nothing", row, st, y, f[row+1][y]);

                // choose something
                FOR (chosen, 0, m) {
                    if (now[chosen] == 1 || s[row][chosen] == '.') continue;
                    int y = st + (1 - now[chosen]) * xp[chosen];
                    f[row + 1][y] += f[row][st];
                    dbg(chosen, row, st, y, f[row+1][y]);
                }
            }
        }

        FOR (st, 0, xp[m]) {
            if (f[n][st] == 0) continue;
            init_now(st);
            int cnt = 0;
            FOR (j, 0, m) {
                if (now[j] == 2) { cnt = -1; break; }
                if (now[j] == 1) cnt++;
            }
            if (cnt >= 0) ans[cnt] += f[n][st];
        }

        // FOR (i, 1, K + 1) ans[i] *= fac[i];
        
        FOR (i, 1, K + 1) { o(__int128(ans[i]) * fac[i]); puts(""); }
    }
}