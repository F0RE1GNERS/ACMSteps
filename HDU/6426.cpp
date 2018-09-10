// [Auto Archived]
// Submit: 2018-08-28 22:39:04
// Time: 1918MS
// Memory: 39192K

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

const int N = 6E5 + 100;
const int MOD = 998244353, G = 3;

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }

LL wn[N << 2], rev[N << 2];
int NTT_init(int n_) {
    int step = 0; int n = 1;
    for ( ; n < n_; n <<= 1) ++step;
    FOR (i, 1, n)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
    int g = bin(G, (MOD - 1) / n, MOD);
    wn[0] = 1;
    for (int i = 1; i <= n; ++i)
        wn[i] = wn[i - 1] * g % MOD;
    return n;
}

void NTT(LL a[], int n, int f) {
    FOR (i, 0, n) if (i < rev[i])
        std::swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            int t = n / (k << 1);
            FOR (j, 0, k) {
                LL w = f == 1 ? wn[t * j] : wn[n - t * j];
                LL x = a[i + j];
                LL y = a[i + j + k] * w % MOD;
                a[i + j] = (x + y) % MOD;
                a[i + j + k] = (x - y + MOD) % MOD;
            }
        }
    }
    if (f == -1) {
        LL ninv = get_inv(n, MOD);
        FOR (i, 0, n)
            a[i] = a[i] * ninv % MOD;
    }
}

LL A[N], B[N];
LL I2, I3, I4, I6, I8, I24;

void go(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2, len = r - l + 1;
    dbg(l, r, mid);
    go(l, mid);

    static LL a[N], b[N], b2[N], c[N];
    int n = NTT_init(2 * len);
    fill(a, a + n, 0); FOR (i, l, mid + 1) a[i - l] = A[i];
    fill(b, b + n, 0); FOR (i, 0, len) b[i] = A[i];
    fill(b2, b2 + n, 0); for (int i = 0; 2 * i < len; ++i) b2[2 * i] = A[i];
    NTT(a, n, 1); NTT(b, n, 1); NTT(b2, n, 1);

    FOR (i, l, mid + 1) {
        int j = i * 3 + 1;
        if (j > mid && j <= r) (A[j] += I3 * A[i]) %= MOD;
    }
    
    LL mul = l == 0 ? I6 : I2;
    FOR (i, 0, n) c[i] = b[i] * b[i] % MOD * a[i] % MOD;
    NTT(c, n, -1);
    FOR (i, mid + 1, r + 1) (A[i] += c[i - l - 1] * mul) %= MOD;

    FOR (i, 0, n) c[i] = a[i] * b2[i] % MOD;
    NTT(c, n, -1);
    FOR (i, mid + 1, r + 1) (A[i] += c[i - l - 1] * I2) %= MOD;

    go(mid + 1, r);
}

void finish(int maxq) {
    static LL a[N], a2[N], a3[N], b[N];
    int n = NTT_init(maxq * 4);
    for (int i = 0; i * 4 + 1 < maxq; ++i) (B[i * 4 + 1] += A[i] * I4) %= MOD;

    fill(a, a + n, 0); FOR (i, 0, maxq) a[i] = A[i];
    fill(a2, a2 + n, 0); for (int i = 0; i * 2 < maxq; ++i) a2[i * 2] = A[i];
    fill(a3, a3 + n, 0); for (int i = 0; i * 3 < maxq; ++i) a3[i * 3] = A[i];
    NTT(a, n, 1); NTT(a2, n, 1); NTT(a3, n, 1);

    FOR (i, 0, n) b[i] = a[i] * a[i] % MOD * a[i] % MOD * a[i] % MOD;
    NTT(b, n, -1); FOR (i, 0, n) (B[i + 1] += b[i] * I24) %= MOD;

    FOR (i, 0, n) b[i] = a2[i] * a2[i] % MOD;
    NTT(b, n, -1); FOR (i, 0, n) (B[i + 1] += b[i] * I8) %= MOD;

    FOR (i, 0, n) b[i] = a2[i] * a[i] % MOD * a[i] % MOD;
    NTT(b, n, -1); FOR (i, 0, n) (B[i + 1] += b[i] * I4) %= MOD;

    FOR (i, 0, n) b[i] = a[i] * a3[i] % MOD;
    NTT(b, n, -1); FOR (i, 0, n) (B[i + 1] += b[i] * I3) %= MOD;

    FOR (i, 0, n) b[i] = a[i] * a[i] % MOD;
    NTT(b, n, -1); FOR (i, 0, n) (B[i] += (MOD - b[i] * I2 % MOD)) %= MOD;

    FOR (i, 0, maxq) (B[i] += A[i]) %= MOD;
    for (int i = 0; i * 2 < maxq; ++i) (B[i * 2] += (A[i] * I2 % MOD)) %= MOD;
}


int main() {
    I2 = get_inv(2, MOD);
    I3 = get_inv(3, MOD);
    I4 = get_inv(4, MOD);
    I6 = get_inv(6, MOD);
    I8 = get_inv(8, MOD);
    I24 = get_inv(24, MOD);

    const int maxq = 1E5 + 100;
    A[0] = 1;
    // calc(0, 10);
    go(0, maxq);
    finish(maxq);
    int T; cin >> T;
    while (T--) {
        int n; scanf("%d", &n);
        printf("%d %d\n", B[n], A[n]);
    }
}