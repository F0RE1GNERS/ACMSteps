// [Auto Archived]
// Submit: 2018-07-30 12:26:16
// Time: 249MS
// Memory: 1408K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args<< " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39m" << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
const int N = 1E5 + 100;


int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int s = 0;
        FOR (_, 0, n) {
            int t; scanf("%d", &t); s ^= t;
        }
        FOR (_, 1, n) { int a, b; scanf("%d%d", &a, &b); }
        puts(s ? "Q" : "D");
    }
}