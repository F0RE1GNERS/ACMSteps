// [Auto Archived]
// Submit: 2018-08-23 11:56:42
// Time: 2901MS
// Memory: 317136K

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

const unsigned N = 1E7 + 10;
const unsigned MOD = (1u << 30) - 1;

int mu[N], cc[N], np[N];
unsigned phi[N], g2[N], g3[N], pr[N], pc, f[N], minp[N];

void getphi() {
    phi[1] = 1; mu[1] = 1; g2[1] = 1; g3[1] = 1; f[1] = 1; minp[1] = 1;
    FOR (i, 2, N) {
        if (!np[i]) {
            pr[pc++] = i; phi[i] = i - 1u;
            mu[i] = -1; g2[i] = i; g3[i] = i; cc[i] = 1;
            f[i] = phi[i] - phi[1]; minp[i] = i;
        }
        FOR (j, 0, pc) {
            unsigned k = i * pr[j];
            if (k >= N) break;
            np[k] = true;
            if (i % pr[j] == 0) {
                phi[k] = phi[i] * pr[j];
                mu[k] = 0; g2[k] = g2[i]; g3[k] = g3[i];
                cc[k] = cc[i] + 1;
                if (cc[k] % 2 == 1) g2[k] = g2[k] * pr[j];
                if (cc[k] % 3 == 1) g3[k] = g3[k] * pr[j];
                minp[k] = minp[i] * pr[j];
                if (minp[k] == k) f[k] = - (f[i] + phi[i / pr[j]]) + phi[k];
                else f[k] = f[minp[k]] * f[k / minp[k]];
                break;
            } else {
                phi[k] = phi[i] * (pr[j] - 1);
                mu[k] = -mu[i]; cc[k] = 1;
                g2[k] = g2[i] * pr[j];
                g3[k] = g3[i] * pr[j];
                minp[k] = pr[j];
                f[k] = f[i] * f[pr[j]];
            }
        }
    }
}

// unsigned f2[N];
// void init() {
//     FOR (g, 1, N) {
//         for (int k = 1, x = g; x < N; x += g, ++k) {
//             if (mu[k] < 0) f2[x] -= phi[g];
//             else if (mu[k] > 0) f2[x] += phi[g];
//         }
//     }
// }

int main() {
    getphi();
    // init();
    // FOR (i, 0, 100) dbg(i, phi[i], mu[i], minp[i], f[i], f2[i]);
    // FOR (i, 0, N) assert (f[i] == f2[i]);
    int T; cin >> T;
    while (T--) {
        unsigned A, B, C, n; cin >> A >> B >> C; n = A;
        unsigned ans = 0;
        while (n >= 2 && (B < g2[n] || C < g3[n])) --n;
        FOR (g, 1, n + 1)
            ans += f[g] * (A / g) * (B / g2[g]) * (C / g3[g]);
        cout << (ans & MOD) << endl;
    }
    return 0;
}