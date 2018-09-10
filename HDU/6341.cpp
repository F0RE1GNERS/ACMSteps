// [Auto Archived]
// Submit: 2018-08-01 14:13:23
// Time: 31MS
// Memory: 1428K

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

const int maxn = 20;
const int N = 16;
const int P = 4;

int n, ans;
int s[N][N], tmp[N][N];
int rot_x[N][N], rot_y[N][N];

void rotate(int x, int y) {
    FOR (i, 0, P) FOR (j, 0, P) tmp[rot_x[i][j]][rot_y[i][j]] = s[x + i][y + j];
    FOR (i, 0, P) FOR (j, 0, P) s[x + i][y + j] = tmp[i][j];
    // if (x == 0 && y == 0) FOR (i, 0, P) FOR (j, 0, P) dbg(x + i, y + j, s[x + i][y + j]);
}

int rx[N], ry[N];

bool check(int x, int y) {
    // dbg(x, y);
    FOR (i, 0, P) FOR (j, 0, P) {
        if (rx[x + i] & (1 << s[x + i][y + j])) { dbg(rx[x+i],s[x+i][y+j],x+i); return false; }
        if (ry[y + j] & (1 << s[x + i][y + j])) { dbg(ry[y+j],s[x+i][y+j],y+j); return false; }
    }
    // dbg(x, y, "check");
    return true;
}

void mark(int x, int y) {
    FOR (i, 0, P) FOR (j, 0, P) {
        rx[x + i] |= 1 << s[x + i][y + j];
        ry[y + j] |= 1 << s[x + i][y + j];
    }
}

void unmark(int x, int y) {
    FOR (i, 0, P) FOR (j, 0, P) {
        rx[x + i] &= ~(1 << s[x + i][y + j]);
        ry[y + j] &= ~(1 << s[x + i][y + j]);
    }
}

void dfs(int now, int i, int j) {
    // if (now > ans) break;
    if (i == 4) {
        ans = min(ans, now);
        return;
    }
    int ni = i, nj = j + 1;
    if (nj == 4) {
        nj = 0; ni++;
    }
    dbg(now, i, j, ni, nj);

    FOR (d, 0, 4) {
        if (check(i * 4, j * 4)) {
            mark(i * 4, j * 4);
            dfs(now + (4 - d) % 4, ni, nj);
            unmark(i * 4, j * 4);
        }
        rotate(i * 4, j * 4);
    }
}

void init() {
    FOR (i, 0, 4) { rot_x[i][0] = 3; rot_y[i][0] = i; }
    FOR (i, 0, 4) { rot_x[3][i] = 3 - i; rot_y[3][i] = 3; }
    FOR (i, 0, 4) { rot_x[i][3] = 0; rot_y[i][3] = i; }
    FOR (i, 0, 4) { rot_x[0][i] = 3 - i; rot_y[0][i] = 0; }
    rot_x[1][1] = 2; rot_y[1][1] = 1;
    rot_x[2][1] = 2; rot_y[2][1] = 2;
    rot_x[2][2] = 1; rot_y[2][2] = 2;
    rot_x[1][2] = 1; rot_y[1][2] = 1;
    FOR (i, 0, 4) FOR (j, 0, 4) dbg(i, j, rot_x[i][j], rot_y[i][j]);
}

char m[maxn][maxn];

int main() {
    init();

    int T; cin >> T;
    while (T--) {
        ans = 1E9;
        FOR (i, 0, N) scanf("%s", m[i]);
        FOR (i, 0, N) FOR (j, 0, N) {
            if (m[i][j] >= 'A') s[i][j] = m[i][j] - 'A' + 10;
            else s[i][j] = m[i][j] - '0';
        }
        FOR (i, 0, N) FOR (j, 0, N) dbg(i, j, s[i][j]);
        dfs(0, 0, 0);

        // FOR (i, 0, N) FOR (j, 0, N) {
        //     if (m[i][j] >= 'A') assert (s[i][j] == m[i][j] - 'A' + 10);
        //     else assert (s[i][j] == m[i][j] - '0');
        // }
        cout << ans << endl;
    }
}
