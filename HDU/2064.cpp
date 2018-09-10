// [Auto Archived]
// Submit: 2016-11-06 19:29:22
// Time: 15MS
// Memory: 1564K

#include <bits/stdc++.h>
using namespace std;

int n;
long long f[40];

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    f[0] = 0;
    for (int i = 1; i <= 35; ++i)
        f[i] = 3 * f[i-1] + 2;
    while (~scanf("%d",&n))
        printf("%lld\n",f[n]);
    return 0;
}
