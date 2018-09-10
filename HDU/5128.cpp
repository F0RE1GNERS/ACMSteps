// [Auto Archived]
// Submit: 2016-10-23 15:59:33
// Time: 15MS
// Memory: 1816K

#include <bits/stdc++.h>
using namespace std;

struct Vec {
    int x;
    int y;
    // bool operator < (const Vec v) const {
    //     return x < v.x || (x == v.x && y < v.y);
    // }
};

bool is_in_interval(int x, int l, int r) {
    return x > l && x < r;
}

Vec vecs[250];
int vis[250][250];
int n,ans;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    while (~scanf("%d",&n) && n) {
        for (int i = 0; i < n; ++i)
            scanf("%d%d",&vecs[i].x,&vecs[i].y);
        //sort(vecs,vecs+n);
        memset(vis,0,sizeof(vis));
        for (int i = 0; i < n; ++i)
            vis[vecs[i].x][vecs[i].y] = 1;
        ans = -1;
        for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        for (int k = 0; k < n; ++k)
        for (int l = 0; l < n; ++l)
        {
            if (vecs[i].x < vecs[j].x && vecs[i].y < vecs[j].y &&
                vecs[k].x < vecs[l].x && vecs[k].y < vecs[l].y)
            {
                int x1 = vecs[i].x;
                int x2 = vecs[j].x;
                int y1 = vecs[i].y;
                int y2 = vecs[j].y;
                int x3 = vecs[k].x;
                int x4 = vecs[l].x;
                int y3 = vecs[k].y;
                int y4 = vecs[l].y;
                if (!vis[x1][y1] || !vis[x1][y2] || !vis[x2][y1] || !vis[x2][y2]) continue;
                if (!vis[x3][y3] || !vis[x3][y4] || !vis[x4][y3] || !vis[x4][y4]) continue;
                if (is_in_interval(x1,x3,x4) && is_in_interval(x2,x3,x4) &&
                    is_in_interval(y1,y3,y4) && is_in_interval(y2,y3,y4))
                    ans = (x4-x3)*(y4-y3);
                if (is_in_interval(x3,x1,x2) && is_in_interval(x4,x1,x2) &&
                    is_in_interval(y3,y1,y2) && is_in_interval(y4,y1,y2))
                    ans = (x2-x1)*(y2-y1);
                if (x3 >= x1 && x3 <= x2 && y3 >= y1 && y3 <= y2) continue;
                if (x3 >= x1 && x3 <= x2 && y4 >= y1 && y4 <= y2) continue;
                if (x4 >= x1 && x4 <= x2 && y3 >= y1 && y3 <= y2) continue;
                if (x4 >= x1 && x4 <= x2 && y4 >= y1 && y4 <= y2) continue;
                if (x1 >= x3 && x1 <= x4 && y1 >= y3 && y1 <= y4) continue;
                if (x1 >= x3 && x1 <= x4 && y2 >= y3 && y2 <= y4) continue;
                if (x2 >= x3 && x2 <= x4 && y1 >= y3 && y1 <= y4) continue;
                if (x2 >= x3 && x2 <= x4 && y2 >= y3 && y2 <= y4) continue;
                // if ((x2-x1)*(y2-y1)+(x4-x3)*(y4-y3) > ans)
                //     printf("%d %d %d %d\n",i,j,k,l);
                ans = max(ans,(x2-x1)*(y2-y1)+(x4-x3)*(y4-y3));
            }
        }
        // if (i != k && vecs[i].x < vecs[j].x && vecs[i].y < vecs[j].y &&
        //     vecs[k].x < vecs[l].x && vecs[k].y < vecs[l].y) {
        //     if (vis[vecs[i].x][vecs[j].y] && vis[vecs[j].x][vecs[i].y] &&
        //         vis[vecs[k].x][vecs[l].y] && vis[vecs[l].x][vecs[k].y])
        //         ans = max(ans,(vecs[j].y-vecs[i].y)*(vecs[j].x-vecs[i].x)+
        //             (vecs[l].y-vecs[k].y)*(vecs[l].x-vecs[k].x));
        // }
        if (ans == -1) printf("imp\n");
        else printf("%d\n",ans);
    }
    return 0;
}
