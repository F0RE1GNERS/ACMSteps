// [Auto Archived]
// Submit: 2017-07-27 23:03:53
// Time: 1419MS
// Memory: 6252K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int modn = 1e9 + 7;
const int N = 1e5 + 10;
typedef pair<int, int> pii;
int mu[N], prime[N], vis[N], cnt, n, a[N];
int b[3*N], s[3*N];
vector<pii> mu2;

void mobius() {
    memset(vis, 0, sizeof vis);
    mu[1] = 1;
    int cnt = 0;
    for(int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[cnt++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < cnt && i*prime[j] < N; j++) {
            vis[i*prime[j]] = 1;
            if (i%prime[j])
                mu[i*prime[j]] = -mu[i];
            else {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    for (int i = 2; i < N; ++i)
        if (mu[i])
            mu2.push_back({i, -mu[i]});
}

int pown(int x, int y) {
    if (y == 0) return 1;
    else if (y == 1) return x % modn;
    int res = pown(x, y / 2);
    res = 1LL * res * res % modn;
    if (y & 1) res = 1LL * res * x % modn;
    return res;
}

int main() {
    mobius();
    // for (auto i: mu2)
    //     printf("%d %d\n", i.first, i.second);
    int kases;
    scanf("%d", &kases);
    for (int kase = 1; kase <= kases; ++kase) {
        scanf("%d", &n);
        memset(b, 0, sizeof b);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &a[i]);
            b[a[i]]++;
        }
        for (int i = 1; i < 3*N; ++i)
            s[i] = s[i - 1] + b[i];
        int ans = 0;
        for (auto m: mu2) {
            int &coe = m.second;
            int &divider = m.first;
            int lans = 1; int exist = 0;
            for (int j = 0; divider * j < N; ++j) {
                int count = s[divider * j + divider - 1] - (j == 0 ? 0 : s[divider * j - 1]);
                lans = 1LL * lans * pown(j, count) % modn;
                if (count > 0) exist = 1;
            }
            if (exist) ans = (1LL * ans + coe * lans + modn) % modn;
        }
        printf("Case #%d: %d\n", kase, ans);
    }
}
