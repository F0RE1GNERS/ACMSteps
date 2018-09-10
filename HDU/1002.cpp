// [Auto Archived]
// Submit: 2016-10-13 22:15:24
// Time: 0MS
// Memory: 1592K

#include <bits/stdc++.h>
using namespace std;

char s1[1200],s2[1200],s3[1200];
int a[1200],b[1200],c[1200];
int len1,len2,len3;
int kases;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    #endif
    scanf("%d",&kases);
    for (int kase = 1; kase <= kases; ++kase) {
        memset(s1,0,sizeof(s1));
        memset(s3,0,sizeof(s3));
        memset(s2,0,sizeof(s2));
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(c,0,sizeof(c));
        scanf("%s%s",s1,s2);
        len1 = strlen(s1);
        len2 = strlen(s2);
        for (int i = 0; i < len1; ++i)
            a[i] = s1[len1-i-1]-'0';
        for (int i = 0; i < len2; ++i)
            b[i] = s2[len2-i-1]-'0';
        len3 = max(len1,len2)+1;
        for (int i = 0; i < len3; ++i) {
            if (i < len1 && i < len2) c[i] = a[i]+b[i];
            else if (i < len1) c[i] = a[i];
            else if (i < len2) c[i] = b[i];
        }
        for (int i = 0; i < len3; ++i) {
            c[i+1] += c[i]/10;
            c[i] %= 10;
        }
        while (c[len3-1] == 0) --len3;
        for (int i = 0; i < len3; ++i)
            s3[i] = c[len3-i-1]+'0';
        printf("Case %d:\n%s + %s = %s\n",kase,s1,s2,s3);
        if (kase < kases) printf("\n");
    }
    return 0;
}
