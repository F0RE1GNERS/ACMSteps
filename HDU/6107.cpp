// [Auto Archived]
// Submit: 2017-08-11 14:58:24
// Time: 483MS
// Memory: 52904K

#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
int T, n, w, q, pw, dw, a[N];
int hold[3][N];
int st1[20][N], st2[20][N];

int main() {
    scanf("%d", &T);
    // T = 1;
    while (T--) {
        scanf("%d%d%d%d", &n, &w, &pw, &dw);
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        for (int i = n; i < 2 * n; ++i)
            a[i] = 1e9;
        {
            memset(hold, 0, sizeof hold);
            memset(st1, -1, sizeof st1); memset(st1[0], 0, sizeof st1[0]);
            memset(st2, -1, sizeof st2); memset(st2[0], 0, sizeof st2[0]);
            for (int t = 0; t < 3; ++t) {
                int W = w;
                if (t == 1) W = dw;
                if (t == 2) W = w - pw - dw;
                int l = 0, r = 0, sum = -1;
                while (l < n) {
                    while (r < n && sum + a[r] + 1 <= W)
                        sum += a[r++] + 1;
                    hold[t][l] = r - l;
                    sum -= (a[l++] + 1);
                }
                // for (int i = 0; i < n; ++i)
                //     printf("%d ", hold[t][i]);
                // puts("hh");
            }
            for (int i = 0; i < n; ++i) {
                st1[0][i] = hold[0][i];
                st2[0][i] = hold[1][i] + hold[2][i + hold[1][i]];
            }
            for (int i = 1; (1 << i) <= n; ++i)
                for (int j = 0; j < n; ++j) {
                    if (st1[i - 1][j] > 0 && st1[i - 1][j + st1[i - 1][j]] > 0)
                        st1[i][j] = st1[i - 1][j] + st1[i - 1][j + st1[i - 1][j]];
                    if (st2[i - 1][j] > 0 && st2[i - 1][j + st2[i - 1][j]] > 0)
                        st2[i][j] = st2[i - 1][j] + st2[i - 1][j + st2[i - 1][j]];
                }
            // puts("st1");
            // for (int i = 0; (1 << i) <= n; ++i) {
            //     for (int j = 0; j < n; ++j)
            //         printf("%d ", st1[i][j]);
            //     puts("");
            // }
            // puts("st2");
            // for (int i = 0; (1 << i) <= n; ++i) {
            //     for (int j = 0; j < n; ++j)
            //         printf("%d ", st2[i][j]);
            //     puts("");
            // }
        }
        scanf("%d", &q);
        while (q--) {
            int xi, hi, ans, loc = 0, a2 = 0;  // loc is wordloc
            scanf("%d%d", &xi, &hi);
            xi--;
            ans = 0;
            while (loc < n && ans < xi) {
                int i = 0;
                while (loc + st1[i + 1][loc] <= n && st1[i + 1][loc] > 0 &&
                    ans + (1 << (i + 1)) <= xi) ++i;
                // printf("%d %d\n", loc, 1 << i);
                ans += (1 << i);
                loc += st1[i][loc];
                // printf("%d %d\n", loc, ans);
            }
            // printf("before %d\n", loc);
            while (loc < n && a2 < hi) {
                int i = 0;
                while (loc + st2[i + 1][loc] <= n && st2[i + 1][loc] > 0 &&
                    a2 + (1 << (i + 1)) <= hi) ++i;
                a2 += (1 << i);
                loc += st2[i][loc];
                if (!st2[i][loc]) break;
            }
            // printf("after %d\n", loc);
            ans += hi;
            while (loc < n) {
                int i = 0;
                while (loc + st1[i + 1][loc] <= n && st1[i + 1][loc] > st1[i][loc]) ++i;
                ans += (1 << i);
                loc += st1[i][loc];
            }
            printf("%d\n", ans);
        }
        // puts("hahaha");
    }
}