// [Auto Archived]
// Submit: 2018-08-01 14:32:44
// Time: 31MS
// Memory: 1456K

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

#define y0 sdfkjsdklfsdl
#define y1 sdlsdfjsfkiof


const int N = 2e2;

int M[N][N];
LL S[N][N];
int A[N];

template<typename T>
inline void o(T p) {
    static int stk[70], tp;
    if (p == 0) { putchar('0'); return; }
    if (p < 0) { p = -p; putchar('-'); }
    while (p) stk[++tp] = p % 10, p /= 10;
    while (tp) putchar(stk[tp--] + '0');
}

LL sum(int x0, int y0, int x1, int y1) {
    //dbg(x0, y0, x1, y1);
    return S[x1][y1]-S[x0-1][y1]-S[x1][y0-1]+S[x0-1][y0-1];
}

int main() {
#ifdef zerol
    //freopen("in", "r", stdin);
#endif
    int T, Q; scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d", &n); m = 2*n;
        for(int i = 0; i<n; ++i) scanf("%d", A+i);
        int cursor = 0;
        for (int i = 0; i<m*2; ++i) {
               for (int j = 0; j <= i; ++j) { 
                M[j][i - j] = A[cursor++];
                cursor %= n;
            }
        }
        for(int i = 0; i<m; ++i)
            for(int j = 0; j<m; ++j) {
                S[i][j] = M[i][j]+S[i-1][j]+S[i][j-1]-S[i-1][j-1];
            }
        scanf("%d", &Q);
        while(Q--) {
            int x0, y0, x1, y1;
            scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
            __int128 ans = 0, tmp;
            LL xx0 = x0/m, xx1 = x1/m; //dbg(xx0, xx1);
            LL yy0 = y0/m, yy1 = y1/m; //dbg(yy0, yy1);
            tmp = S[m-1][m-1];
            if(xx1==xx0) {
                if(yy1==yy0) {
                    fuck(0);
                    ans = sum(x0%m, y0%m, x1%m, y1%m);
                } else {
                    fuck(1);
                    ans += sum(x0%m, y0%m, x1%m, m-1);
                    ans += (yy1-yy0-1)*sum(x0%m, 0, x1%m, m-1);
                    ans += sum(x0%m, 0, x1%m, y1%m);
                }
            } else if(yy1==yy0) {
                fuck(2);
                ans += sum(x0%m, y0%m, m-1, y1%m);
                ans += (xx1-xx0-1)*sum(0, y0%m, m-1, y1%m);
                ans += sum(0, y0%m, x1%m, y1%m);
            } else {
                fuck(3);
                ans = tmp*(xx1-xx0-1)*(yy1-yy0-1);
                ans += sum(x0%m, y0%m, m-1, m-1);
                ans += sum(0, y0%m, x1%m, m-1);
                ans += sum(x0%m, 0, m-1, y1%m);
                ans += sum(0, 0, x1%m, y1%m);
                ans += (xx1-xx0-1)*sum(0, 0, m-1, y1%m);
                ans += (xx1-xx0-1)*sum(0, y0%m, m-1, m-1);
                ans += (yy1-yy0-1)*sum(0, 0, x1%m, m-1);
                ans += (yy1-yy0-1)*sum(x0%m, 0, m-1, m-1);
            }
            o(ans); puts("");
        }
    }
}