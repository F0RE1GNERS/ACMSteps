// [Auto Archived]
// Submit: 2018-08-14 19:56:39
// Time: 904MS
// Memory: 5468K

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

const int N = 1.1E6;

int m; int pat[N];
namespace kmp {
    int f[N];  // f[i] 表示已匹配成功 i 个，失配要去哪里
    
    template<typename T>
    int go(int stat, T c, bool& acc) {
        // stat 是当前态 (表示已经匹配了 stat 个字符), c 是要走的边
        // return -1 if accepted
        while (stat && c != pat[stat]) stat = f[stat];
        if (c == pat[stat]) stat++;
        if (stat == m) acc = true;
        dbg(stat, acc);
        return stat;
    }

    void getFail() {
        static int f2[N];
        f[0] = f[1] = 0;
        f2[0] = f2[1] = 0;
        FOR (i, 1, m) {
            int j = f2[i];
            while (j && pat[i] != pat[j]) j = f2[j];
            f2[i+1] = f[i+1] = (pat[i] == pat[j]) ? j+1 : 0;
            if (f[i+1] == j+1 && pat[i+1] == pat[j+1]) f[i+1] = f[j+1];
        }
        FOR (i, 0, m) dbg(i, f[i]);
    }
}

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n >> m;
        static int a[N];
        FOR (i, 0, n) scanf("%d", a + i);
        FOR (i, 0, m) scanf("%d", pat + i);
        kmp::getFail();

        int s = 0, ans = -1;
        FOR (i, 0, n) {
            bool acc = false;
            s = kmp::go(s, a[i], acc);
            if (acc) {
                ans = i - m + 2;
                break;
            }
        }
        cout << ans << endl;
    }
}
