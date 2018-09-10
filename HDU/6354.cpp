// [Auto Archived]
// Submit: 2018-08-06 12:49:20
// Time: 31MS
// Memory: 1516K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
#ifdef ONLINE_JUDGE
#define assert(condition) if (!(condition)) { int x = 1, y = 0; cout << x / y << endl; }
#endif
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
typedef double ld;
const ld INF = 1e100;
const ld EPS = 1e-10;
const ld PI = acos(-1.0);

// -1: less than 0
// 1: greater than 0
inline int dcmp(ld x) {
    return fabs(x) < EPS ? 0 : (x > 0 ? 1 : -1);
}

struct PT {
    ld x, y;
    PT() { x = 0; y = 0; }
    PT(ld x, ld y): x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y) {}
    PT operator + (const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator * (ld c) const { return PT(x * c, y * c); }
    PT operator / (ld c) const { return PT(x / c, y / c); }
    inline int operator < (const PT& p) const {
        return dcmp(x - p.x) < 0 || (dcmp(x - p.x) == 0 && dcmp(y - p.y) < 0);
    }
    inline bool operator == (const PT& p) const { return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0; }
    inline bool operator != (const PT& p) const { return !((*this) == p); }
};

PT RotateCCW90(PT p) { return PT(-p.y, p.x); }
PT RotateCW90(PT p) { return PT(p.y, -p.x); }
PT RotateCCW(PT p, ld t) {
    return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}
ld dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
ld dist2(PT p, PT q) { return dot(p - q, p - q); }
ld cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }
ld angle(PT p, PT q) { return acos(dot(p, q) / sqrt(dot(p, p) * dot(q, q))); }
ostream &operator << (ostream &os, const PT &p) {
    return (os << "(" << p.x << "," << p.y << ")");
}
istream &operator >> (istream &is, PT &p) {
    return (is >> p.x >> p.y);
}

ld DistanceBetweenPoints(PT a, PT b) { return sqrt(dist2(a, b)); }
vector<PT> CircleCircleIntersection(PT a, PT b, ld r, ld R) {
    vector<PT> ret;
    ld d = sqrt(dist2(a, b));
    if (dcmp(d) == 0 || dcmp(d - (r + R)) > 0 || dcmp(d + min(r, R) - max(r, R)) < 0) return ret;
    ld x = (d * d - R * R + r * r) / (2 * d);
    ld y = sqrt(r * r - x * x);
    PT v = (b - a) / d;
    ret.push_back(a + v * x + RotateCCW90(v) * y);
    ret.push_back(a + v * x - RotateCCW90(v) * y);
    return ret;
}

ld ComputeIntersectionLength(PT a, PT b, ld r, const vector<PT> &v) {
    assert (a != b);
    PT dir = PT(b - a);
    dir = dir / sqrt(dot(dir, dir)) * r;
    // dbg(a, b, r, dir, v[0]-a, v[1]-a);
    ld res = angle(dir, v[0] - a) + angle(dir, v[1] - a);
    // dbg(res);
    res *= r; return res;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int m; ld R; scanf("%d%lf", &m, &R);
        PT Z(0, 0);
        vector<PT> c(m); vector<ld> d(m);
        FOR (i, 0, m) scanf("%lf%lf%lf", &c[i].x, &c[i].y, &d[i]);
        ld ans = 2 * PI * R;
        FOR (i, 0, m) {
            dbg(fabs(R-d[i]), DistanceBetweenPoints(c[i],Z));
            if (dcmp(fabs(R - d[i]) - DistanceBetweenPoints(c[i], Z)) > 0)
                continue;
            if (dcmp(fabs(R + d[i]) - DistanceBetweenPoints(c[i], Z)) <= 0)
                continue;
            // dbg(R, d[i]);
            vector<PT> v = CircleCircleIntersection(Z, c[i], R, d[i]);
            assert (v.size() == 2);
            ans -= ComputeIntersectionLength(Z, c[i], R, v);
            ans += ComputeIntersectionLength(c[i], Z, d[i], v);
        }
        printf("%.9f\n", ans);
    }
}