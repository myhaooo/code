#include <bits/stdc++.h>
#define rg register
#define qwq 0
#define int long long
using namespace std;
const int M = 1 << 10, mod = 998244353;
int n, K, m, nn;
int f[2][M][13];

inline void add(int &x, int y) {
	x = (x + y) % mod;
}

main() {
	cin >> n >> K;
	m = n / K;
	nn = 1 << m;
	f[0][0][0] = 1;
	for (rg int i = 1; i <= n; i++) {
		rg int ii = i & 1;
		for (rg int s = 0; s < nn; s++) {
			for (rg int j = 0; j <= m; j++) {
				f[ii][s][j] = 0;
			}
		}
		for (rg int s = 0; s < nn; s++) {
			for (rg int j = 0; j <= m; j++) {
				if (j && (s & (1 << j - 1)))
					continue;
				for (rg int k = 0; k <= m; k++) {
					if (k && (!(s & (1 << k - 1))))
						continue;
					if (!j) {
						add(f[ii][s][0], f[ii ^ 1][s][k]);
						continue;
					}
					if (!k) {
						add(f[ii][s | (1 << j - 1)][j], f[ii ^ 1][s][0]);
						continue;
					}
					if (__gcd(j, k) != 1) {
						add(f[ii][s | (1 << j - 1)][j], f[ii ^ 1][s][k]);
					}
				}
			}
		}
	}
	rg int ans = 0;
	for (rg int i = 0; i <= m; i++)
		add(ans, f[n & 1][nn - 1][i]);
	for (rg int i = 1; i <= n - m; i++)
		ans = ans * i % mod;
	cout << ans << "\n";
}
