// [Auto Archived]
// Submit: 2018-08-15 15:10:20
// Time: 218MS
// Memory: 1432K

#include <bits/stdc++.h>
 
#undef zerol

using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cerr << "Debug: " << #args << " -> "; err(args); } while (0)
#define fuck(x) do { printf("fuck@%d\n", x); } while(0)
#else
#define dbg(...)
#define fuck(...)
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

typedef double ld;

const ld INF = 1e100;
const ld EPS = 1e-12;
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

ld dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
ld dist2(PT p, PT q) { return dot(p - q, p - q); }
ld cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }
ostream &operator << (ostream &os, const PT &p) {
    return (os << "(" << p.x << "," << p.y << ")");
}
istream &operator >> (istream &is, PT &p) {
    return (is >> p.x >> p.y);
}
PT RotateCCW(PT p, ld t) {
    return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

PT A, B, C;

void read(PT& p) {
    scanf("%lf%lf", &p.x, &p.y);
}

double sqr(double t) {
    return t*t;
}

double S(PT a, PT b, PT c) {
    ld norm = sqrt(dot(b-a, b-a));
    ld s = fabs(dot(b-a, b-a))+fabs(dot(c-a, b-a))+fabs(dot(c-b, b-a));
    return s/norm/2;
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T; scanf("%d", &T);
    while(T--) {
        double inf = 1E18;
        double ans = inf; int w;
        read(A); read(B); read(C); scanf("%d", &w);
        double a2 = cross(B-A, C-A);
        dbg(a2);
        if(a2<0) swap(B, C);
        a2 = fabs(a2);
        double a = sqrt(dist2(B, C));
        double b = sqrt(dist2(A, C));
        double c = sqrt(dist2(A, B));
        if(S(A, B, C)<w+EPS) {
            ans = min(ans, a2/c);
        }
        if(S(B, C, A)<w+EPS) {
            ans = min(ans, a2/a);
        }
        if(S(C, A, B)<w+EPS) {
            ans = min(ans, a2/b);
        }
        dbg(ans);
        int ttt = 0;
        while(++ttt<=3) {
            if(c>w-EPS) {
                int qqq = 0;
                ld cosalpha = (b*b+c*c-a*a)/(2*b*c);
                ld cosbeta = (a*a+c*c-b*b)/(2*a*c);
                ld cosphi = sqrt(1-sqr(w/c));
                dbg(cosalpha, cosbeta, cosphi);
                {                
                    dbg(A, B, C);
                    dbg(a, b, c);
                    if(cosphi<cosbeta+EPS && -cosphi<cosalpha+EPS) {
                        ld norm = sqrt(dot(A-B, A-B));
                        PT one = RotateCCW(A-B, -acos(cosphi))/norm;
                        ld s = (fabs(dot(A-B, one)) + fabs(dot(A-C, one)) + fabs(dot(B-C, one)))/2;
                        if(s<ans) ans = s;
                        dbg(norm, one, s);
                    }
                }
                {                
                    dbg(A, B, C);
                    dbg(a, b, c);
                    if(-cosphi<cosbeta+EPS && cosphi<cosalpha+EPS) {
                        ld norm = sqrt(dot(B-A, B-A));
                        PT one = RotateCCW(A-B, PI+acos(cosphi))/norm;
                        ld s = (fabs(dot(A-B, one)) + fabs(dot(A-C, one)) + fabs(dot(B-C, one)))/2;
                        if(s<ans) ans = s;
                        dbg(norm, one, s);
                    }
                }
            }
            dbg(ans);
            swap(A, B); swap(A, C);
            swap(a, b); swap(a, c);
        }
        if(ans==inf) {
            puts("impossible");
        }else {
            printf("%.12f\n", ans);
        }
    }
    return 0;
}