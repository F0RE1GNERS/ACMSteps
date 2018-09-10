// [Auto Archived]
// Submit: 2016-02-07 10:51:51
// Time: 0MS
// Memory: 1572K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> PINT;
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define REP(i,a,n) for (int i=(int)(a);i<(int)(n);++i)
#define PER(i,a,n) for (int i=(int)(n)-1;i>=(int)(a);--i)
#define SQR(i) (i)*(i)
const int nmax = 1200;

char t[nmax],p[nmax];
int f[nmax],ans,n,m;

int main()
{
    while (scanf("%s%s",t,p)!=EOF&&strcmp(t,"#")!=0)
    {
        n = strlen(t);
        m = strlen(p);
        f[0]=0,f[1]=0;
        REP(i,1,m) {
            int j = f[i];
            while (j&&p[i]!=p[j]) j=f[j];
            f[j+1] = p[i]==p[j]?j+1:0;
        }
        int j = 0;
        ans = 0;
        REP(i,0,n) {
            while (j&&p[j]!=t[i]) j=f[j];
            if (p[j]==t[i]) ++j;
            if (j==m) ++ans,j=0;
        }
        printf("%d\n",ans);
    }
    return 0;
}
