#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;
const int N = 5e5 + 5;
bool dp[2005][2005];
bool chk(int x[], int y[], int n, int m) 
{
	if (x[1] <= y[1] || x[n] <= y[m]) return false; 
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) dp[i][j] = false;
	dp[1][1] = true;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) 
			if (x[i] > y[j]) dp[i][j] |= (dp[i - 1][j - 1] | dp[i - 1][j] | dp[i][j - 1]);
	return dp[n][m];
}
int x[N], y[N], ttx[N], tty[N];
int main()
{
	int n, m, q;
	scanf("%*d%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
	for (int i = 1; i <= m; i++) scanf("%d", &y[i]);
	putchar(chk(x, y, n, m) || chk(y, x, m, n) ? '1' : '0');
	while (q--)
	{
		for (int i = 1; i <= n; i++) ttx[i] = x[i];
		for (int i = 1; i <= m; i++) tty[i] = y[i];
		int cx, cy;
		scanf("%d%d", &cx, &cy);
		while (cx--) {int p, v; scanf("%d%d", &p, &v); ttx[p] = v;}
		while (cy--) {int p, v; scanf("%d%d", &p, &v); tty[p] = v;}
		putchar(chk(ttx, tty, n, m) || chk(tty, ttx, m, n) ? '1' : '0');
	}
	return 0;
}