#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i > _##i; --i)
#ifdef zerol
#define dbg(args...) do { cout << "Debug: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif
void err() { cout << endl; }
template<template<typename...> class T, typename t, typename... Args>
void err(T<t> a, Args... args) { for (auto x: a) cout << x << ' '; err(args...); }
template<typename T, typename... Args>
void err(T a, Args... args) { cout << a << ' '; err(args...); }
// -----------------------------------------------------------------------------

#define y1 klfjlsdjfklsdjk

const int N = 1e5+10;

typedef pair<int, int> P;

struct Line {
    int x, y, len, id;
};

bool cmp(const Line &p, const Line &q) {
    return p.x==q.x?p.y<q.y:p.x<q.x;
}

int x1[N], y1[N], x2[N], y2[N];

Line ver[N], hor[N];

set<P> H[2], V[2];

vector<int> Remove[N];

int fa[N], cc;
LL ss;

int Fa(int x) { return fa[x]==x?x:(fa[x] = Fa(fa[x])); }

void Union(int x, int y) {
    dbg("union", x, y);
    x = Fa(x); y = Fa(y);
    if(x!=y) {
        fa[y] = x; --cc;
    }
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int n, m, k; scanf("%d%d%d", &n, &m, &k); cc = 0; ss = 0;
        int nn = 0, mm = 0;
        H[0].clear(); H[1].clear();
        V[0].clear(); V[1].clear();
        FOR(i, 0, k) {
            scanf("%d%d%d%d", x1+i, y1+i, x2+i, y2+i);
            if(x1[i]==x2[i]) {
                hor[nn++] = (Line){x1[i], y1[i], y2[i]-y1[i]+1, i};
            } else {
                ver[mm++] = (Line){x1[i], y1[i], x2[i]-x1[i]+1, i};
            }
            fa[i] = i;
        }
        sort(hor, hor+nn, cmp);
        sort(ver, ver+mm, cmp);
        int now = 0, nxt = 1;
        int cur = 0;
        int p = 0, q = 0;
        for(int i = 1; i<=n; ++i) {
            //dbg(i);
            int pp = p, qq = q;
            while(p<nn && hor[p].x==i) {
                ++cc;
                ss+=hor[p].len;
                auto it = V[now].lower_bound({hor[p].y, -1}); int yy = hor[p].y+hor[p].len-1;
                while(it!=V[now].end() && it->first<=yy) {
                    Union(hor[p].id, it->second); ++it;
                }
                it = H[now].lower_bound({hor[p].y, -1}); if(it!=H[now].begin()) --it;
                while(it!=H[now].end() && y2[it->second]<hor[p].y) ++it;
                while(it!=H[now].end() && y1[it->second]<=yy) {
                    Union(hor[p].id, it->second); ++it;
                }
                H[nxt].insert(P(hor[p].y, hor[p].id));
                ++p;
            }
            while(q<mm && ver[q].x==i) {
                ++cc;
                auto it = V[now].lower_bound({ver[q].y, -1});
                if(it!=V[now].end() && it->first==ver[q].y) {
                    Union(ver[q].id, it->second);
                }
                it = H[now].lower_bound({ver[q].y+1, -1}); if(it!=H[now].begin()) --it;
                if(it!=H[now].end() && y1[it->second]<=ver[q].y && y2[it->second]>=ver[q].y) {
                    Union(ver[q].id, it->second);
                }
                V[nxt].insert({ver[q].y, ver[q].id});
                Remove[ver[q].x+ver[q].len].push_back(ver[q].id);
                ++q;
            }
            H[now].clear();
            H[now].swap(H[nxt]);
            for(auto id: Remove[i]) {
                V[now].erase({y1[id], id}); --cur;
            }
            for(auto x: V[nxt]) {
                V[now].insert(x); ++cur;
            }
            dbg(i, cur);
            V[nxt].clear();
            ss+=cur;
            while(pp<p) {
                auto it = V[now].lower_bound({y2[hor[pp].id]+1, -1});
                if(it!=V[now].end() && it->first==y2[hor[pp].id]+1) {
                    Union(hor[pp].id, it->second);
                }
                if(it!=V[now].begin()) --it;
                if(it!=V[now].end() && it->first==y1[hor[pp].id]-1) {
                    Union(hor[pp].id, it->second);
                }
                it = H[now].lower_bound({y2[hor[pp].id]+1, -1});
                dbg(i, pp, it->first, y2[hor[pp].id]);
                if(it!=H[now].end() && it->first==y2[hor[pp].id]+1) {
                    Union(hor[pp].id, it->second);
                }
                ++pp;
            }
            while(qq<q) {
                auto it = V[now].lower_bound({ver[qq].y+1, -1});
                if(it!=V[now].end() && it->first==ver[qq].y+1) {
                    Union(ver[qq].id, it->second);
                }
                it = V[now].lower_bound({ver[qq].y-1, -1});
                if(it!=V[now].end() && it->first==ver[qq].y-1) {
                    Union(ver[qq].id, it->second);
                }
                ++qq;
            }
            printf("%lld %d\n", ss, cc);
        }
        FOR(i, 1, n+2) Remove[i].clear();
    }
    return 0;
}
 
