// [Auto Archived]
// Submit: 2017-08-09 13:06:31
// Time: 1762MS
// Memory: 15616K

#include <bits/stdc++.h>
using namespace std;
const int maxnode = 130;
const int modn = 998244353;
const int CHAR_SIZE = 2;
const int MAX_SIZE = 500;

inline int mp(char ch) { return ch - '0'; }

struct AC_Automata {
  int ch[MAX_SIZE][CHAR_SIZE], danger[MAX_SIZE], fail[MAX_SIZE];
  int sz;
  void init() {
    sz = 1;
    memset(ch[0], 0, sizeof ch[0]);
    memset(danger, 0, sizeof danger);
  }
  void _insert(const string &s, int m) {
    int n = s.size();
    int u = 0, c;
    for (int i = 0; i < n; i++) {
      c = mp(s[i]);
      if (!ch[u][c]) {
        memset(ch[sz], 0, sizeof ch[sz]);
        danger[sz] = 0;
        ch[u][c] = sz++;
      }
      u = ch[u][c];
    }
    danger[u] |= 1 << m;
  }
  void _build() {
    queue<int> Q;
    fail[0] = 0;
    for (int c = 0, u; c < CHAR_SIZE; c++) {
      u = ch[0][c];
      if (u) {
        Q.push(u);
        fail[u] = 0;
      }
    }
    int r;
    while (!Q.empty()) {
      r = Q.front();
      Q.pop();
      danger[r] |= danger[fail[r]];
      for (int c = 0, u; c < CHAR_SIZE; c++) {
        u = ch[r][c];
        if (!u) {
          ch[r][c] = ch[fail[r]][c];
          continue;
        }
        fail[u] = ch[fail[r]][c];
        Q.push(u);
      }
    }
  }
} ac, acr;

int T, n, L;
int slen[10];
char s[10][130], str[130], tt[200];
const int offset = 100;
int f[2][70][maxnode][maxnode], g[70][maxnode][maxnode];

void dfs(int depth, int loc1, int loc2, int state) {
    if (depth >= 19 || depth >= L) return;
    for (int i = 0; i <= 1; ++i) {
        tt[offset + depth] = i + '0';
        tt[offset - depth - 1] = 1 - i + '0';
        int newloc1 = ac.ch[loc1][i];
        int newloc2 = acr.ch[loc2][1 - i];
        int nstate = state;
        for (int j = 0; j < n; ++j) {
            if (strncmp(tt + offset - depth - 1, s[j], slen[j]) == 0 ||
                strncmp(tt + offset + depth - slen[j] + 1, s[j], slen[j]) == 0)
                nstate |= 1 << j;
        }
        // printf("%s %d %d %d\n", tt + offset - depth - 1, depth + 1, nstate, newloc1);
        if (depth + 1 == 19 || depth + 1 == L)
            f[(depth + 1) % 2][nstate][newloc1][newloc2] = (f[(depth + 1) % 2][nstate][newloc1][newloc2] + 1) % modn;
        dfs(depth + 1, newloc1, newloc2, nstate);
    }
    tt[offset + depth] = tt[offset - depth - 1] = 0;
}

int main() {   
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++cas) {
        ac.init();
        acr.init();  // ac_automata for reverse
        scanf("%d%d", &n, &L);
        for (int i = 0; i < n; i++) {
            scanf("%s", str);
            // cout << ss << endl;
            ac._insert(string(str), i);
            strcpy(s[i], str);
            slen[i] = strlen(s[i]);
            reverse(str, str + strlen(str));
            acr._insert(string(str), i);
        }
        ac._build();
        acr._build();
        memset(f, 0, sizeof f);
        memset(g, 0, sizeof g);
        memset(tt, 0, sizeof tt);
        dfs(0, 0, 0, 0);
        // printf("%d\n", ac.sz);
        // for (int i = 0; i < ac.sz; ++i)
        //     printf("%d\n", ac.danger[i]);
        for (int i = 19; i < L; ++i) {
            int u = i % 2;
            int v = 1 - u;
            memset(f[v], 0, sizeof f[v]);
            for (int j = 0; j < (1 << n); ++j)
                for (int k = 0; k < ac.sz; ++k)
                    for (int k2 = 0; k2 < acr.sz; ++k2) {
                        if (f[u][j][k][k2]) {
                            for (int ne = 0; ne <= 1; ++ne) {
                                int nk = ac.ch[k][ne], nk2 = acr.ch[k2][1 - ne];
                                int newmask = j | ac.danger[nk] | acr.danger[nk2];
                                f[v][newmask][nk][nk2] = (f[v][newmask][nk][nk2] + f[u][j][k][k2]) % modn;
                            }
                        }
                }
        }
        int ans = 0;
        int mask = 0;
        for (int j = 0; j < n; ++j)
            mask += 1 << j;
        for (int k = 0; k < ac.sz; ++k)
            for (int k2 = 0; k2 < acr.sz; ++k2)
                ans = (ans + f[L % 2][mask][k][k2]) % modn;
        printf("%d\n", ans);
    }
}
