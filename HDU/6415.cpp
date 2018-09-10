// [Auto Archived]
// Submit: 2018-08-20 14:33:30
// Time: 1887MS
// Memory: 160296K

#include <bits/stdc++.h>

//#undef zerol
using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cerr << "Debug: " << #args << " -> "; err(args); } while (0)
#define fuck(x) do { printf("fuck@%d\n", x); } while(0)
#else
#define dbg(...)
#define fuck(...)
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------
const int N = 80 + 6;
LL fac[N * N] = {1};
int n, m;
LL P[N][N];
LL f[N][N][N * N];
int c[N][N][N * N], clk;
LL K;

LL go(LL x, LL y, LL k) {

    LL& ret = f[x][y][k];
    if (c[x][y][k] == clk) return ret;
    c[x][y][k] = clk;

    if (x == n || y == m) return ret = fac[n * m - k] * P[n][x] % K * P[m][y] % K;
    ret = 0;
    if (k < x * y) ret += go(x, y, k + 1) * (x * y - k);
    ret += go(x + 1, y, k + 1) * y;
    ret += go(x, y + 1, k + 1) * x;
//    dbg(x, y, k, ret);
    return ret %= K;
}

int main() {
    int T; cin >> T;
    while (T--) {
        ++clk;
        cin >> n >> m >> K;
        int t = max(n, m);
        FOR (i, 0, t+1) {
            P[i][0] = 1;
            FOR(j, 1, i+1) P[i][j] = P[i][j-1]*(i-j+1)%K;
        }
        FOR (i, 1, n * m + 1) fac[i] = fac[i - 1] * i % K;
        cout << go(1, 1, 1) << endl;
    }
}