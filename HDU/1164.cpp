// [Auto Archived]
// Submit: 2016-10-21 22:48:25
// Time: 15MS
// Memory: 1568K

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> vv;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    while (~scanf("%d",&n)) {
        vv.clear();
        for (int i = 2; i * i <= n; ++i) {
            if (n % i == 0) {
                while (n % i == 0) {
                    vv.push_back(i);
                    n /= i;
                }
            }
        }
        if (n > 1) vv.push_back(n);
        for (int i = 0; i < vv.size(); ++i) {
            printf("%d%c",vv[i],i==vv.size()-1?'\n':'*');
        }
    }
    return 0;
}
