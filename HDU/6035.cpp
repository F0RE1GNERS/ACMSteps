// [Auto Archived]
// Submit: 2017-07-26 14:14:32
// Time: 1201MS
// Memory: 22152K

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 250000;
vector<int> g[N];
int n, vis[N], c[N], sum[N], sz[N], blocks[N], samesize[N];
LL ans;

// sum[i]: how large the subtrees, with color i heads, are, already
// samesize[i]: what is the largest same color subtree of subtree is, for node i

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

void push_block(int color, int sz, int same = 0) {
    if (sz) {
        ans += 1LL * sz * blocks[color];
        // printf("%d %d ans=%lld\n", color, sz, ans);
        if (same) ans += 1LL * sz * (sz - 1) / 2;
        blocks[color] += sz;
    }
    // if (sz) {
    //     blocks[color].push_back(sz);
    // }
}

void dfs(int u) {
    vis[u] = 1;
    sz[u] = 1;
    samesize[u] = 1;
    for (int v: g[u]) {
        if (vis[v]) continue;
        int s1 = sum[c[u]];
        dfs(v);
        if (c[u] == c[v])
            samesize[u] += samesize[v];
        sz[u] += sz[v];
        int ds = sum[c[u]] - s1;  // how large is the subtreees in v subtree
        int block = sz[v] - ds;
        push_block(c[u], block);  // this block is stopped by node u
        sum[c[u]] += block;
        if (c[u] != c[v])
            push_block(c[v], samesize[v], 1);  // this block is stopped here
    }
    sum[c[u]]++;
}

int main() {
    int kase = 0;
    while (~scanf("%d", &n)) {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &c[i]);
        for (int i = 1; i <= n; ++i) {
            g[i].clear();
            // blocks[i].clear();
        }
        memset(sum, 0, sizeof sum);
        memset(sz, 0, sizeof sz);
        memset(vis, 0, sizeof vis);
        memset(samesize, 0, sizeof samesize);
        memset(blocks, 0, sizeof blocks);
        for (int i = 0; i < n - 1; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            add_edge(x, y);
        }
        ans = 0;
        dfs(1);
        for (int i = 1; i <= n; ++i)
            push_block(i, sz[1] - sum[i]);
        push_block(c[1], samesize[1], 1);
        // for (int i = 1; i <= n; ++i) {
        //     for (int u: blocks[i]) printf("%d ", u);
        //     printf("\n");
        // }
        printf("Case #%d: %lld\n", ++kase, ans);
    }
}