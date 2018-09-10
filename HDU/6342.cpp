// [Auto Archived]
// Submit: 2018-08-01 12:48:51
// Time: 15MS
// Memory: 2256K

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

#define OP 1
#define ZERO 2
#define DIGIT 4
#define QUESTION 7

const int N = 1E3 + 100;

char s[N], t[N];
int n, pos[N];

int get(char s) {
    if (s == '+' || s == '*') return OP;
    if (s == '0') return ZERO;
    if (s >= '1' && s <= '9') return DIGIT;
    if (s == '?') return QUESTION;
    assert (0);
}

bool go() {
    FOR (i, 0, n) {
        if (s[i] != '?') {
            if (!pos[i]) return false;
            t[i] = s[i];
        }
        else if (pos[i] & DIGIT) t[i] = '1';
        else if (pos[i] & OP) t[i] = '+';
        else if (pos[i] & ZERO) t[i] = '0';
        else return false;
    }
    return true;
}

int main() {
    int T; cin >> T;
    while (T--) {
        memset(s, 0, sizeof s);
        memset(t, 0, sizeof t);
        scanf("%s", s);
        n = strlen(s);
        FOR (i, 0, n)
            pos[i] = get(s[i]);
        pos[0] &= ~OP;
        pos[n - 1] &= ~OP;
        FOR (i, 0, n) {
            if (pos[i] == OP)
                pos[i + 1] &= ~OP;
            if ((i == 0 || pos[i - 1] == OP) && pos[i] == ZERO) {
                pos[i + 1] &= ~ZERO;
                pos[i + 1] &= ~DIGIT;
            }
        }
        FOR (i, 0, n) dbg(i, pos[i]);
        if (go()) puts(t);
        else puts("IMPOSSIBLE");
    }
}
