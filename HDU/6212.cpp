// [Auto Archived]
// Submit: 2017-09-18 10:02:38
// Time: 249MS
// Memory: 2668K

#include <bits/stdc++.h>
using namespace std;

const int N = 505, inf = (int) 1e9;
char s[N];

void mini(int &a, const int b) {
    if (b < a) a = b;
}

int n, m, a[N], b[N], f[N][N];

int main() {
    int T;
    scanf("%d", &T);
    for (int tt = 1; tt <= T; ++tt) {
        scanf("%s", s);
        m = strlen(s);
        n = 0;
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);
        memset(f, 0, sizeof f);
        for (int i = 0; i < m; ++i) {
            int x = s[i] - '0';
            if (n && x == a[n]) b[n]++;
            else a[++n] = x, b[n] = 1;
        }
        for (int i = n; i; i--) {
            f[i][i] = b[i] == 1 ? 2 : 1;
            for (int j = i + 1; j <= n; j++) {
                f[i][j] = inf;
                for (int k = i; k < j; k++)
                    mini(f[i][j], f[i][k] + f[k + 1][j]);
                if (a[i] == a[j]) {
                    mini(f[i][j], f[i + 1][j - 1] + (b[i] + b[j] == 2 ? 1 : 0));
                    if (b[i] == 1 || b[j] == 1)
                        for (int k = i + 1; k < j; k++)
                            if (b[k] == 1 && a[k] == a[i])
                                mini(f[i][j], f[i + 1][k - 1] + f[k + 1][j - 1]);
                }
            // printf("f[%d][%d]=%d\n", i, j, f[i][j]);
            }
        }
        printf("Case #%d: %d\n", tt, f[1][n]);
    }
    return 0;
}
