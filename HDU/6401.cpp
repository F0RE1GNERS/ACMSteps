// [Auto Archived]
// Submit: 2018-08-15 12:14:08
// Time: 15MS
// Memory: 1404K

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
const int mp[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
char a[10][10], b[10][10];

char s[100];
int main() {
    int T; cin >> T;
    while (T--) {
        int Qn; cin >> Qn;
        FOR (i, 0, 3) scanf("%s", a[i]);
        while (Qn--) {
            scanf("%s", s);
            int x = mp[s[0] - '1'][0], y = mp[s[0] - '1'][1];
            FOR (i, x, x + 2)
                FOR (j, y, y + 2)
                     b[i][j] = a[i][j];
            if (s[1] == 'C') {
                a[x][y] = b[x + 1][y]; a[x][y + 1] = b[x][y];
                a[x + 1][y] = b[x + 1][y + 1]; a[x + 1][y + 1] = b[x][y + 1];
            } else {
                a[x][y] = b[x][y + 1]; a[x][y + 1] = b[x + 1][y + 1];
                a[x + 1][y] = b[x][y]; a[x + 1][y + 1] = b[x + 1][y];
            }
        }
        FOR (i, 0, 3) {
            FOR (j, 0, 3) printf("%c", a[i][j]);
            puts("");
        }
    }
}