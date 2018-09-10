// [Auto Archived]
// Submit: 2016-07-25 20:14:29
// Time: 0MS
// Memory: 1608K

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;
    Point(double _x = 0, double _y = 0)
        :x(_x),y(_y) { }
};

typedef Point Vector;

bool operator < (Point a, Point b) { return (a.x < b.x) || (a.x == b.x && a.y < b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x-b.x, a.y-b.y); }

double Dot(Vector a, Vector b) { return a.x*b.x+a.y*b.y; }
double Cross(Vector a, Vector b) { return a.x*b.y-a.y*b.x; }
double length(Point a, Point b) { return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)); }

double MinRadius(Point a, Point b, Point c)
{
    if (Dot(b-a,c-a) < 0 || Dot(a-b,c-b) < 0 || Dot(a-c,b-c) < 0)
        return max(length(a,b),max(length(a,c),length(b,c))) / 2;
    else
        return length(a,b)*length(a,c)*length(b,c)/2/fabs(Cross(a-c,b-c));
}

int n,convex[120],csz,tmpcsz;
Point p[120];
double ans;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    #endif
    while (~scanf("%d",&n) && n)
    {
        for (int i = 0; i < n; ++i)
            scanf("%lf%lf",&p[i].x,&p[i].y);

        if (n == 1)
            ans = 0;
        else if (n == 2)
            ans = length(p[0],p[1])/2;
        else {
            // GET CONVEX
            csz = 0;
            sort(p,p+n);
            for (int i = 0; i < n; ++i)
            {
                while (csz > 1 &&
                    Cross(p[i]-p[convex[csz-1]],p[convex[csz-1]]-p[convex[csz-2]]) <= 0)
                    --csz;
                convex[csz++] = i;
            }
            tmpcsz = csz;
            for (int i = n-2; i >= 0; --i)
            {
                while (csz > tmpcsz &&
                    Cross(p[i]-p[convex[csz-1]],p[convex[csz-1]]-p[convex[csz-2]]) <= 0)
                    --csz;
                convex[csz++] = i;
            }
            --csz;

            // GET DIAMETER
            ans = 0;
            for (int i = 0; i < csz; ++i)
                for (int j = i+1; j < csz; ++j)
                    for (int k = j+1; k < csz; ++k)
                        ans = max(ans,MinRadius(p[convex[i]],p[convex[j]],p[convex[k]]));
        }
        ans += 0.5;
        printf("%.2lf\n",ans);
    }
    return 0;
}
