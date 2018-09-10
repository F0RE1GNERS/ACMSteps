// [Auto Archived]
// Submit: 2016-10-23 18:20:10
// Time: 46MS
// Memory: 1640K

#include <bits/stdc++.h>
using namespace std;
#define eps 1e-8
using namespace std;
#define N 100017

struct Point{
    double x,y;
    Point(double x=0, double y=0):x(x),y(y) {}
    void input() { scanf("%lf%lf",&x,&y); }
};
typedef Point Vector;
struct Circle{
    Point c;
    double r;
    Circle(){}
    Circle(Point c,double r):c(c),r(r) {}
    Point point(double a) { return Point(c.x + cos(a)*r, c.y + sin(a)*r); }
    void input() { scanf("%lf%lf%lf",&c.x,&c.y,&r); }
};
int dcmp(double x) {
    if(x < -eps) return -1;
    if(x > eps) return 1;
    return 0;
}
template <class T> T sqr(T x) { return x * x;}
Vector operator + (Vector A, Vector B) { return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x - B.x, A.y - B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }
bool operator < (const Point& a, const Point& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
bool operator >= (const Point& a, const Point& b) { return a.x >= b.x && a.y >= b.y; }
bool operator <= (const Point& a, const Point& b) { return a.x <= b.x && a.y <= b.y; }
bool operator == (const Point& a, const Point& b) { return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0; }
double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
Vector VectorUnit(Vector x){ return x / Length(x);}
Vector Normal(Vector x) { return Point(-x.y, x.x) / Length(x);}
double angle(Vector v) { return atan2(v.y, v.x); }

bool OnSegment(Point P, Point A, Point B) {
    return dcmp(Cross(A-P,B-P)) == 0 && dcmp(Dot(A-P,B-P)) < 0;
}
double DistanceToSeg(Point P, Point A, Point B)
{
    if(A == B) return Length(P-A);
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
    return fabs(Cross(v1, v2)) / Length(v1);
}
double DistanceToLine(Point P, Point A, Point B){
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1,v2)) / Length(v1);
}
Point DisP(Point A, Point B){
    return Length(B-A);
}
bool SegmentIntersection(Point A,Point B,Point C,Point D) {
    return max(A.x,B.x) >= min(C.x,D.x) &&
           max(C.x,D.x) >= min(A.x,B.x) &&
           max(A.y,B.y) >= min(C.y,D.y) &&
           max(C.y,D.y) >= min(A.y,B.y) &&
           dcmp(Cross(C-A,B-A)*Cross(D-A,B-A)) <= 0 &&
           dcmp(Cross(A-C,D-C)*Cross(B-C,D-C)) <= 0;
}

Point Zero = Point(0,0);
double TriAngleCircleInsection(Circle C, Point A, Point B)
{
    Vector OA = A-C.c, OB = B-C.c;
    Vector BA = A-B, BC = C.c-B;
    Vector AB = B-A, AC = C.c-A;
    double DOA = Length(OA), DOB = Length(OB),DAB = Length(AB), r = C.r;
    if(dcmp(Cross(OA,OB)) == 0) return 0;
    if(dcmp(DOA-C.r) < 0 && dcmp(DOB-C.r) < 0) return Cross(OA,OB)*0.5;
    else if(DOB < r && DOA >= r) {
        double x = (Dot(BA,BC) + sqrt(r*r*DAB*DAB-Cross(BA,BC)*Cross(BA,BC)))/DAB;
        double TS = Cross(OA,OB)*0.5;
        return asin(TS*(1-x/DAB)*2/r/DOA)*r*r*0.5+TS*x/DAB;
    }
    else if(DOB >= r && DOA < r) {
        double y = (Dot(AB,AC)+sqrt(r*r*DAB*DAB-Cross(AB,AC)*Cross(AB,AC)))/DAB;
        double TS = Cross(OA,OB)*0.5;
        return asin(TS*(1-y/DAB)*2/r/DOB)*r*r*0.5+TS*y/DAB;
    }
    else if(fabs(Cross(OA,OB)) >= r*DAB || Dot(AB,AC) <= 0 || Dot(BA,BC) <= 0) {
        if(Dot(OA,OB) < 0) {
            if(Cross(OA,OB) < 0) return (-acos(-1.0)-asin(Cross(OA,OB)/DOA/DOB))*r*r*0.5;
            else                 return ( acos(-1.0)-asin(Cross(OA,OB)/DOA/DOB))*r*r*0.5;
        }
        else                     return asin(Cross(OA,OB)/DOA/DOB)*r*r*0.5;
    }
    else {
        double x = (Dot(BA,BC)+sqrt(r*r*DAB*DAB-Cross(BA,BC)*Cross(BA,BC)))/DAB;
        double y = (Dot(AB,AC)+sqrt(r*r*DAB*DAB-Cross(AB,AC)*Cross(AB,AC)))/DAB;
        double TS = Cross(OA,OB)*0.5;
        return (asin(TS*(1-x/DAB)*2/r/DOA)+asin(TS*(1-y/DAB)*2/r/DOB))*r*r*0.5 + TS*((x+y)/DAB-1);
    }
}

int n,kase;
double k;
Point a,b;
Point P[1000];

double CommonArea(Circle C) {
    double res = 0;
    for (int i = 0; i < n; i++)
        res += TriAngleCircleInsection(C, P[i], P[i + 1]);
    return fabs(res);
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
    //freopen("a.out","w",stdout);
    #endif
    while (~scanf("%d%lf",&n,&k)) {
        for (int i = 0; i < n; ++i)
            scanf("%lf%lf",&P[i].x,&P[i].y);
        P[n] = P[0];
        scanf("%lf%lf%lf%lf",&a.x,&a.y,&b.x,&b.y);
        double D = 2*k*k*a.x-2*b.x;
        double E = 2*k*k*a.y-2*b.y;
        double F = - (k*k*a.x*a.x - b.x*b.x + k*k*a.y*a.y - b.y*b.y);
        double AA = 1-k*k;
        D /= AA;
        E /= AA;
        F /= AA;
        double R = 0.5 * sqrt(D*D + E*E - 4*F);
        Point p;
        p.x = -0.5 * D;
        p.y = -0.5 * E;
        // p.x = (b.x + k*a.x) / (1 - k*k);
        // p.y = (b.y + k*a.y) / (1 - k*k);
        // cout << p.x << endl;
        // cout << p.y << endl;
        // cout << R << endl;

        // double R = sqrt((2*k*k*a.x*a.x + 2*k*b.x*a.x + 2*k*k*a.y*a.y +
        //     2*k*b.y*a.y + k*k*b.x*b.x + k*k*b.y*b.y -
        //     pow(k,4)*a.x*a.x - pow(k,4)*a.y*a.y)) / (1-k*k);
        // Point p;
        // p.x = -2;
        // p.y = 0;
        // double R = 1;
        printf("Case %d: %.10lf\n",++kase,CommonArea(Circle(p,R)));
    }
    return 0;
}
