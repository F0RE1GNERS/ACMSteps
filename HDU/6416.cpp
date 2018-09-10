// [Auto Archived]
// Submit: 2018-08-20 16:43:32
// Time: 5132MS
// Memory: 36940K

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
#define fuck(...)9
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

const int N = 2e3+10;
const int MOD = 998244353;

char mp[N][N];
int dp[N][N][2];

int mod(int x) {
    return x>=MOD?x-MOD:x;
}

int fix(int x) {
    return x<0?x+MOD:x;
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T; scanf("%d", &T);
    while(T--) {
        memset(dp, 0, sizeof(dp));
        int n, m, k; scanf("%d%d%d", &n, &m, &k); k = min(k, m-1);
        for(int i = 1; i<=n; ++i) scanf("%s", mp[i]+1);
        dp[0][1][0] = 1; dp[0][m][1] = 1;
        for(int h = 1; h<=n; ++h) {
            dbg(h);
            for(int i = 1; i+1<=m && i<=k; ++i) {
                dp[h-1][1][0] = mod(dp[h-1][1][0] + dp[h-1][i+1][0]);
                dp[h-1][m][1] = mod(dp[h-1][m][1] + dp[h-1][m-i][1]);
            }
            for(int i = 2; i+k<=m; ++i) {
                dp[h-1][i][0] = dp[h-1][i+k][0];
                dp[h-1][m-i+1][1] = dp[h-1][m-i-k+1][1];
            }
            for(int i = m-k+1; i<=m; ++i) dp[h-1][i][0] = 0, dp[h-1][m-i+1][1] = 0;
            for(int i = 1; i<=m; ++i) {
                dbg(h, i, dp[h-1][i][0]);
            }
            LL pos = 0, neg = 0;
            for(int i = 1, j; i<=m; ) {
                int delta = fix(pos-neg);
                for(j = i; j<=m && mp[h][j] == mp[h][i]; ++j) {
                    dp[h][j][0] = dp[h-1][j][0]; pos = mod(pos+dp[h-1][j][0]);
                    dp[h][j][1] = dp[h-1][j][1]; neg = mod(neg+dp[h-1][j][1]);
                }
                dp[h][i][0] = mod(dp[h][i][0] + delta);
                delta = fix(pos-neg);
                dp[h][j-1][1] = mod(dp[h][j-1][1] + delta);
                i = j;
            }
            for(int i = 1; i<=m; ++i) {
                dbg(h, i, dp[h][i][0]);
            }
        }
        LL ans = 0;
        for(int i = 1; i<=m; ++i) {
            ans = mod(ans+dp[n][i][0]);
            dbg(dp[n][i][0]);
        }
        printf("%lld\n", ans);
            
    }
    return 0;
}
