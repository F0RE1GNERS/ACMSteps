// [Auto Archived]
// Submit: 2018-08-20 13:29:12
// Time: 15MS
// Memory: 1380K

#include <bits/stdc++.h>

//#undef zerol
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

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T; scanf("%d", &T);
    while(T--) {
        LL a, b, c, d, e, f;
        scanf("%lld%lld%lld", &a, &b, &c);
        scanf("%lld%lld%lld", &d, &e, &f);
        LL x = a*e+b*f+c*d-a*f-b*d-c*e;
        LL y = a+b+c;
        LL g = abs(__gcd(x, y));
        x/=g; y/=g;
        if(y==1) {
            printf("%lld\n", x);
        } else {
            printf("%lld/%lld\n", x, y);
        }
    }
    return 0;
}
