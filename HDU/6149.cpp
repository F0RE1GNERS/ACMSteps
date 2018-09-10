// [Auto Archived]
// Submit: 2017-08-18 20:37:46
// Time: 592MS
// Memory: 21280K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int modn = 1e9 + 7;

int mat[50][50];
int n, m, k, h[50];
int ans;
vector<int> S[50];
vector<int> L, H;
int dp[50][100000];

int main() {
    int T; cin >> T;
    while (T--) {
        memset(mat, 0, sizeof mat);
        memset(h, 0, sizeof h);
        memset(dp, 0, sizeof dp);
        for (int i = 0; i < 50; ++i)
            S[i].clear();
        L.clear(); H.clear();
        ans = 0;
        cin >> n >> m >> k;
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            mat[u][v] = mat[v][u] = 1;
        }
        for (int i = 0; i < k; ++i) {
            int t; cin >> t;
            h[t] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            if (!h[i]) L.push_back(i);
            else H.push_back(i);
        }
        for (int k = 0; k < (int) L.size(); ++k) {
            for (int i = 0; i < (int) H.size(); ++i)
                for (int j = i + 1; j < (int) H.size(); ++j)
                    if (mat[L[k]][H[i]] && mat[L[k]][H[j]]) {
                        S[k].push_back((1 << i) + (1 << j));
                        // printf("%d %d %d\n", k, i, j);
                    }
        }
        int Lsize = (int) L.size();
        for (int i = 0; i < Lsize; ++i)
            for (int j = 0; j < (1 << 15); ++j) {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                for (int status: S[i]) {
                    if ((j & status) == 0)
                        dp[i + 1][j | status] = max(dp[i + 1][j | status], dp[i][j] + 1);
                }
            }
        int ans = 0;
        for (int j = 0; j < (1 << 15); ++j)
            ans = max(ans, dp[Lsize][j]);
        printf("%d\n", ans);
    }
}