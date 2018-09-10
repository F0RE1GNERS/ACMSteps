// [Auto Archived]
// Submit: 2016-10-28 22:51:10
// Time: 15MS
// Memory: 1656K

#include <bits/stdc++.h>
using namespace std;

int T;
char s[100010];
long long ans;

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&T);
    for (int i = 0; i < T; ++i) {
        scanf("%s",s);
        int n = strlen(s);
        ans = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] != 'q')
                continue;
            int j = i;
            while (j < n && s[j] == 'q') ++j;
            int len = j - i;
            ans += ((long long)len*(len+1))/2;
            i = j;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
