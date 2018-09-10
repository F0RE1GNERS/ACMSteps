// [Auto Archived]
// Submit: 2018-07-30 12:22:17
// Time: 0MS
// Memory: 1380K

#include <bits/stdc++.h>
 
//#undef zerol

using namespace std;
using LL = long long;
using ULL = unsigned long long;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i < _##i; ++i)
#ifdef zerol
#define dbg(args...) do { cerr << "Debug: " << #args << " -> "; err(args); } while (0)
#define fuck(x) do { printf("fuck@%d\n", x); } while(0)
#else
#define dbg(...)
#define fuck(...)
#endif // zerol
void err() { cerr << endl; }
template<typename T, typename... Args>
void err(T a, Args... args) { cerr << a << ' '; err(args...); }
// ----------------------------------------------------------------

const int N = 100;

char m[N][N];

char example[][10] = {
    "+-+  ",
    "|.|/ ",
    "+-+.+",
    " /./|",
    "  +-+"
};
        int a, b, c;

void print() {
    
        for(int i = 2*(b+c); i>=0; --i) {
            m[i][2*(a+b)+1] = 0;
            printf("%s\n", m[i]);
        }
}

void trans(char& a, char b) {
    if(b!=' ') a = b;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        memset(m, '.', sizeof(m));
        scanf("%d%d%d", &a, &b, &c);
        for(int i = b-1; i>=0; --i)
            for(int j = 0; j<c; ++j)
                for(int k = 0; k<a; ++k) {
                    int x = i*2+2*j;
                    int y = i*2+2*k;
                    for(int ii = 0; ii<5; ++ii)
                        for(int jj = 0; jj<5; ++jj) {
                            trans(m[x+ii][y+jj], example[ii][jj]);
                        }
                }
        print();
    }
    return 0;
}