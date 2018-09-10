// [Auto Archived]
// Submit: 2016-10-31 20:14:22
// Time: 483MS
// Memory: 1944K

#include <bits/stdc++.h>
using namespace std;

int kases,n,a[100010];
long long ans;
const double eps = 1e-9;
int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++i)
            scanf("%d",&a[i]);
        for (int i = n-1; i > 0; --i)
            a[i] = a[i] - a[i-1];
        ans = 0;
        double sp = 1e18;
        for (int i = n-1; i >= 0; --i) {
            long long t = (long long)((a[i] - eps) / sp) + 1;
            ans += t;
            sp = (double)a[i] / t;
            //cout << t << " " << sp << endl;
            //printf("%Lf %Lf\n",t,sp);
        }
        printf("Case #%d: %ld\n",kase,ans);
    }
    return 0;
}