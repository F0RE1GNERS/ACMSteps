// [Auto Archived]
// Submit: 2018-08-03 10:19:16
// Time: 3026MS
// Memory: 78092K

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

const int N = 1E4 + 100;
const int M = 1E6 + 100;
const LL INF = 1E18 + 1E6;
const LL INF2 = 1E15;

int K = 233;

int divisors[N];

const LL p_max = 1E3 + 100;
LL prime[p_max], p_sz;
void get_prime() {
    static bool vis[p_max];
    FOR (i, 2, p_max) {
        if (!vis[i]) prime[p_sz++] = i;
        FOR (j, 0, p_sz) {
            if (prime[j] * i >= p_max) break;
            vis[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

pair<LL, int> a1[M], a2[M];
pair<LL, int> *ans = a1, *ansplus = a2;
int m;
vector<LL> res[300];

void clean_ans() {
    int p = 0;
    multiset<int> t;
    FOR (i, 0, m) {
        auto& e = ans[i];
        if ((int) t.size() == K + 1 && e.second < *t.begin())
            continue;
        ansplus[p++] = e;
        t.insert(e.second);
        if ((int) t.size() > K + 1)
            t.erase(t.begin());
    }
    m = p;
    swap(ans, ansplus);
}

void expand(int p) {
    FOR (i, 0, m) {
        auto& e = ans[i];
        LL q = e.first; int w = 0;
        while (q < INF2 || INF / p > q) {
            q = q * p; w++;
            ans[m++] = {q, e.second * (w + 1)};
        }
    }
    sort(ans, ans + m);
    // ans.insert(ansplus.begin(), ansplus.end());
}

int main() {
    get_prime();

    ans[m++] = {1, 1};
    FOR (i, 0, p_sz) {
        // auto t = ans;
        dbg(i, prime[i]);
        expand(prime[i]);
        clean_ans();
        if (prime[i] >= 350) break;
    }
    dbg(m);

    while (K >= 0) {
        clean_ans();
        FOR (i, 0, m) res[K].push_back(ans[i].first);
        dbg(K, res[K].size());
        K--;
    }

    int T; cin >> T;
    while (T--) {
        LL n; int k; scanf("%lld%d", &n, &k);
        LL l = 1, r = INF - 1;
        while (l < r) {
            LL mid = (l + r) / 2;
            int rem = upper_bound(res[k].begin(), res[k].end(), mid) - res[k].begin();
            if (mid - rem < n) l = mid + 1;
            else r = mid;
        }
        cout << l << endl;
    }
    
    // for (auto e: ans) cout << e.first << " " << e.second << endl;
}

void naive() {
    FOR (i, 1, N) {
        for (int j = i; j < N; j += i)
            divisors[j]++;
    }
    map<int, int> greater;
    set<int> S;
    FOR (i, 1, N) {
        int counter = 0;
        FOR (j, 1, i) if (divisors[j] > divisors[i]) {
            counter++;
            if (counter <= K) assert (S.count(j));
        }
        if (counter <= K) {
            int c = 0;
            for (auto e: greater) if (e.first > divisors[i]) c += e.second;
            S.insert(i);
            dbg(i, divisors[i], c);
            greater[divisors[i]]++;
        }
    }
}