// [Auto Archived]
// Submit: 2017-05-06 00:02:29
// Time: 31MS
// Memory: 1564K

#include <bits/stdc++.h>
using namespace std;

int n, m, q;
int c[20][20];
int ans;

int check(int x, int y, int dx, int dy) {
    int cnt = 0;
    for (x -= dx, y -= dy; x >= 0 && y >= 0; x -= dx, y -= dy) {
        if (c[x][y]) cnt++;
        if (cnt == 2) {
            if (c[x][y] == 2) return 1;
            return 0;
        }
    }
    return 1;
}

void dfs(int u, int s) {
    if (u >= n * m) {
        ans = max(ans, s);
        return;
    }
    int i = u / m;
    int j = u % m;
    if (c[i][j] == 0 && check(i, j, 1, 0) && check(i, j, 0, 1)) {
        c[i][j] = 1;
        dfs(u + 1, s + 1);
        c[i][j] = 0;
    }
    dfs(u + 1, s);
}

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    #endif

    while (~scanf("%d%d%d", &n, &m, &q)) {
        memset(c, 0, sizeof c);
        ans = 0;
        for (int i = 0; i < q; ++i) {
            int a, b;
            scanf("%d%d", &a, &b);
            c[a][b] = 2;
        }
        dfs(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}

