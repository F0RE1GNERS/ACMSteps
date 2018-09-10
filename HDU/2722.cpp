// [Auto Archived]
// Submit: 2016-04-07 16:13:14
// Time: 15MS
// Memory: 1644K

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LLD;
typedef pair<int,int> PINT;
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define X first
#define Y second
#define SQR(i) (i)*(i)
const int nmax = 500;
const int inf = 1e9+7;
const LL linf = 1e16;
const int modulo = 1e9+7;
const double pi = acos(-1.0);

struct edge {
    edge(int t,int c):to(t),cost(c) { }
    int to,cost;
};

struct node {
    node() {}
    node(int i,int c):id(i),cost(c) { }
    int id,cost;
    bool operator>(const node &c) const {
        return cost > c.cost;
    }
};

int h,w,n;
vector<edge> g[nmax];
int dist[nmax],vis[nmax],s,t;

inline int find_id(int i, int j)
{
    return i*w+j;
}

void input_edge_data(pair<int,char> &p)
{
    int i;
    char j;
    scanf("%d",&i);
    while (scanf("%c",&j),j==' '||j=='\n');;
    p.first = i;
    p.second = j;
}

void input_horizontal(int line)
{
    pair<int,char> p;
    int intera, interb;
    for (int i = 0; i < w-1; ++i)
    {
        intera = find_id(line,i);
        interb = find_id(line,i+1);
        input_edge_data(p);
        if (p.first == 0) continue;
        p.first = 2520 / p.first;
        if (p.second == '*')
        {
            g[intera].push_back(edge(interb,p.first));
            g[interb].push_back(edge(intera,p.first));
        }
        if (p.second == '>')
            g[intera].push_back(edge(interb,p.first));
        if (p.second == '<')
            g[interb].push_back(edge(intera,p.first));
    }
}

void input_vertical(int line)
{
    pair<int,char> p;
    int intera, interb;
    for (int i = 0; i < w; ++i)
    {
        intera = find_id(line,i);
        interb = find_id(line+1,i);
        input_edge_data(p);
        if (p.first == 0) continue;
        p.first = 2520 / p.first;
        if (p.second == '*')
        {
            g[intera].push_back(edge(interb,p.first));
            g[interb].push_back(edge(intera,p.first));
        }
        if (p.second == 'v')
            g[intera].push_back(edge(interb,p.first));
        if (p.second == '^')
            g[interb].push_back(edge(intera,p.first));
    }
}

int main()
{
    while (scanf("%d%d",&h,&w)!=EOF && h+w>0)
    {
        h++,w++;
        n = h*w;
        memset(vis,0,sizeof(vis));
        for (int i = 0; i < n; ++i)
        {
            g[i].clear();
            dist[i] = inf;
        }
        for (int i = 0; i < h-1; ++i)
        {
            input_horizontal(i);
            input_vertical(i);
        }
        input_horizontal(h-1);
        s = 0;
        t = h*w-1;
        dist[s] = 0;
        priority_queue<node,vector<node>,greater<node> > q;
        q.push(node(s,dist[s]));
        while (!q.empty())
        {
            node u;
            do {
                u = q.top();
                q.pop();
            } while (!q.empty()&&vis[u.id]);
            if (q.empty()&&vis[u.id]) break;
            if (u.id == t) break;
            vis[u.id] = 1;
            for (int i = 0; i < g[u.id].size(); ++i)
            {
                edge &e = g[u.id][i];
                if (!vis[e.to] && u.cost+e.cost<dist[e.to])
                {
                    dist[e.to] = u.cost+e.cost;
                    q.push(node(e.to,dist[e.to]));
                }
            }
        }
        if (dist[t]>=inf) printf("Holiday\n");
        else printf("%d blips\n",dist[t]);
    }
    return 0;
}
