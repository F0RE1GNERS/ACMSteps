// [Auto Archived]
// Submit: 2016-11-05 09:31:16
// Time: 0MS
// Memory: 1412K

#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

unsigned long long f[100];
unsigned long long power[100];

int main() {
    #ifdef ULTMASTER
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    power[0] = 0;
    for (int i = 1; i <= 64; ++i) {
        power[i] = (~0LLU);
        power[i] >>= (64 - i);
    }
    f[0] = 0;
    for (int i = 1; i <= 64; ++i) {
        f[i] = 2 * f[i - 1] + power[1];
        for (int j = 2; j <= i; ++j)
            f[i] = min(f[i], 2 * f[i - j] + power[j]);
    }
    int n;
    while (~scanf("%d", &n))
        printf("%llu\n", f[n]);
    return 0;
}
