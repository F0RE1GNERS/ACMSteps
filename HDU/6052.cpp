// [Auto Archived]
// Submit: 2017-07-28 10:00:20
// Time: 78MS
// Memory: 2916K

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef long long LL;

struct Node {
    int lineSize, lineNumber, ans;
};

int n, m;
int g[200][200];
int dp[200][200];
stack<Node> S;
vector<pii> color[20000];
double ans;

void dfs(vector<pii> &v, int N, int depth, int start, LL &res,
    int leftmost, int uppermost, int rightmost, int lowermost) {
    for (int i = start; i < N; ++i) {
        int _leftmost = min(leftmost, v[i].second);
        int _uppermost = min(uppermost, v[i].first);
        int _rightmost = max(rightmost, v[i].second);
        int _lowermost = max(lowermost, v[i].first);
        int lans = (_leftmost + 1) * (m - _rightmost) * (_uppermost + 1) * (n - _lowermost);
        res += (depth % 2 ? 1 : -1) * lans;
        dfs(v, N, depth + 1, i + 1, res, _leftmost, _uppermost, _rightmost, _lowermost);
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                scanf("%d", &g[i][j]);
                color[g[i][j]].push_back({i, j});
            }
        ans = 0;
        for (int i = 0; i < n * m; ++i) {
            if (color[i].empty())
                continue;
            if ((int) color[i].size() <= 13) {
                LL res = 0;
                dfs(color[i], (int) color[i].size(), 1, 0, res, 200, 200, -1, -1);
                // printf("%lld\n", res);
                ans += res;
            } else {
                LL res = 0;
                int &c = i;
                memset(dp, 0, sizeof dp);
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < m; ++j) {
                        if (g[i][j] != c)
                            dp[i+1][j+1] = dp[i+1][j] + 1;
                    }
                }
                for (int j = 0; j < m; ++j) {
                    while (!S.empty()) S.pop();
                    for (int i = 0; i < n; ++i) {
                        while (!S.empty() && S.top().lineSize >= dp[i+1][j+1])
                            S.pop();
                        int lans = 0;
                        if (S.empty())
                            lans = (i + 1) * dp[i+1][j+1];
                        else
                            lans = (i - S.top().lineNumber) * dp[i+1][j+1] + S.top().ans;
                        // if (lans && c == 2)
                        //     printf("%d %d %d\n", i, j, lans);
                        S.push((Node){dp[i+1][j+1], i, lans});
                        res += lans;
                    }
                }
                // printf("%lld\n", res);
                ans += ((n*(n+1)*(m+1)*m)/4) - res;
            }
            color[i].clear();
        }

        printf("%.9f\n", 1.0 * ans / ((n*(n+1)*(m+1)*m)/4));
    }
}