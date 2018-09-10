// [Auto Archived]
// Submit: 2017-08-20 08:58:06
// Time: 1622MS
// Memory: 1684K

#include <bits/stdc++.h>
using namespace std;

typedef double ld;
const ld pi = 3.141592653589793238L;

struct Point {
    ld x, y;
    Point() : x(0), y(0) {}
    Point(ld _x, ld _y) : x(_x), y(_y) {}

    Point operator * (ld a) const { return Point(x * a, y * a); }
    Point operator / (ld a) const { return Point(x / a, y / a); }
};

struct Circle {
    Point p;
    ld r;
    Circle() :p(0, 0), r(0) {}
    Circle(ld _x, ld _y, ld _r) : p(_x, _y), r(_r) {}
};

ld len2(const Point &a) { return a.x*a.x + a.y*a.y; }

Circle Inverse(Circle a) {
    ld d = sqrt(len2(a.p)), r = (1 / (d - a.r) - 1 / (d + a.r)) / 2;
    a.p = a.p * (1 / (d - a.r) - r) / d, a.r = r;
    return a;
}

ld area(ld r) {
    return pi * r * r;
}

ld solve(ld R, ld R1, int n) {
    if (R1 > R)
        swap(R1, R);
    if (R1 == R) return 0;
    ld R2 = R - R1;
    ld ans = area(R2);
    Circle cx = Inverse(Circle(0, R + R1, R - R1)), cy;
    ld t = 0;
    for (int i = 2; i <= n; i += 1) {
        if (i % 2 == 0) {
            cy = Circle(cx.p.x + cx.r * i, cx.p.y, cx.r);
            t = area(Inverse(cy).r);
        }
        ans += t;
        if (t < 1e-13) break;
    }
    return ans;
}

void print(ld d) {
    printf("%.5f\n", d);
    // long long t = (long long) (d * 100000);
    // printf("%lld.%lld\n", t / 100000, t % 100000);
}

int T, R1, R2, N;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &R1, &R2, &N);
        print(solve(R1, R2, N));
    }
    // for (int R1 = 100; R1 >= 1; --R1)
    //     for (int R2 = 100; R2 >= 1; --R2) {
    //         // scanf("%d%d%d", &R1, &R2, &N);
    //         printf("%d %d %.5f\n", R1, R2, solve(R1, R2, 10000000));
    //     }
}