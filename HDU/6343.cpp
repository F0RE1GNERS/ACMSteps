// [Auto Archived]
// Submit: 2018-08-01 12:07:49
// Time: 62MS
// Memory: 1800K

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
const int EPS = 1E-10;
int w[N];

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        FOR (i, 1, n + 1)
            scanf("%d", w + i);
        cout << int(sqrt(abs(w[n] - w[1])) + EPS) << endl;
    }
}
