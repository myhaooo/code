#include <bits/stdc++.h>
#define N 55
#define int long long
#define mod 1000000007
using namespace std;
int n, m;
int dp[N][N][N * N];

void add(int &x, int y) {
	x += y;
	if (x > mod)
		x -= mod;
}

signed main() {
	cin >> n >> m;
	dp[0][0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= i; j++)
			for (int k = 2 * j; k <= m; k++) {
				add(dp[i][j][k], dp[i - 1][j][k - 2 * j] * (2 * j + 1) % mod);
				add(dp[i][j][k], dp[i - 1][j + 1][k - 2 * j] * (j + 1) % mod * (j + 1) % mod);
				add(dp[i][j][k], j >= 1 ? dp[i - 1][j - 1][k - 2 * j] : 0);
			}
	cout << dp[n][0][m] << "\n";
	return 0;
}
