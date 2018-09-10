// [Auto Archived]
// Submit: 2016-02-06 16:19:30
// Time: 62MS
// Memory: 10892K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> PINT;
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define REP(i,a,n) for (int i=(int)(a);i<(int)(n);++i)
#define PER(i,a,n) for (int i=(int)(n)-1;i>=(int)(a);--i)
const int nmax = 40100;

struct edge {
    edge() { }
    edge(int f,int t,int c):from(f),to(t),cost(c) { }
    int from;
    int to;
    int cost;
};

struct mquery {
    mquery() { }
    mquery(int a,int b,int c,int d):from(a),to(b),ans(c),id(d) { }
    int from;
    int to;
    int ans;
    int id;
};

bool cmp_id(mquery lhs, mquery rhs) { return lhs.id < rhs.id; }
bool cmp_from(mquery lhs, mquery rhs) { return lhs.from < rhs.from; }

int t,n,m,a,b,k,fa[nmax],dist[nmax],vis[nmax];
vector<edge> g[nmax];
mquery query[500];
vector<int> q[nmax];

int find(int x)
{
    if (x == fa[x]) return x;
    int r = find(fa[x]);
    dist[x] += dist[fa[x]];
    fa[x] = r;
    return r;
}

int finddist(int x)
{
    find(x);
    return dist[x];
}

void tarjan(int u)
{
    vis[u] = true;
    REP(i,0,g[u].size()) {
        edge &e = g[u][i];
        if (!vis[e.to]) {
            tarjan(e.to);
            fa[e.to] = u;
            dist[e.to] = e.cost;
        }
    }
    pair<mquery*,mquery*> p = equal_range(query,query+2*m,mquery(u,0,0,0),cmp_from);
    for (mquery* i = p.first; i < p.second; ++i) {
        int lca = find(i->to);
        if (vis[lca]) q[lca].push_back(i-query);
    }
    REP(i,0,q[u].size()) {
        mquery &r = query[q[u][i]];
        r.ans = finddist(r.from) + finddist(r.to);
    }
    if (!q[u].empty()) q[u].clear();
}

int main()
{
    scanf("%d",&t);
    while (t--)
    {
        memset(dist,0,sizeof(dist));
        memset(vis,0,sizeof(vis));
        scanf("%d%d",&n,&m);
        REP(i,0,n+1) fa[i] = i;
        REP(i,0,n-1) scanf("%d%d%d",&a,&b,&k),g[a].push_back(edge(a,b,k)),g[b].push_back(edge(b,a,k));
        REP(i,0,m) {
            scanf("%d%d",&a,&b);
            query[2*i] = mquery(a,b,-1,i);
            query[2*i+1] = mquery(b,a,-1,i);
        }
        sort(query,query+2*m,cmp_from);
        tarjan(1);
        sort(query,query+2*m,cmp_id);
        REP(i,0,m) printf("%d\n",(query[2*i].ans==-1?query[2*i+1].ans:query[2*i].ans));
        REP(i,0,n+1) g[i].clear();
    }
    return 0;
}
