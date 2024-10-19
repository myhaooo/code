#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 100005;
int T, n, m, b[maxn], t[maxn];
int a[maxn], p[maxn], mx;
multiset<int> s;
void exgcd(int A, int B, int &x, int &y, int &gcdn)
{
	if (!B)
		x = 1, y = 0, gcdn = A;
	else
		exgcd(B, A % B, y, x, gcdn), y -= (A / B) * x;
}
int ExCRT()
{
	int ans = 0, lcm = 1, x, y, gcdn, A, B, C;
	for (int i = 1; i <= n; ++i)
	{
		// cout<<lcm<<" \n";
		A = (__int128)b[i] * lcm % p[i];
		B = p[i];
		C = (a[i] - b[i] * ans % p[i] + p[i]) % p[i];
		exgcd(A, B, x, y, gcdn), x = (x % B + B) % B;
		if (C % gcdn)
			return -1;
		ans += (__int128)(C / gcdn) * x % (B / gcdn) * lcm % (lcm *= B / gcdn);
		ans %= lcm;
	}
	if (ans < mx)
		ans += ((mx - ans - 1) / lcm + 1) * lcm;
	return ans;
}
signed main()
{
#ifndef LOCAL
#define NDEBUG
	cin.tie(0), cout.tie(0);
#define file(a)                               \
	FILE *FI = freopen(#a ".in", "r", stdin); \
	FI = freopen(#a ".out", "w", stdout)
	// file();
#else
#ifdef LEN
	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
#endif
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
	// #include "../local.h"
#endif

	cin >> T;
	while (T--)
	{
		s.clear(), mx = 0;
		cin >> n >> m;
		for (int i = 1; i <= n; ++i)
			cin >> a[i];
		for (int i = 1; i <= n; ++i)
			cin >> p[i];
		for (int i = 1; i <= n; ++i)
			cin >> t[i];
		for (int i = 1, x; i <= m; ++i)
			cin >> x, s.insert(x);

		for (int i = 1; i <= n; ++i)
		{
			auto u = s.upper_bound(a[i]);
			if (u != s.begin())
				u--;
			b[i] = *u, s.erase(u), s.insert(t[i]);
			mx = max(mx, (a[i] - 1) / b[i] + 1);
		}
		cout << ExCRT() << "\n";
	}
}