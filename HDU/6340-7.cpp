// [Auto Archived]
// Submit: 2018-08-03 16:54:31
// Time: 4071MS
// Memory: 25256K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

const int MOD = 998244353;
const int N = 3E5 + 100;
const int M = 6E5 + 100;
const int G = 3;

LL bin(LL x, LL n, LL MOD) {
    if (n < 0) return bin(bin(x, -n, MOD), MOD - 2, MOD);
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}

LL inv[M];
void inv_init(LL n, LL p) {
    inv[1] = 1;
    FOR (i, 2, n)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

LL invf[M], fac[M];
void fac_inv_init(LL n, LL p) {
    fac[0] = 1;
    FOR (i, 1, n)
        fac[i] = i * fac[i - 1] % p;
    invf[n - 1] = bin(fac[n - 1], p - 2, p);
    FORD (i, n - 2, -1)
        invf[i] = invf[i + 1] * (i + 1) % p;
}

int wn[25];
void getwn() {
    for (int i = 1; i <= 23; ++i) {
        int t = 1 << i;
        wn[i] = bin(G, (MOD - 1) / t, MOD);
    }
}

void change(int *y, int len) {
    for (int i = 1, j = len / 2; i < len - 1; ++i) {
        if (i < j) swap(y[i], y[j]);
        int k = len / 2;
        while (j >= k) { j -= k; k /= 2; }
        j += k;
    }
}

void NTT(int *y, int len, int on) {
    change(y, len);
    for (int id = 0, h = 2; h <= len; h <<= 1) {
        ++id;
        for (int j = 0; j < len; j += h) {
            for (int w = 1, k = j; k < j + h / 2; ++k) {
                int u = y[k];
                int t = 1LL * y[k + h / 2] * w % MOD;
                y[k] = u + t;
                if (y[k] >= MOD) y[k] -= MOD;
                y[k + h / 2] = u - t + MOD;
                if (y[k + h / 2] >= MOD) y[k + h / 2] -= MOD;
                w = 1LL * w * wn[id] % MOD;
            }
        }
    }
    if (on == -1) {
        for (int i = 1; i < len / 2; ++i) swap(y[i], y[len - i]);
        int inv = bin(len, MOD - 2, MOD);
        for (int i = 0; i < len; ++i)
            y[i] = 1LL * y[i] * inv % MOD;
    }
}

namespace BernoulliInit {
    const int P = 998244353; // 119 * 2 ^ 23 + 1
    const int G = 3;

    int B[N], a[N], tmp[N];

    void get_inv(int A[], int A0[], int t) {
        if (t == 1) { A0[0] = bin(A[0], P - 2, P); return; }
        get_inv(A, A0, t / 2);
        for (int i = 0; i < t; ++i) tmp[i] = A[i];
        for (int i = t; i < 2 * t; ++i) tmp[i] = 0;
        for (int i = t / 2; i < 2 * t; ++i) A0[i] = 0;
        NTT(tmp, 2 * t, 1); NTT(A0, 2 * t, 1);
        for (int i = 0; i < 2 * t; ++i) {
            tmp[i] = (2 - 1LL * tmp[i] * A0[i] % P) % P;
            if (tmp[i] < 0) tmp[i] += P;
            A0[i] = 1LL * A0[i] * tmp[i] % P;
        }
        NTT(A0, 2 * t, -1);
    }

    void init() {
        getwn();
        for (int i = 0; i < N - 1; ++i) a[i] = invf[i + 1];
        int len = 1 << 17; get_inv(a, B, len);
        for (int i = 0; i < len; ++i)
            B[i] = 1LL * B[i] * fac[i] % P;
    }
};

LL B[M];
void init() {
    inv_init(M, MOD);
    fac_inv_init(M, MOD);
    BernoulliInit::init();
    // B[0] = 1;
    // FOR (i, 1, 1000) {
    //     LL& s = B[i] = 0;
    //     FOR (j, 0, i)
    //         s += fac[i + 1] * invf[i + 1 - j] % MOD * invf[j] % MOD * B[j] % MOD;
    //     s = (s % MOD * -inv[i + 1] % MOD + MOD) % MOD;
    // }
    // FOR (i, 0, 10) dbg(i, B[i]);
    FOR (i, 0, 1 << 17) {
        // if (i < 500) assert (B[i] == BernoulliInit::B[i]);
        B[i] = BernoulliInit::B[i];
    }
    B[1] = (MOD + 1) / 2; // patch for B+
}

LL G1[M];
LL p[N], a[N];

LL A(LL p, LL i) {
    return fac[p] * invf[p + 1 - i] % MOD * invf[i] % MOD * B[p + 1 - i] % MOD;
}

namespace NTTConv {
    const int MAXN = 6E5 + 100;
    int N, a[MAXN], b[MAXN];

    void conv(int *s, int *t, int n, int *result) {
        N = 1; while (N < n * 2) N *= 2;
        memset(a, 0, sizeof (int) * N);
        memset(b, 0, sizeof (int) * N);
        copy(s, s + n, a); copy(t, t + n, b);
        NTT(a, N, 1);
        NTT(b, N, 1);
        for (int i = 0; i < N; ++i)
            a[i] = 1LL * a[i] * b[i] % MOD;
        NTT(a, N, -1);
        copy(a, a + N, result);
    }
};

int t1[N], t2[N], G2[N];

const int D = 0;

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        int K, m; cin >> K >> m;
        LL N = 1;
        FOR (i, 0, m) {
            cin >> p[i] >> a[i];
            N = N * bin(p[i], a[i], MOD) % MOD;
        }
        dbg(N);
        LL ans = 0;

        if (K > D) {
            fill(t1, t1 + 2 * K + 10, 0); fill(t2, t2 + 2 * K + 10, 0);
            FOR (jp, 0, K + 1) t1[jp] = B[jp] * invf[jp] % MOD;
            LL np = 1;
            FOR (k, 0, K + 2) {
                np = np * N % MOD;
                t2[k] = np * invf[k + 1] % MOD;
            }
            NTTConv::conv(t1, t2, K + 10, G2);
        }

        FOR (i, 0, K + 1) dbg("J", i, t1[i]);
        FOR (i, 0, K + 1) dbg("K", i, t2[i]);

        FOR (i, -1, K + 1) {
            G1[i + 1] = 0;
            LL post = B[i + 1] * invf[i + 1] % MOD;
            LL t = 1;
            FOR (j, 0, m)
                t = t * (1 - bin(p[j], i, MOD) + MOD) % MOD;
            if (K <= D) {
                FOR (j, 1, K + 2) FOR (k, 1, j + 2) {
                    if (j - k != i) continue;
                    LL d = B[K + 1 - j] % MOD * invf[K + 1 - j] % MOD * 
                           bin(N, k, MOD) % MOD * invf[k] % MOD;
                    G1[i + 1] += d;
                }
                G1[i + 1] %= MOD;
                ans += G1[i + 1] * post % MOD * t % MOD;
            } else {
                ans += G2[K - i] * post % MOD * t % MOD;
            }
        }
        cout << ans % MOD * fac[K] % MOD << endl;
    }

}
