// [Auto Archived]
// Submit: 2018-07-30 14:27:39
// Time: 1201MS
// Memory: 26196K

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
void err() { cout << "\033[39;0m" << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

LL dcmp(LL x) { return x; }

struct PT {
    LL x, y, id;
    PT() { x = 0; y = 0; id = 0; }
    PT(LL x, LL y): x(x), y(y), id(0) {}
    PT(LL x, LL y, int id): x(x), y(y), id(id) {}
    PT(const PT &p) : x(p.x), y(p.y), id(p.id) {}
    PT operator + (const PT &p) const { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p) const { return PT(x - p.x, y - p.y); }
    PT operator * (LL c) const { return PT(x * c, y * c); }
    PT operator / (LL c) const { return PT(x / c, y / c); }
    inline LL operator < (const PT& p) const {
        return dcmp(x - p.x) < 0 || (dcmp(x - p.x) == 0 && dcmp(y - p.y) < 0);
    }
    inline bool operator == (const PT& p) const { return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0; }
    inline bool operator != (const PT& p) const { return !((*this) == p); }
};
LL dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
LL dist2(PT p, PT q) { return dot(p - q, p - q); }
LL cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }
ostream &operator << (ostream &os, const PT &p) {
    return (os << "(" << p.x << "," << p.y << ")");
}
istream &operator >> (istream &is, PT &p) {
    return (is >> p.x >> p.y);
}
LL area2(PT a, PT b, PT c) { return cross(a,b) + cross(b,c) + cross(c,a); }
typedef vector<PT> VPT;

const int N = 3E5 + 100;
int n;
PT pts[N];

VPT convex_hull() {
    VPT up;
    sort(pts, pts + n);
    FOR (i, 0, n) {
        while (up.size() > 1) {
            LL t = area2(up[up.size() - 2], up.back(), pts[i]);
            if (t > 0) up.pop_back();
            else if (t == 0 && up.back().id > pts[i].id) up.pop_back();
            else break;
        }
        up.push_back(pts[i]);
    }
    return up;
}

map<pair<int, int>, int> MAP;

int main() {
    // get_phi();
    int T; cin >> T;
    while (T--) {
        cin >> n;
        MAP.clear();
        FOR (i, 0, n) {
            pair<int, int> tmp;
            scanf("%d%d", &tmp.first, &tmp.second);
            if (MAP.find(tmp) == MAP.end()) MAP[tmp] = i;
            else MAP[tmp] = min(MAP[tmp], i);
        }
        n = 0;
        for (auto x: MAP) {
            pts[n++] = PT(x.first.first, x.first.second, x.second);
        }
        auto res = convex_hull();
        FOR (i, 0, res.size())
            printf("%d%c", res[i].id + 1, i == _i - 1 ? '\n' : ' ');
    }
    return 0;
}