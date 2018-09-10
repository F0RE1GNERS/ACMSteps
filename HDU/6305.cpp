// [Auto Archived]
// Submit: 2018-07-23 22:34:50
// Time: 795MS
// Memory: 92656K

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

#define fi first
#define se second
const int MOD = 1e9 + 7;
const int N = 1e6 + 10;
typedef pair<int, int> P;
stack<int> st;
P b[N];
int a[N], rs[N], ls[N];
LL inv[N], ans;

int build(P *a, int n) {
    FOR (i, 0, n) {
        int last = -1;
        while (!st.empty() && a[st.top()] > a[i]) {
            last = st.top();
            st.pop();
        }
        if (!st.empty())
            rs[st.top()] = i;
        ls[i] = last;
        st.push(i);
    }
    int rt = 0;
    while (!st.empty()) {
        rt = st.top(); st.pop();
    }
    return rt;
}

int dfs(int i) {
    int s = 1;
    if (ls[i] != -1) s += dfs(ls[i]);
    if (rs[i] != -1) s += dfs(rs[i]);
    ans = ans * inv[s] % MOD;
    return s;
}

void solve() {
    int n; scanf("%d", &n);
    fill(ls, ls + n, -1);
    fill(rs, rs + n, -1);
    FOR (i, 0, n) {
        scanf("%d", &a[i]);
        b[i] = {-a[i], i};
    }
    int root = build(b, n);
    dbg(root);
    FOR (i, 0, n) dbg(ls[i], rs[i]);
    ans = n * inv[2] % MOD;
    dfs(root);
    printf("%lld\n", ans);
}

void init(int p) {
    inv[1] = 1;
    FOR (i, 2, N)
        inv[i] = (p - p / i) * inv[p % i] % p;
}

int main() {
    int T;
    scanf("%d", &T);
    init(MOD);
    while (T--) {
        solve();
    }
    return 0;
}