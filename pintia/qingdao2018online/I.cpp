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

typedef double ld;
const ld pi = acos(-1);
const ld eps = 1e-9;
const ld eps2 = 1e-9;
 
ld f(ld theta)
{
	ld s = sin(theta);
	return 1 / (sqrt(s * s + 3) - s);
}

ld simpson(ld l, ld r)
{
	ld c = (l + r) / 2;
	return (f(l) + 4 * f(c) + f(r)) * (r - l) / 6;
}

ld asr(ld l, ld r, ld eps, ld S)
{
	ld m = (l + r) / 2;
	ld L = simpson(l, m), R = simpson(m, r);
	if (fabs(L + R - S) < 15 * eps) return L + R + (L + R - S) / 15;
	return asr(l, m, eps / 2, L) + asr(m, r, eps / 2, R);
}

ld asr(ld l, ld r, ld eps) { return asr(l, r, eps, simpson(l, r)); }

int main() {
	int T; cin >> T;
	ld full = asr(0, pi, eps)+2;
	while(T--) {
		
		ld V, R, D;
		cin >> V >> R >> D;
		if(2*R*full>=D)
		{
			printf("%.12f\n", (double)(D/V));
			continue;
		}
		ld l = pi / 2, r = pi, ans = 1e9;
		while (l + eps2 < r)
		{
			ld phi = (l + r) / 2;
			ld t = 2*R/V*asr(0, phi, eps);
			ld x = D - (2 * R * (1 - cos(phi)) + V * t), y = 2 * R * sin(phi);
			ld d = sqrt(x * x + y * y);
			ld alpha = atan2(2 * y / d, 2 * x / d - 1);
			if (phi-alpha > pi/2)
			{
				ans = min(ans, t + d / V / 2);
				r = phi;
			}
			else
			{
				l = phi;
			}
		}
		printf("%.12f\n", (double)ans);
	}
}
