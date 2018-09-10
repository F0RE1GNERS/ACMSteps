// [Auto Archived]
// Submit: 2018-08-25 12:49:57
// Time: 218MS
// Memory: 2296K

#include <bits/stdc++.h>

//#define zerol
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

typedef pair<int, int> P;

priority_queue<P, vector<P>, greater<P>> pq; 

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m = 0; scanf("%d", &n);
        LL ans = 0;
        while(n--) {
            int x; scanf("%d", &x); dbg(x);
            if(!pq.empty()) {
                P p = pq.top();
                dbg(p.first, p.second);
                if(p.first<x) {
                    pq.pop();
                    ans+=x-p.first;
                    if(p.second) {
                        ++m;
                    } else {
                        pq.push(P(p.first, 1));
                    }
                    pq.push(P(x, 0));
                } else {
                    pq.push(P(x, 1));
                }
            } else {
                pq.push(P(x, 1));
            }
        }
        printf("%lld %d\n", ans, m*2);
        while(!pq.empty()) pq.pop();
    } 
    return 0;
}