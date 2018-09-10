// [Auto Archived]
// Submit: 2016-10-26 22:55:18
// Time: 0MS
// Memory: 1584K

#include <bits/stdc++.h>
using namespace std;

int kases;
int h,m,s;
double a1,a2;
double X1,X2,Y1,Y2,ans;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&kases);
    while (kases--) {
        scanf("%d%d%d",&h,&m,&s);
        a1 = acos(-1.0) * 2 * (h / 12.0 + m / 60.0 / 12.0 + s / 60.0 / 12.0 / 60.0);
        a2 = acos(-1.0) * 2 * (m / 60.0 + s / 60.0 / 60.0);
        X1 = cos(a1); X2 = cos(a2);
        Y1 = sin(a1); Y2 = sin(a2);
        ans = (X1*X2+Y1*Y2) / (sqrt(X1*X1+Y1*Y1)*sqrt(X2*X2+Y2*Y2));
        ans = acos(ans) * 180 / acos(-1.0);
        printf("%d\n",(int)ans);
    }
    return 0;
}
