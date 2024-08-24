#include <cstdio>
#include <cstring>
#define int long long

const int mod = 1e9 + 7, inv2 = 500000004, inv6 = 166666668;
int n, a[1000005], f[1000005][2];
inline int s(int n) {return n * (n + 1) % mod * inv2 % mod;}
inline int t(int n) {return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;}

int solve(int p, int q) {
	memset(f, 0, sizeof f);
	f[1][0] = p ^ 1, f[1][1] = p;
	for (int i = 2; i <= n; ++ i) {
		f[i][0] = (f[i - 1][1] * (a[i - 1] - q + 1) + f[i - 1][0] * s(a[i - 1] - q)) % mod;
		f[i][1] = (f[i - 1][1] * s(a[i - 1]) + f[i - 1][0] * (a[i - 1] * s(a[i - 1]) % mod - t(a[i - 1]))) % mod;
	}
	if (p == 0) return (f[n][1] * (a[n] - q + 1) + f[n][0] * s(a[n] - q)) % mod;
	else return (f[n][1] * s(a[n]) + f[n][0] * (a[n] * s(a[n]) % mod - t(a[n]))) % mod;
}

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; ++ i) scanf("%lld", a + i);
	printf("%lld", ((solve(0, 0) + solve(1, 0) - solve(0, 1) - solve(1, 1)) % mod + mod) % mod);
	return 0;
}