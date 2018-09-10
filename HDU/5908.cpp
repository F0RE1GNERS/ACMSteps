// [Auto Archived]
// Submit: 2016-10-28 23:14:19
// Time: 577MS
// Memory: 1952K

#include <bits/stdc++.h>
using namespace std;

int T;
int n,s[100010];
int s1,s2,t1,t2;
int modn = 1e9+7;
vector<int> ans;

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    scanf("%d",&T);
    while (T--) {
        scanf("%d",&n);
        for (int i = 0; i < n; ++i)
            scanf("%d",&s[i]);
        ans.clear();
        for (int i = 1; i < n; ++i)
            if (n % i == 0) {
                s1 = 0;
                s2 = 1;
                for (int j = 0; j < i; ++j) {
                    s1 = (s1 + s[j]) % modn;
                    s2 = ((long long)s2 * s[j]) % modn;
                }
                int ok = 1;
                for (int j = 1; j < n/i; ++j) {
                    t1 = 0;
                    t2 = 1;
                    for (int k = 0; k < i; ++k) {
                        t1 = (t1 + s[j*i+k]) % modn;
                        t2 = ((long long)t2 * s[j*i+k]) % modn;
                    }
                    if (s1 != t1 || s2 != t2)
                        ok = 0;
                }
                if (ok) ans.push_back(i);
            }
        ans.push_back(n);
        for (int i = 0; i < ans.size(); ++i)
            printf("%d%c",ans[i],i==ans.size()-1?'\n':' ');
    }
    return 0;
}
