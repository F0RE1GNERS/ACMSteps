// [Auto Archived]
// Submit: 2016-09-18 21:39:39
// Time: 0MS
// Memory: 1608K

#include <bits/stdc++.h>
using namespace std;

struct BigInteger {
    int _d[1200];
    int len;
    int sign;
    void print()
    {
        if (len == 0)
            printf("0\n");
        else {
            if (sign) printf("-");
            printf("%d",_d[len-1]);
            for (int i = len-2; i >= 0; --i)
                printf("%03d",_d[i]);
            printf("\n");
        }
    }
    BigInteger(int from = 0)
    {
        len = 0;
        sign = 0;
        memset(_d,0,sizeof(_d));
        while (from)
        {
            _d[len++] = from % 1000;
            from /= 1000;
        }
    }
    BigInteger(char * s)
    {
        int slen = strlen(s);
        len = 0;
        sign = 0;
        memset(_d,0,sizeof(_d));
        for (int i = slen-1; i >= 0; i -= 3)
        {
            _d[len] = s[i]-'0';
            if (i-1 >= 0) _d[len] += (s[i-1]-'0')*10;
            if (i-2 >= 0) _d[len] += (s[i-2]-'0')*100;
            ++len;
        }
    }
};

int compare(BigInteger lhs, BigInteger rhs)
{
    if (lhs.len < rhs.len)
        return -1;
    if (lhs.len > rhs.len)
        return 1;
    if (lhs.len == rhs.len)
        for (int i = lhs.len-1; i >= 0; --i)
        {
            if (lhs._d[i] > rhs._d[i])
                return 1;
            else if (lhs._d[i] < rhs._d[i])
                return -1;
        }
    return 0;
}

BigInteger Plus(BigInteger lhs, BigInteger rhs)
{
    BigInteger ret;
    ret.len = max(lhs.len,rhs.len)+2;
    for (int i = 0; i < ret.len; ++i)
        ret._d[i] = lhs._d[i] + rhs._d[i];
    for (int i = 0; i < ret.len; ++i)
    {
        ret._d[i+1] += (ret._d[i]/1000);
        ret._d[i] %= 1000;
    }
    while (ret.len > 0 && ret._d[ret.len-1] == 0)
        --ret.len;
    return ret;
}

BigInteger Minus(BigInteger lhs, BigInteger rhs)
{
    BigInteger ret;
    if (compare(lhs,rhs) < 0)
    {   
        ret = Minus(rhs,lhs);
        ret.sign = 1;
        return ret;
    }
    ret.len = max(lhs.len,rhs.len);
    for (int i = 0; i < ret.len; ++i)
        ret._d[i] = lhs._d[i] - rhs._d[i];
    for (int i = 0; i < ret.len; ++i)
        while (ret._d[i] < 0)
        {
            ret._d[i] += 1000;
            ret._d[i+1]--;
        }
    while (ret.len > 0 && ret._d[ret.len-1] == 0)
        --ret.len;
    return ret;
}

BigInteger Multiply(BigInteger lhs, BigInteger rhs)
{
    BigInteger ret;
    ret.len = lhs.len+rhs.len+5;
    for (int i = 0; i < lhs.len; ++i)
        for (int j = 0; j < rhs.len; ++j)
            ret._d[i+j] += lhs._d[i]*rhs._d[j];
    for (int i = 0; i < ret.len; ++i)
    {
        ret._d[i+1] += (ret._d[i]/1000);
        ret._d[i] %= 1000;
    }
    while (ret.len > 0 && ret._d[ret.len-1] == 0)
        --ret.len;
    return ret;
}

BigInteger Divide(BigInteger lhs, int divider)
{
    BigInteger ret;
    int rem = 0;
    for (int i = lhs.len-1; i >= 0; --i)
    {
        rem = rem*1000+lhs._d[i];
        ret._d[i] = rem/divider;
        rem -= (ret._d[i]*divider);
    }
    ret.len = lhs.len;
    while (ret.len > 0 && ret._d[ret.len-1] == 0)
        --ret.len;
    return ret;
}

BigInteger Pow(BigInteger base, int expr)
{
    if (expr == 0) return BigInteger(1);
    if (expr == 1) return base;
    BigInteger ret = Pow(base,expr/2);
    ret = Multiply(ret,ret);
    if (expr&1) ret = Multiply(ret,base);
    return ret;
}

BigInteger lhs,rhs,ret;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    #endif
    char s1[1200],s2[1200];
    int t;
    scanf("%d",&t);
    for (int testc = 1; testc <= t; ++testc)
    {
        scanf("%s%s",s1,s2);
        lhs = BigInteger(s1);
        rhs = BigInteger(s2);
        printf("Case %d:\n",testc);
        printf("%s + %s = ",s1,s2);
        Plus(lhs,rhs).print();
        if (testc < t) printf("\n");
    }
    return 0;
}
