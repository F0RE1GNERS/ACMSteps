// [Auto Archived]
// Submit: 2018-07-23 12:41:13
// Time: 670MS
// Memory: 9212K

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cout << "Debug: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif // zerol
void err() { cout << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// ----------------------------------------------------------------

const int N = 1e6 + 10;
// vector<int> nums[N];
int n;
LL ap[N];

void init() {
    // for (int i = 1; i < N; ++i)
    //     for (int j = i + i; j < N; j += i)
    //         nums[j].push_back(i);
}

int v[N], vp;

int main() {
    int T, cas = 0;
    scanf("%d", &T);
    init();
    memset(ap, 0, sizeof ap);
    while (T--) {
        int n; scanf("%d", &n);
        LL ans2 = -1;
        if (n % 3 == 0)
            ans2 = 1LL * (n / 3) * (n / 3) * (n / 3);
        else if (n % 4 == 0)
            ans2 = 1LL * (n / 2) * (n / 4) * (n / 4);
        printf("%lld\n", ans2);
    }
}
