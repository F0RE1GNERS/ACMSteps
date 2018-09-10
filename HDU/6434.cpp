// [Auto Archived]
// Submit: 2018-08-22 12:51:10
// Time: 920MS
// Memory: 260768K

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
#define fuck(...)9
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

const int N = 2E7+10;
const int MOD = 998244353;

int pr[N], pc;
bool np[N];
int phi[N];
LL sp[N];

void getphi() {
    phi[1] = 0;
    for(int i = 2; i<N; ++i) {
        if(!np[i]) {
            pr[pc++] = i; phi[i] = i-1;
        }
        for(int j = 0; j<pc; ++j) {
            int k = i*pr[j];
            if(k>=N) break;
            np[k] = true;
            if(i%pr[j]==0) {
                phi[k] = phi[i] * pr[j];
                break;
            } else {
                phi[k] = phi[i] * (pr[j]-1);
            }
        }
    }
    for(int i = 2; i<N; ++i) {
        sp[i] = sp[i-2]+phi[i];
    }
}

int main() {
#ifdef zerol
    freopen("in", "r", stdin);
    //freopen("out2", "w", stdout);
#endif
    getphi();
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n); LL ans;
        if((n&1)) {
            ans=sp[n]/2+sp[n-1];
        } else {
            ans=sp[n]+sp[n-1]/2;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
