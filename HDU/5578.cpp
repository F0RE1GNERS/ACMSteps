// [Auto Archived]
// Submit: 2016-12-04 22:12:43
// Time: 15MS
// Memory: 1560K

#include <bits/stdc++.h>
using namespace std;
char s[2000];
int ans, kases;
const int inf = 1e8;

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    #endif
    scanf("%d", &kases);
    for (int kase = 1; kase <= kases; ++kase) {
        scanf("%s", s);
        int n = strlen(s);
        ans = inf;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (s[i] == s[j])
                    ans = min(ans, j - i);
        printf("Case #%d: ", kase);
        if (ans == inf) printf("%d\n", -1);
        else printf("%d\n", ans);
    }
    return 0;
}
