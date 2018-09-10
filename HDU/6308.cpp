// [Auto Archived]
// Submit: 2018-07-23 12:28:23
// Time: 436MS
// Memory: 1348K

#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cerr << "Debug: " << #args << " -> "; err(args); } while (0)
#else
#define dbg(...)
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

using namespace std;

inline char next_char() {
    return getchar();
}

char ch = next_char();

inline bool maybe_digit(char c) {
    return c >= '0' && c <= '9';
}

template<typename T>
inline bool rn(T& _v) {
    static bool negative;
    negative = false;
    _v = 0;
    while (!maybe_digit(ch) && ch != EOF) {
        negative = ch == '-'; ch = next_char();
    };
    if (ch == EOF)return false;
    do {
        _v = (_v << 1) + (_v << 3) + ch - '0';
    } while (maybe_digit(ch = next_char()));
    if (negative) _v = -_v;
    return true;
}

template<typename T>
inline T rn() {
    T v = T();
    rn(v);
    return v;
}

template<typename T>
inline bool rd(T& _v) {
    static bool negative;
    negative = false;
    _v = 0;
    while (!maybe_digit(ch) && ch != EOF) {
        negative = ch == '-'; ch = next_char();
    };
    if (ch == EOF)return false;
    do {
        _v = (_v * 10) + (ch - '0');
    } while (maybe_digit(ch = next_char()));
    static int stk[70], tp;
    if (ch == '.')
    {
        tp = 0;
        T _v2 = 0;
        while (maybe_digit(ch = next_char())) {
            stk[tp++] = ch - '0';
        }
        while (tp--)
        {
            _v2 = _v2 / 10 + stk[tp];
        }
        _v += _v2 / 10;
    }
    if (ch == 'e' || ch == 'E')
    {
        ch = next_char();
        static bool _neg = false;
        if (ch == '+') ch = next_char();
        else if (ch == '-') _neg = true, ch = next_char();
        if (maybe_digit(ch))
        {
            _v *= pow(10, rn<LL>()*(_neg ? -1 : 1));
        }
    }
    if (negative) _v = -_v;
    return true;
}

int main() {
    int T;
    while(rn(T)) {
        while(T--) {
            double v; int hh, mm; 
            rn(hh); rn(mm); rd(v);
            //scanf("%d%d UTC%lf", &hh, &mm, &v);
            //dbg(v);
            mm += round((hh+v+16)*60);
            hh = (mm/60)%24;
            mm %= 60;
            printf("%02d:%02d\n", hh, mm);
        }
    }
    return 0;
}