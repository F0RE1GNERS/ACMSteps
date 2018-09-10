// [Auto Archived]
// Submit: 2017-08-02 13:01:42
// Time: 1138MS
// Memory: 10836K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 4e5 + 10;
const int MOD = 998244353;
const int G = 3;

int n, m, N, a[MAXN], b[MAXN], c[MAXN];
int fac[MAXN], invfac[MAXN], u[MAXN], v[MAXN];
int w[MAXN], u1[MAXN], apow[MAXN], apowinv[MAXN];

int quick_pow(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a % MOD;
    int res = quick_pow(a, b / 2);
    res = 1LL * res * res % MOD;
    if (b & 1) res = 1LL * res * a % MOD;
    return res;
}

void ntt(int * a, int N, int f) {
    int i, j = 0, t, k;
    for (i = 1; i < N - 1; i++) {
        for (t = N; j ^= t >>= 1, ~j & t;);
        if (i < j) {
            swap(a[i], a[j]);
        }
    }
    for (i = 1; i < N; i <<= 1) {
        t = i << 1;
        int wn = quick_pow(G, (MOD - 1) / t);
        for (j = 0; j < N; j += t) {
            int w = 1;
            for (k = 0; k < i; k++, w = 1LL * w * wn % MOD) {
                int x = a[j + k], y = 1LL * w * a[j + k + i] % MOD;
                a[j + k] = (x + y) % MOD, a[j + k + i] = (x - y + MOD) % MOD;
            }
        }
    }
    if (f == -1) {
        reverse(a + 1, a + N);
        int inv = quick_pow(N, MOD - 2);
        for (i = 0; i < N; i++)
            a[i] = 1LL * a[i] * inv % MOD;
    }
}

int main() {
    fac[0] = fac[1] = invfac[0] = invfac[1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
        invfac[i] = quick_pow(fac[i], MOD - 2);
    }
    while (~scanf("%d", &n)) {
        for (int i = 0; i <= n; ++i)
            scanf("%d", &c[i]);
        for (N = 1; N <= 2 * n; N <<= 1);
        LL A = 0;
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            scanf("%d", &a[i]);
            A += a[i];
        }
        A = (MOD - A % MOD) % MOD;
        apow[0] = apowinv[0] = 1;
        for (int i = 1; i <= N; ++i) {
            apow[i] = 1LL * apow[i - 1] * A % MOD;
            apowinv[i] = quick_pow(apow[i], MOD - 2);
        }

        // brute force
        // memset(u1, 0, sizeof u1);
        // for (int i = 0; i <= n; ++i) {
        //     for (int j = 0; j <= i; ++j) {
        //         u1[j] = (u1[j] + 1LL * c[i] * fac[i] % MOD * invfac[j] % MOD * invfac[i - j] % MOD * quick_pow(A, i - j)) % MOD;
        //     }
        // }
        // for (int j = 0; j <= n; ++j) {
        //     for (int i = j; i <= n; ++i) {
        //         u1[j] = (u1[j] + 1LL * c[i] * fac[i] % MOD * invfac[j] % MOD * invfac[i - j] % MOD * quick_pow(A, i - j)) % MOD;
        //     }
        // }
        // for (int i = 0; i <= n; ++i)
        //     printf("%d ", u1[i]);
        // puts("");

        memset(u, 0, sizeof u);
        memset(v, 0, sizeof v);
        for (int i = 0; i <= n; ++i) {
            u[i] = 1LL * c[i] * fac[i] % MOD * quick_pow(A, i) % MOD;
            w[i] = invfac[i];
            // printf("%d %d\n", u[i], w[i]);
        }

        // brute force 2
        // for (int t = 0; t <= n; ++t) {
        //     int xx = 0;
        //     for (int i = t; i <= n; ++i)
        //         xx = (xx + 1LL * u[i] * w[i - t]) % MOD;
        //     printf("%lld ", (1LL * xx * quick_pow(quick_pow(A, t), MOD - 2) * invfac[t] % MOD));
        // }
        // puts("");

        for (int i = 0; i <= n; ++i)
            v[i] = w[n - i];
        ntt(u, N, 1);
        ntt(v, N, 1);
        for (int i = 0; i < N; ++i)
            u[i] = 1LL * u[i] * v[i] % MOD;
        ntt(u, N, -1);
        for (int t = 0; t <= n; ++t) {
            int z = u[n + t];
            z = (1LL * apowinv[t] * invfac[t] % MOD * z) % MOD;
            // if (z != u1[t]) printf("%d %d\n", z , u1[t]);

            // assert (z == u1[t]);
            printf("%d ", z);
        }
        puts("");
    }
}