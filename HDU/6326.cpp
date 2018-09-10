// [Auto Archived]
// Submit: 2018-07-31 08:49:56
// Time: 2043MS
// Memory: 25324K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "\033[32;1m" << #args<< " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << "\033[39m" << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------
inline LL sig(LL x) {
    return x >= 0 ? 1 : -1;
}

struct P {
    LL a, b;
    int id;
    bool operator < (const P &p) const {
        if (sig(b - a) != sig(p.b - p.a))
            return b - a > p.b - p.a;
        if (b >= a) return a < p.a || (a == p.a && id < p.id);
        else return b > p.b || (b == p.b && id < p.id);
    }
};

const int N = 1E5 + 100;
int n, fa[N], ta[N];
vector<int> g[N];
P y[N];

void dfs(int u, int f) {
    ta[u] = f;
    for (int x: g[u]) {
        if (x == f) continue;
        dfs(x, u);
    }
}

int find(int x) {
    return fa[x] == x ? x: fa[x] = find(fa[x]);
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR (i, 1, n + 1) g[i].clear();
        y[0].a = y[0].b = y[0].id = 0;
        y[1].a = y[1].b = 0; y[1].id = 1;
        FOR (i, 2, n + 1) {
            scanf("%lld%lld", &y[i].a, &y[i].b);
            y[i].id = i;
        }
        FOR (i, 1, n) {
            int u, v; scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, 0);
        iota(fa, fa + n + 1, 0);
        set<P> s(y + 1, y + n + 1);
        vector<P> res;
        // dbg(n);
        FOR (i, 0, n) {
            auto victim = *s.begin();
            dbg(victim.a, victim.b, victim.id);
            int father = find(ta[victim.id]);
            dbg(y[father].a, y[father].b, father);
            if (father == 0) {
                res.push_back(victim);
                fa[victim.id] = 0;
                s.erase(s.begin());
            } else {
                auto e = s.find(y[father]);
                assert (e->a == y[father].a);
                y[father].a = max(e->a, e->a - e->b + victim.a);
                y[father].b = victim.b - victim.a + e->b - e->a + y[father].a;
                dbg(y[father].a, y[father].b, father);
                s.erase(e); s.erase(s.begin());
                fa[victim.id] = father;
                s.insert(y[father]);
            }
            dbg(s.size());
        }
        LL t = 0, ans = 0;
        for (auto& x: res) {
            t -= x.a; ans = min(ans, t);
            t += x.b;
            dbg(x.a, x.b, x.id);
        }
        cout << -ans << endl;
    }
}
