// [Auto Archived]
// Submit: 2015-12-06 09:12:57
// Time: 4914MS
// Memory: 17212K

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <cctype>
#include <sstream>
#include <cmath>
using namespace std;
typedef long long LL;

int dp[1000005][2][2];
int L,M,ans;

int main()
{
    while (scanf("%d%d",&L,&M)!=EOF)
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                dp[1][i][j] = dp[2][i][j] = 1%M;
        for (int i = 3; i <= L; ++i)
        {
            dp[i][0][1] = dp[i-1][0][0];
            dp[i][0][0] = (dp[i-1][1][0]+dp[i-1][0][0])%M;
            dp[i][1][0] = (dp[i-1][1][1]+dp[i-1][0][1])%M;
            dp[i][1][1] = dp[i-1][0][1];
        }
        ans = 0;
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                ans += dp[L][i][j];
        ans %= M;
        printf("%d\n",ans);
    }
    return 0;
}