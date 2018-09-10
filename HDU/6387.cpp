// [Auto Archived]
// Submit: 2018-08-14 09:34:33
// Time: 655MS
// Memory: 1524K

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
vector<int> bs[3];


int main() {
    int T; cin >> T;
    while (T--) {
        int m; cin >> m;
        int mx = 0;
        FOR (i, 0, 3) bs[i].clear();
        FOR (i, 0, m) {
            int x; char s[3];
            scanf("%d%s", &x, s);
            pos[i] = x - 1; ch[i] = s[0] - 'A';
            mx = max(mx, x);
            bs[ch[i]].push_back(pos[i]);
        }

        FOR (i, 0, 3) sort(bs[i].begin(), bs[i].end());
        FOR (i, 0, 3) dbg(bs[i]);

        mx += 2;
        
        ans = {N, N, N};
        FOR (p, 3, mx + 1) {
            FOR (j, 0, 3) {
                fi[j] = N, la[j] = -1;
                for (int i = 0; i * p < N; ++i) {
                    auto lb = lower_bound(bs[j].begin(), bs[j].end(), i * p);
                    auto ub = lower_bound(bs[j].begin(), bs[j].end(), (i + 1) * p);
                    if (lb == ub) continue;
                    ub--; fi[j] = min(fi[j], (*lb) % p); la[j] = max(la[j], (*ub) % p);
                }
            }
            if (la[0] < fi[1] && la[1] < fi[2]) {
                ans = min(ans, {la[0], la[1], p - 1});
            }
        }
        if (ans[0] == N) {
            puts("NO");
        } else {
            printf("%d %d %d\n", ans[0] + 1, ans[1] - ans[0], ans[2] - ans[1]);
        }
    }
}
