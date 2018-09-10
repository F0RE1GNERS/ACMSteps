// [Auto Archived]
// Submit: 2018-07-30 15:24:02
// Time: 156MS
// Memory: 4336K

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

const int N = 100+5;
const int M = 2000;
const int MOD = 1e9+7;

int id[N][N][N];
int a[N], v[N];
int gcd[N][N];
int state[M][3], cnt;

LL dp[N][M];

int pown(int a, int b) {
    int ret = 1;
    while(b) {
        if(b&1) ret = 1LL * ret * a % MOD;
        a = 1LL * a * a % MOD;
        b>>=1;
    }
    return ret;
}

int inv(int a) {
    return pown(a, MOD-2);
}

void dfs(int x, int d) {
    static int v[4];
    if(d==0) {
        state[cnt][0] = v[3];
        state[cnt][1] = v[2];
        state[cnt][2] = v[1];
        //dbg(v[3], v[2], v[1], cnt);
        id[v[3]][v[2]][v[1]] = cnt++;
        return;
    }
    for(int i = x; i<N; i+=x) {
        v[d] = i;
        dfs(i, d-1);
    }
}

inline int ___gcd(int x, int y) {
    return gcd[x][y];
}

int main() {
    dfs(1, 3); dbg(cnt);
    int T, n, m, freenum;
    for(int i = 1; i<=100; ++i)
        for(int j = 1; j<=100; ++j) gcd[i][j] = __gcd(i, j);
    scanf("%d", &T);
    //T = 10;
#define __gcd ___gcd
    while(T--) {
        memset(dp, 0, sizeof(dp));
        scanf("%d%d", &n, &m); freenum = 0;
        for(int i = 1; i<=n; ++i) scanf("%d", a+i), freenum+=a[i]==0;
        //n = 100, m = 100, freenum = 100;
        for(int i = 1; i<=m; ++i) scanf("%d", v+i);
        if(a[1]!=0) {
            dp[1][id[a[1]][a[1]][a[1]]] = 1;
            dbg(id[a[1]][a[1]][a[1]]);
        } else {
            for(int i = 1; i<=m; ++i) {
                dp[1][id[i][i][i]] = 1;
            }
        }
        for(int i = 2; i<=3; ++i) {
            if(a[i]!=0) {
                for(int j = 0; j<cnt; ++j) {
                    //dbg(dp[i-1][j], i-1, j);
                    if(dp[i-1][j]>0) {
                        int k = a[i];
                        {
                            int x = __gcd(state[j][0], k);
                            int y = __gcd(state[j][1], k);
                            int z = __gcd(state[j][2], k);
                            dp[i][id[y][z][k]]+=dp[i-1][j];
                        }
                        //dbg(id[y][z][k]);
                    }
                }
            } else {
                for(int j = 0; j<cnt; ++j) if(dp[i-1][j]>0)
                    for(int k = 1; k<=m; ++k) {
                        int x = __gcd(state[j][0], k);
                        int y = __gcd(state[j][1], k);
                        int z = __gcd(state[j][2], k);
                        dp[i][id[y][z][k]]+=dp[i-1][j];
                        //dbg(id[y][z][k]);
                    }
            }
        }
        for(int i = 4; i<=n; ++i) {
            /*
            for(int j = 0; j<cnt; ++j) if(dp[i-1][j]>0) {
                dp[i-1][j]%=MOD;
            }
            */
            if(a[i]!=0) {
                for(int j = 0; j<cnt; ++j) if(dp[i-1][j]>0) {
                    int k = a[i];
                    {
                        int x = __gcd(state[j][0], k);
                        int y = __gcd(state[j][1], k);
                        int z = __gcd(state[j][2], k);
                        int key = id[y][z][k];
                        (dp[i][key]+=dp[i-1][j]*v[x])%=MOD;
                    }
                }
            } else {
                for(int j = 0; j<cnt; ++j) if(dp[i-1][j]>0)
                    for(int k = 1; k<=m; ++k) {
                        int x = __gcd(state[j][0], k);
                        int y = __gcd(state[j][1], k);
                        int z = __gcd(state[j][2], k);
                        int key = id[y][z][k];
                        (dp[i][key]+=dp[i-1][j]*v[x])%=MOD;
                    }
            }
        }
        LL ans = 0;
        for(int i = 0; i<cnt; ++i) ans = (ans + dp[n][i])%MOD;
        dbg(ans);
        printf("%lld\n", ans*inv(pown(m, freenum))%MOD);
    }
    return 0;
}