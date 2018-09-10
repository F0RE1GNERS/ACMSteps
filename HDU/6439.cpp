// [Auto Archived]
// Submit: 2018-08-30 09:43:37
// Time: 1419MS
// Memory: 38220K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "DEBUG: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

const LL MOD = 1E9 + 7;
const int M = 100;

const LL p_max = 1E6 + 100;
int prime[p_max], p_sz, mu[p_max], minp[p_max], basep[p_max];
bool p_vis[p_max];
LL inv[M], C[M][M], B[M];

LL n, x, A;

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

void prime_init() {
    mu[1] = 1;
    FOR (i, 2, p_max) {
        if (!p_vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
            minp[i] = i; basep[i] = i;
        }
        static LL d;
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            p_vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                minp[d] = minp[i] * prime[j];
                basep[d] = prime[j];
                break;
            } else {
                mu[d] = -mu[i];
                minp[d] = prime[j];
                basep[d] = prime[j];
            }
        }
    }
}

void inv_init(LL n, LL p) {
    inv[1] = 1;
    FOR (i, 2, n)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

void init_C(int n) {
    FOR (i, 0, n) {
        C[i][0] = C[i][i] = 1;
        FOR (j, 1, i)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
}

void init() {
    inv_init(M, MOD);
    init_C(M);
    B[0] = 1;
    FOR (i, 1, M - 1) {
        LL& s = B[i] = 0;
        FOR (j, 0, i)
            s += C[i + 1][j] * B[j] % MOD;
        s = (s % MOD * -inv[i + 1] % MOD + MOD) % MOD;
    }
}

LL bsum(LL k, LL n) {
    // k should be less than M
    // return Sum[i^k, {i, 1, n}], time complexity O(k)
    assert (k >= 0 && k < M);
    LL ret = 0;
    static LL p[M] = {1};
    n %= MOD;
    FOR (i, 1, k + 2)
        p[i] = p[i - 1] * (n + 1) % MOD;
    FOR (i, 1, k + 2)
        ret += C[k + 1][i] * B[k + 1 - i] % MOD * p[i] % MOD;
    ret = ret % MOD * inv[k + 1] % MOD;
    if (k == 0) ret = (ret + MOD - 1) % MOD; // 0^0 = 1
    return ret;
}

LL factor[30], f_sz;
void get_factor(LL x) {
    f_sz = 0;
    LL t = sqrt(x + 0.5);
    for (LL i = 0; prime[i] <= t; ++i)
        if (x % prime[i] == 0) {
            factor[f_sz++] = prime[i];
            while (x % prime[i] == 0) x /= prime[i];
        }
    if (x > 1) factor[f_sz++] = x;
}

namespace Solution1 {
    LL solve() {
        LL ans = 0, C = x;
        get_factor(A);
        function<void(LL, LL, LL)> dfs = [&](LL k, LL x, LL sgn) {
            if (k == f_sz) ans = ans + sgn * bsum(C, n / x);
            else {
                dfs(k + 1, x, sgn); dfs(k + 1, x * factor[k], -sgn);
            }
        };
        dfs(0, 1, 1);
        return (ans % MOD + MOD) % MOD;
    }
}

namespace Solution2 {
    int maxn = p_max;
    LL G[p_max], Gsum[p_max], b[p_max];
    LL mem[p_max * 2];
    LL B;
    inline LL id(LL x) { return x <= B ? x : (n / x) + B; }


    void G_init() {
        G[0] = 0; G[1] = Gsum[1] = 1;
        b[0] = bin(0, x, MOD); b[1] = bin(1, x, MOD);
        FOR (i, 2, maxn) {
            if (minp[i] == i) {
                b[i] = bin(i, x, MOD);
                G[i] = (b[i] + MOD - b[i / basep[i]]) % MOD;
            } else {
                b[i] = b[minp[i]] * b[i / minp[i]] % MOD;
                G[i] = G[minp[i]] * G[i / minp[i]] % MOD;
            }
            Gsum[i] = (Gsum[i - 1] + G[i]) % MOD;
        }
    }

    LL go(LL n) {
        // return Sum[G[i], {i, 1, n}]
        if (n < maxn) return Gsum[n];
        LL& res = mem[id(n)];
        if (res == -1) {
            LL all = bsum(x, n);
            LL red = 0;
            for (LL p = 2; p <= n; ) {
                LL len = n / (n / p) - p + 1;
                (red += len * go(n / p)) %= MOD;
                p += len;
            }
            // dbg(n, all, red);
            res = (all - red + MOD) % MOD;
        }
        return res;
    }

    LL solve() {
        B = sqrt(n + 0.5);
        maxn = round(pow(n, 0.666));
        G_init();
        memset(mem, -1, sizeof(LL) * (2 * B + 2));
        return go(n);
    }
}

int main() {
    init(); prime_init();
    int T; cin >> T; int cas = 0;
    int K, a[100];
    while (T--) {
        cin >> K >> n;
        x = 0; A = 0;
        FOR (i, 0, K) {
            cin >> a[i];
            if (a[i] == -1) x++;
            else if (a[i] > 0) A = __gcd(A, LL(a[i]));
        }
        printf("Case #%d: ", ++cas);
        if (A > 0) cout << Solution1::solve() << endl;
        else cout << Solution2::solve() << endl;
    }
    return 0;
}