// [Auto Archived]
// Submit: 2018-07-30 15:40:56
// Time: 1201MS
// Memory: 4396K

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
const int N = 50 + 5, INF = 1E9, SP = 100, PS = 150;
int G[N][N];
inline void up(int& a, int b) { a = min(a, b); }
int A[PS + 1][N][N], B[SP + 1][N][N];
int n, m;

void mul(int a[N][N], int b[N][N], int c[N][N]) {
    FOR (i, 0, n) FOR (j, 0, n) c[i][j] = INF;
    FOR (i, 0, n)
        FOR (j, 0, n)
             FOR (k, 0, n)
                  up(c[i][j], a[i][k] + b[k][j]);

}

int go(int u, int v, int a[N][N], int b[N][N]) {
    int ret = INF;
    FOR (i, 0, n) up(ret, a[u][i] + b[i][v]);
    return ret == INF ? -1 : ret;
}

void prt(int A[N][N]) {
#ifdef zerol
    FOR (i, 0, n)
        FOR (j, 0, n)
             printf("%d%c", A[i][j], j == _j - 1 ? '\n' : ' ');
#endif
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
#endif
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        FOR (i, 0, n) FOR (j, 0, n) G[i][j] = INF;
        FOR (i, 0, n) FOR (j, 0, n) A[0][i][j] = B[0][i][j] = INF;
        FOR (i, 0, n) A[0][i][i] = B[0][i][i] = 0;


        FOR (_, 0, m) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w); --u; --v;
            up(G[u][v], w);
        }


        FOR (i, 1, PS + 1)
            mul(A[i - 1], G, A[i]);

        FORD (k, PS - 1, 0)
            FOR (i, 0, n)
                FOR (j, 0, n)
                    up(A[k][i][j], A[k + 1][i][j]);


        FOR (i, 1, SP + 1)
            mul(B[i - 1], A[SP], B[i]);
        int Qn; cin >> Qn;
        while (Qn--) {
            int u, v, k; scanf("%d%d%d", &u, &v, &k); --u; --v;
            printf("%d\n", go(u, v, A[k % SP], B[k / SP]));
        }
    }
}