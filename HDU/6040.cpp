// [Auto Archived]
// Submit: 2017-07-26 17:04:35
// Time: 1575MS
// Memory: 40828K

#include <bits/stdc++.h>
using namespace std;

unsigned x, y, z;
unsigned rng61() {
    unsigned t;
    x ^= x << 16;
    x ^= x >> 5;
    x ^= x << 1;
    t = x;
    x = y;
    y = z;
    z = t ^ x ^ y;
    return z;
}

struct Query {
    int b, id;
    unsigned ans;
};

bool cmp1(Query x, Query y) {
    return x.b < y.b;
}
bool cmp2(Query x, Query y) {
    return x.id < y.id;
}

int n, m;
unsigned a[12000000];
Query q[200];

int main() {
    int cas = 0;
    while (~scanf("%d%d%u%u%u", &n, &m, &x, &y, &z)) {
        for (int i = 0; i < m; ++i) {
            scanf("%d", &q[i].b);
            q[i].id = i;
        }
        for (int i = 0; i < n; ++i)
            a[i] = rng61();
        sort(q, q + m, cmp1);
        int length = n;
        for (int i = m - 1; i >= 0; --i) {
            if (i < m - 1 && q[i].b == q[i + 1].b)
                q[i].ans = q[i + 1].ans;
            else {
                nth_element(a, a + q[i].b, a + length);
                q[i].ans = a[q[i].b];
                length = q[i].b + 1;
            }
        }
        sort(q, q + m, cmp2);
        printf("Case #%d: ", ++cas);
        for (int i = 0; i < m; ++i)
            printf("%u%c", q[i].ans, " \n"[i == m - 1]);
    }
    return 0;
}
