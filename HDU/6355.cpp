// [Auto Archived]
// Submit: 2018-08-07 18:21:21
// Time: 2059MS
// Memory: 20000K

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
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

const int MOD = 1E9 + 7;
const int N = 1E2;

LL C[N][N];

LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}

LL inv(LL x, LL MOD) { return bin(x, MOD - 2, MOD); }

LL go(const vector<LL>& left, const vector<LL>& right, LL limit, const vector<LL>& poly) {
    int n = poly.size();
    vector<vector<LL>> left_pow(n, vector<LL>(left.size(), 1));
    vector<vector<LL>> right_pow(n, vector<LL>(right.size(), 1));
    FOR (i, 1, n) FOR (j, 0, left.size()) left_pow[i][j] = left[j] % MOD * left_pow[i - 1][j] % MOD;
    FOR (i, 1, n) FOR (j, 0, right.size()) right_pow[i][j] = right[j] % MOD * right_pow[i - 1][j] % MOD;
    FOR (i, 0, n) FOR (j, 1, right.size()) (right_pow[i][j] += right_pow[i][j - 1]) %= MOD;
    // left is single, right is perfix

    int y = (int) right.size() - 1;
    LL res = 0;
    FOR (x, 0, left.size()) {
        while (y >= 0 && left[x] + right[y] > limit) y--;
        if (y < 0) break;
        // dbg(x, y);
        FOR (i, 0, n) FOR (j, 0, n - i)
            res = (res + poly[i + j] * left_pow[i][x] % MOD * right_pow[j][y] % MOD * C[i + j][i]) % MOD;
    }
    return res;
}

void init() {
    C[0][0] = 1;
    FOR (i, 1, N) {
        C[i][0] = 1;
        FOR (j, 1, N) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}

int main() {
    init();
    int T; cin >> T;
    init();
    while (T--) {
        int n; cin >> n;
        vector<LL> p(n);
        FOR (i, 0, n) cin >> p[i];
        LL M = (accumulate(p.begin(), p.end(), 0LL) + n) / 2;
        vector<LL> poly(n); poly[0] = 1;
        FOR (i, 1, n) {
            vector<LL> tmp(n);
            FOR (j, 0, n) tmp[j] = (M - i + MOD) % MOD * poly[j] % MOD;
            FOR (j, 0, n - 1) (tmp[j + 1] += poly[j] * (MOD - 1) % MOD) %= MOD;
            poly.swap(tmp);
        }
        // dbg(poly);
        LL nfac1 = 1; FOR (i, 1, n) nfac1 = (nfac1 * i) % MOD;
        nfac1 = inv(nfac1, MOD);
        FOR (i, 0, n) poly[i] = poly[i] * nfac1 % MOD;
        // naive
        LL ans2 = 0;
        // if (n <= 16) {
        //     FOR (i, 0, 1 << n) {
        //         LL x = 0;
        //         FOR (j, 0, n) if ((1 << j) & i) x += p[j];
        //         bool negative = __builtin_popcount(i) % 2;
        //         if (x > M - 1) continue;
        //         LL s = 0;
        //         FORD (i, n - 1, -1) s = (s * (x % MOD) + poly[i]) % MOD;
        //         if (negative) ans2 = (ans2 - s + MOD) % MOD;
        //         else ans2 = (ans2 + s) % MOD;
        //         // dbg(s, negative, ans2);
        //     }
        // }

        int mid = n / 2;
        int midrest = n - mid;
        vector<vector<LL>> left(2, vector<LL>());
        vector<vector<LL>> right(2, vector<LL>());
        FOR (i, 0, 1 << mid) {
            LL x = 0;
            FOR (j, 0, mid) if ((1 << j) & i) x += p[j];
            left[__builtin_popcount(i) % 2].push_back(x);
        }
        FOR (i, 0, 1 << midrest) {
            LL x = 0;
            FOR (j, 0, midrest) if ((1 << j) & i) x += p[mid + j];
            right[__builtin_popcount(i) % 2].push_back(x);
        }
    
        // dbg(M);
        // dbg(left[0]);
        // dbg(left[1]);
        // dbg(right[0]);
        // dbg(right[1]);

        LL ans = 0;
        FOR (l, 0, 2) FOR (r, 0, 2) {
            // dbg(l, r);
            sort(left[l].begin(), left[l].end());
            sort(right[r].begin(), right[r].end());
            LL g = go(left[l], right[r], M - 1, poly);
            if ((l + r) % 2) (ans = ans + MOD - g) % MOD;
            else ans = (ans + g) % MOD;
        }
        // if (n <= 16)
        //     assert (ans == ans2);

        cout << ans << endl;
        // cout << ans2 << endl;
    }
}
