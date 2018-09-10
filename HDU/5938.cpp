// [Auto Archived]
// Submit: 2016-10-30 23:54:14
// Time: 608MS
// Memory: 1572K

#include <bits/stdc++.h>
using namespace std;

char s[30];
int A[30];
long long dp[30];
int kases,n;
long long a,b,c,d,e,ans;

long long getnum(int i, int j) {
    long long res = 0;
    for (int k = i; k < j; ++k) {
        res = res * 10 + A[k];
    }
    return res;
}

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase) {
        scanf("%s",s);
        n = strlen(s);
        for (int i = 0; i < n; ++i)
            A[i] = s[i] - '0';
        ans = -1e18;
        for (int i = 0; i < 30; ++i)
            dp[i] = -1;
        for (int i = 1; i < n-3; ++i)
            for (int j = i+1; j < n-2; ++j) {
                a = getnum(0,i);
                b = getnum(i,j);
                if (dp[j] == -1) {
                    dp[j] = 8e18;
                    for (int k = j+1; k < n-1; ++k)
                        for (int l = k+1; l < n; ++l) {
                            c = getnum(j,k);
                            d = getnum(k,l);
                            e = getnum(l,n);
                            dp[j] = min(dp[j],c*d/e);
                        }
                }
                ans = max(ans,a+b-dp[j]);
            }
        printf("Case #%d: %lld\n",kase,ans);
    }
    return 0;
}
