// [Auto Archived]
// Submit: 2017-08-15 21:39:38
// Time: 109MS
// Memory: 3088K

#include <bits/stdc++.h>
using namespace std;
const int modn = 998244353;

int quick_pow(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a % modn;
    int res = quick_pow(a, b / 2);
    res = 1LL * res * res % modn;
    if (b & 1) res = 1LL * res * a % modn;
    return res;
}

int n, m;
char s[1200][1200];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        memset(s, 0, sizeof s);
        for (int i = 1; i <= n; ++i)
            scanf("%s", s[i] + 1);
        
        if (n == 1 && m == 1) {
            if (s[1][1] == '?') puts("1");
            else puts("0");
            continue;
        }

        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if ((i + j) % 2) {
                    if (s[i][j] == 'R') s[i][j] = 'B';
                    else if (s[i][j] == 'B') s[i][j] = 'R';
                }
            }

        int ans = 0, flag = 0, count = 0;
        for (int i = 1; i <= n; ++i) {
            char t = '?';
            for (int j = 1; j <= m; ++j) {
                if (s[i][j] != '?') {
                    if (t == '?') t = s[i][j];
                    else if (s[i][j] != t) {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag) break;
            if (t == '?') count++;
        }
        if (!flag) ans = (ans + quick_pow(2, count)) % modn;

        flag = 0; count = 0;
        for (int j = 1; j <= m; ++j) {
            char t = '?';
            for (int i = 1; i <= n; ++i) {
                if (s[i][j] != '?') {
                    if (t == '?') t = s[i][j];
                    else if (s[i][j] != t) {
                        flag = 1;
                        break;
                    }
                }
            }
            if (flag) break;
            if (t == '?') count++;
        }
        if (!flag) ans = (ans + quick_pow(2, count)) % modn;

        int rs = 1, bs = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j) {
                if (s[i][j] == 'R') rs = 0;
                else if (s[i][j] == 'B') bs = 0;
            }

        ans = (ans - rs - bs + modn) % modn;

        printf("%d\n", ans);
    }
}