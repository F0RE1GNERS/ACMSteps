// [Auto Archived]
// Submit: 2018-08-08 12:23:25
// Time: 0MS
// Memory: 1452K

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

const double G = 9.8;

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    int T; cin >> T;
    while(T--) {
        double a, b, x, y;
        cin >> a >> b >> x >> y;
        int ans = 0;
        double lambda = sqrt(a*a+b*b); 
        double L = -x*lambda/a;
        double V = sqrt(2*G*(y+x*b/a));
        double Vx = V*b/lambda;
        double Vy = V*a/lambda;
        double g = G*a/lambda;
        double aa = G*b/lambda;
        while(L>0) {
            ++ans;
            double t = Vy/g*2;
            L-=Vx*t+aa*t*t/2; 
            Vx+=aa*t;
            dbg(t, L, Vx, Vy);
        }
        cout << ans << endl;
    }
    return 0;
}