// [Auto Archived]
// Submit: 2016-10-02 14:45:21
// Time: 140MS
// Memory: 5488K

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
int dp[1500000];
int p = 1e9;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    dp[0] = 1;
    for (int i = 1; i <= 1000000; i<<=1)
        for (int j = 0; j+i <= 1000000; ++j)
            dp[j+i] = (dp[j+i]+dp[j])%p;
    while (~scanf("%d",&n))
        printf("%d\n",dp[n]);
    return 0;
}