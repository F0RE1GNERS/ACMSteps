// [Auto Archived]
// Submit: 2017-08-18 21:25:55
// Time: 171MS
// Memory: 5368K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int A[50], Asize;
set<int> M;

void dfs(int start, int loc) {
    LL t;
    // printf("%d %d\n", start, loc);
    for (int i = start; i < Asize; ++i) {
        t = 1LL * loc * A[i];
        if (t <= 1e9) {
            M.insert((int) t);
            dfs(i, (int) t);
        } else break;
    }
}

int main() {
    A[0] = 0; A[1] = 1;
    for (int i = 2; ; ++i) {
        A[i] = A[i - 1] + A[i - 2];
        if (A[i] > 1e9) {
            Asize = i;
            break;
        }
    }
    dfs(3, 1);
    // printf("%d\n", (int) M.size());
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        if (n <= 1) puts("Yes");
        else if (M.count(n)) puts("Yes");
        else puts("No");
    }
}