#include <bits/stdc++.h>
#define int unsigned long long
using namespace std;
#define gcd __gcd
int e, N, c, d, n, r;
inline int mul(int x, int y, int c)
{
	return (__int128)((x % c) * (y % c)) % c;
}
inline int qpow(int a, int b, int mod)
{
	int ans = 1;
	while (b)
	{
		if (b & 1)
			ans = (__int128)ans * a % mod;
		a = (__int128)a * a % mod;
		b >>= 1;
	}
	return ans;
}
void exgcd(int a, int b, int &x, int &y)
{
	if (!b)
		x = 1, y = 0;
	else
	{
		exgcd(b, a % b, y, x);
		y = (r + y - mul(a / b, x, r)) % r;
	}
}
int pollard(int n, int c)
{
	mt19937 rand(time(0));
	int x, y, d, i = 1, k = 2;
	x = 1LL * rand() % (n - 1) + 1;
	y = x;
	while (1)
	{
		x = (mul(x, x, n) + c) % n;
		d = gcd((x - y + n) % n, n);
		if (d > 1 && d < n)
			return d;
		if (x == y)
			return n;
		if (++i == k)
			k <<= 1, y = x;
	}
	return 23333333;
}

int tmp;
signed main()
{
	mt19937 rand(time(0));

	cin >> e >> N >> c;
	int p = N;
	while (p >= N)
		p = pollard(N, 1LL * rand() % (n - 1) + 1);
	r = (p - 1) * (N / p - 1);
	exgcd(e, r, d, tmp);
	cout << d << " " << qpow(c, d, N);
	return 0;
}