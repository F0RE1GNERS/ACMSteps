// [Auto Archived]
// Submit: 2018-08-13 16:56:52
// Time: 655MS
// Memory: 1468K

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

const int N = 1E4 + 100;
int fi[N], la[N];
int pos[N], ch[N], vis[N];
vector<int> ans;

const int P = 64;
const int M = (1E4 + 200) / P;
typedef unsigned long long ULL;
const ULL ONE = 1;

struct BS {
    ULL a[M];

    void go(int x) {
        int offset = x / P; x %= P;
        if (x == 0) {
            for (int i = offset, j = 0; i < M; ++i, ++j) {
                a[j] |= a[i] >> x;
            }
        } else {
            for (int i = offset, j = 0; i + 1 < M; ++i, ++j) {
                a[j] |= a[i] >> x;
                a[j] |= a[i + 1] << (64 - x);
            }
        }
    }
    void init() { memset(a, 0, sizeof a); }
    void set(int x) {
        int offset = x / P; x %= P;
        a[offset] |= (ONE << x);
    }
    void debug() {
        FOR (i, 0, M) FOR (j, 0, P) putchar((a[i] & (ONE << j)) ? '1' : '0');
        puts("");
    }
    int lowbit() {
        FOR (i, 0, M)
            if (a[i]) return i * P + __builtin_ctzll(a[i]);
        assert (0);
    }
    int highbit(int x) {
        // 不超过 [0,x) 的最高位
        int xx = x;
        int offset = x / P; x %= P;
        FORD (i, offset, -1) {
            if (!a[i]) continue;
            if (i == offset) {
                FORD (j, x - 1, -1) if ((ONE << j) & a[i]) { return i * P + j; }
            } else return i * P + 63 - __builtin_clzll(a[i]);
        }
        assert (0);
    }

} bs[3], cs[3];

int main() {
    // bs.set(2);
    // bs.set(33);
    // bs.set(55);
    // bs.debug();
    // dbg(bs.lowbit());
    // dbg(bs.highbit(56));

    // bs.go(1);
    // bs.debug();

    // dbg(bs.lowbit());
    // dbg(bs.highbit(50));

    int T; cin >> T;
    while (T--) {
        int m; cin >> m;
        int mx = 0;
        fill(vis, vis + 3, 0);
        FOR (i, 0, 3)  bs[i].init();
        FOR (i, 0, m) {
            int x; char s[3];
            scanf("%d%s", &x, s);
            pos[i] = x - 1; ch[i] = s[0] - 'A';
            mx = max(mx, x);
            vis[ch[i]] = 1;
            bs[ch[i]].set(pos[i]);
        }

        // assert (vis[0] && vis[1] && vis[2]);
        if (!(vis[0] && vis[1] && vis[2])) continue;
        mx += 2;
        
        ans = {N, N, N};
        FOR (p, 3, mx + 1) {
            FOR (i, 0, 3) {
                cs[i] = bs[i];
                for (int px = p; px <= mx; px *= 2)
                    cs[i].go(px);
            }
            FOR (i, 0, 3) {
                fi[i] = cs[i].lowbit();
                la[i] = cs[i].highbit(p);
            }
            if (la[0] < fi[1] && la[1] < fi[2]) {
                ans = min(ans, {la[0], la[1], p - 1});
            }
            FOR (i, 0, 3) dbg(p, i, cs[i].lowbit(), cs[i].highbit(p));
            // if (p == 2473) {
            //     // FOR (i, 0, 3) cs[i].debug();
            //     // dbg(fi[0], la[0], fi[1], la[1], fi[2], la[2]);
            // }
        }
        if (ans[0] == N) {
            puts("NO");
        } else {
            printf("%d %d %d\n", ans[0] + 1, ans[1] - ans[0], ans[2] - ans[1]);
        }
    }
}
