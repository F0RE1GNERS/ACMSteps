// [Auto Archived]
// Submit: 2018-08-24 12:52:47
// Time: 733MS
// Memory: 28844K

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

const int N = 2E5 + 100;
const int MOD = 313;
LL n, a[N], dp[N];

typedef double LD;
const LD PI = acos(-1);
struct C {
    LD r, i;
    C(LD r = 0, LD i = 0): r(r), i(i) {}
};
C operator + (const C& a, const C& b) {
    return C(a.r + b.r, a.i + b.i);
}
C operator - (const C& a, const C& b) {
    return C(a.r - b.r, a.i - b.i);
}
C operator * (const C& a, const C& b) {
    return C(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}

void FFT(C x[], int n, int p) {
    for (int i = 0, t = 0; i < n; ++i) {
        if (i > t) swap(x[i], x[t]);
        for (int j = n >> 1; (t ^= j) < j; j >>= 1);
    }
    for (int h = 2; h <= n; h <<= 1) {
        C wn(cos(p * 2 * PI / h), sin(p * 2 * PI / h));
        for (int i = 0; i < n; i += h) {
            C w(1, 0), u;
            for (int j = i, k = h >> 1; j < i + k; ++j) {
                u = x[j + k] * w;
                x[j + k] = x[j] - u;
                x[j] = x[j] + u;
                w = w * wn;
            }
        }
    }
    if (p == -1)
        FOR (i, 0, n)
            x[i].r /= n;
}

void conv(C a[], C b[], int n) {
    FFT(a, n, 1);
    FFT(b, n, 1);
    FOR (i, 0, n)
        a[i] = a[i] * b[i];
    FFT(a, n, -1);
}

C res[N << 2], b[N << 2];

void go(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    go(l, mid);

    // FOR (i, mid + 1, r + 1)
    //     FOR (j, l, mid + 1)
    //         dp[i] += dp[j] * a[i - j];

    int n = 1; while (n < 2 * (r - l + 1)) n <<= 1;
    fill(res, res + n, 0); fill(b, b + n, 0);
    FOR (i, l, mid + 1) res[i - l] = dp[i];
    FOR (i, 1, r - l + 1) b[i] = a[i];
    conv(res, b, n);
    FOR (i, mid + 1, r + 1) (dp[i] += LL(round(res[i - l].r))) %= MOD;

    go(mid + 1, r);
}

int main() {
    while ((cin >> n) && n) {
        FOR (i, 1, n + 1) {
            scanf("%lld", a + i);
            a[i] %= MOD;
        }
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        // FOR (i, 1, n + 1) {
        //     FOR (j, 1, i + 1) dp[i] += a[j] * dp[i - j];
        // }
        go(0, n);
        cout << dp[n] << endl;
    }
    return 0;
}
