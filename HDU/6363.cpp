// [Auto Archived]
// Submit: 2018-08-08 14:12:26
// Time: 78MS
// Memory: 24908K

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
void err() { cout << "" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
const int N = 2E6 + 100;
const int MOD = 1e9+7;

int fac[N];
int ivf[N];
int cnt;
int v[N];
int f[N];
int g[N];
int fib[N];

int pown(int a, int b, int mod) {
    int ret = 1;
    while(b){
        if(b&1) ret = 1LL * ret * a % mod;
        a = 1LL * a * a % mod;
        b>>=1;
    }
    return ret;
}

int inv(int a, int mod) {
    return pown(a, mod-2, mod);
}

void init() {
    fac[0] = 1;
    FOR(i, 1, N) fac[i] = 1LL*fac[i-1]*i%MOD;
    ivf[N-1] = inv(fac[N-1], MOD);
    FORD(i, N-2, -1) ivf[i] = 1LL*ivf[i+1]*(i+1)%MOD;
    fib[1] = 1;
    FOR(i, 2, N) fib[i] = (fib[i-1]+fib[i-2])%(MOD-1);
}

int C(int n, int m) {
    return 1LL*fac[n]*ivf[n-m]%MOD*ivf[m]%MOD;
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        int n, k; cin >> n >> k; cnt = 0;
        for(int i = 1; i*i<=n; ++i) {
            if(n%i==0) {
                v[cnt++] = i;
                if(i*i!=n) v[cnt++] = n/i;
            }            
        }
        sort(v, v+cnt);
        FOR(i, 0, cnt) {
            int G = v[i];
            int m = n/G;
            f[i] = C(m+k-1, k-1);
            dbg("f", v[i], f[i]);
        }
        FORD(i, cnt-1, -1) {
            g[i] = f[i];
            FOR(j, i+1, cnt) if(v[j]%v[i]==0) g[i] = (g[i]-g[j])%MOD;
            if(g[i]<0) g[i]+=MOD;
        }
        int ans = 0;
        FOR(i, 0, cnt) {
            dbg("g", v[i], g[i]);
            ans = (ans + 1LL*g[i] * pown(2, fib[v[i]], MOD)) % MOD;
        }
        ans = 1LL*ans*inv(f[0], MOD) % MOD;
        ans = (ans + MOD-1)%MOD;
        cout << ans << endl;
    }
}
