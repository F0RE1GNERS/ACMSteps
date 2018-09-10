// [Auto Archived]
// Submit: 2017-08-11 00:24:37
// Time: 1248MS
// Memory: 1704K

#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1.0);
const double eps = 1e-6;

double r, x1, Y1, x2, y2, a, ans, q;

double dot(double x1, double y1, double x2, double y2) {
    return x1 * x2 + y1 * y2;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int _r, _x1, _y1, _x2, _y2;
        scanf("%d%d%d%d%d", &_r, &_x1, &_y1, &_x2, &_y2);
        r = _r; x1 = _x1; Y1 = _y1; x2 = _x2; y2 = _y2;
        x1 /= r; Y1 /= r; x2 /= r; y2 /= r;
        a = sqrt(x1 * x1 + Y1 * Y1);
        if (a < eps) {
            ans = 2;
        } else {
            double ang = acos(dot(x1, Y1, x2, y2) / (x1 * x1 + Y1 * Y1)) / 2;
            // printf("%f %f %f %f %f\n", x1, Y1, x2, y2, ang);
            // assert (ang >= 0 && ang <= pi / 2);
            double p = sin(ang) * a;
            double r = cos(ang) * a;
            // printf("%f %f %f\n", ang, p, r);
            ans = sqrt(1 + p * p - 2 * r + r * r);
            double tt = pow(p * p + r * r, 2) - r * r;
            if (tt > -eps && tt < 1 + eps)
                ans = min(ans, p / sqrt(p * p + r * r));
            ans *= 2;
        }
        printf("%.9f\n", ans * r);
        
    }
}