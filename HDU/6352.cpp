// [Auto Archived]
// Submit: 2018-08-08 00:27:11
// Time: 1606MS
// Memory: 12320K

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

typedef pair<int, int> P;
typedef vector<P> VP;

const LL p_max = 1E5 + 100;
LL prime[p_max], p_sz, mu[p_max], phi[p_max];
bool p_vis[p_max];
vector<LL> factors[p_max];
void init() {
    mu[1] = 1;
    FOR (i, 2, p_max) {
        if (!p_vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        static LL d;
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            p_vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                phi[d] = phi[i] * prime[j];
                break;
            }
            else {
                mu[d] = -mu[i];
                phi[d] = phi[i] * (prime[j] - 1);
            }
        }
    }
    FOR (i, 0, p_sz) {
        // dbg(i, prime[i]);
        for (LL j = prime[i]; j < p_max; j += prime[i])
            factors[j].push_back(prime[i]);
    }
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        int nn; cin >> nn;
        vector<VP> ans;
        FOR (n, 1, nn + 1) {
            if (nn % n) continue;
            if (n == 1) ans.push_back({make_pair(1, 1), make_pair(0, -1)});
            else {
                vector<int> f(phi[n] + 1);
                f[0] = 1;
                auto& factor = factors[n];
                // dbg(n, factor);
                int p = factor.size();
                FOR (i, 0, 1 << p) {
                    LL exp = n;
                    FOR (j, 0, p) if ((1 << j) & i)
                        exp /= factor[j];
                    // dbg(exp, phi[n], __builtin_popcount(i) % 2);
                    if (__builtin_popcount(i) % 2) {
                        FOR (i, exp, phi[n] + 1)
                            f[i] += f[i - exp];
                    } else {
                        FORD (i, phi[n], exp - 1)
                            f[i] -= f[i - exp];
                    }
                    // dbg(f);
                }
                ans.emplace_back();
                FORD (i, phi[n], -1) if (f[i]) ans.back().emplace_back(i, f[i]);
            }
        }
        // random_shuffle(ans.begin(), ans.end());
        sort(ans.begin(), ans.end(), [](const VP& a, const VP& b) {
            int m = min(a.size(), b.size());
            FOR (i, 0, m) {
                if (a[i].first > b[i].first) return a[i].second < 0;
                if (a[i].first < b[i].first) return b[i].second > 0;
                if (a[i].second != b[i].second) return a[i].second < b[i].second;
            }
            if (int(a.size()) > m) return a[m].second < 0;
            if (int(b.size()) > m) return b[m].second > 0;
            return false;
        });
        for (auto r: ans) {
            bool first = true;
            putchar('(');
            for (auto x: r) {
                // dbg(x.first, x.second);
                if (!first || x.second < 0) putchar(x.second > 0 ? '+' : '-');
                if (abs(x.second) > 1 || x.first == 0) printf("%d", abs(x.second));
                if (x.first > 0) {
                    putchar('x');
                    if (x.first > 1) printf("^%d", x.first);
                }
                first = false;
            }
            putchar(')');
        }
        puts("");
    }
}
