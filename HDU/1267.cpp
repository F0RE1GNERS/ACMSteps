// [Auto Archived]
// Submit: 2016-10-25 21:50:39
// Time: 0MS
// Memory: 1408K

#include<stdio.h>
int main()
{
    __int64 a[21][21]={0};
    int m,n,i,j;
    for(i=1;i<21;i++)
    {
        a[i][0]=1;
    }
    for(i=1;i<21;i++)
    {
        for(j=1;j<=i;j++)
        {
            a[i][j]=a[i-1][j]+a[i][j-1];
        }
    }
    while(scanf("%d%d",&m,&n)!=EOF)
    {
        printf("%I64d\n",a[m][n]);
    }
    return 0;
}