// [Auto Archived]
// Submit: 2018-08-01 13:02:51
// Time: 15MS
// Memory: 1424K

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

const int N = 1E3 + 100;
int n, a[N], b[N];
LL now;

int main() {
    int T; cin >> T;
    while (T--) {
        LL m;
        cin >> n >> m;
        FOR (i, 0, n) cin >> a[i] >> b[i];
        sort(b, b + n);
        now = 1;
        int ans = 0;
        FOR (i, 0, n) {
            now *= b[i] + 1;
            if (now <= m) { ans = i + 1; }
            else break;
        }
        cout << ans << endl;
    }
}
