// [Auto Archived]
// Submit: 2016-10-04 22:10:23
// Time: 0MS
// Memory: 1412K

#include <stdio.h>
using namespace std;
int a[10],b[10],n;
void init()
{
    scanf("%d",&n);
    for (int i=0;i<n;i++) scanf("%d",&a[i]);
    for (int i=0;i<n;i++) scanf("%d",&b[i]);
}
int gcd(int p1,int p2)
{
    if (p2==0) return p1;
        else return gcd(p2,p1%p2);
}
void solve(int p)
{
    int s=b[n-1],x=a[n-1];
    for (int i=n-2;i>=0;i--)
    {
        s=a[i]*x+s;
        s=s^x;x=s^x;s=s^x;
        s=s*b[i];
    }
    int k=gcd(s,x);
    printf("Case #%d: %d %d\n",p+1,s/k,x/k);
}
int main()
{
    int num;
    scanf("%d",&num);
    for (int i=0;i<num;i++)
    {
        init();
        solve(i);
    }
}