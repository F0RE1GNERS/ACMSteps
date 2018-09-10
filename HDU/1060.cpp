// [Auto Archived]
// Submit: 2016-09-14 21:35:45
// Time: 0MS
// Memory: 1584K

#include <bits/stdc++.h>
using namespace std;

int n,t;
long double ans;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    cin >> t;
    while (t--)
    {
        cin >> n;
        ans = n*log10l((long double)n);
        ans -= floor(ans);
        printf("%d\n",static_cast<int>(floor(pow(10,ans))));
    }
    return 0;
}
