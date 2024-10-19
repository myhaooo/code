#include <bits/stdc++.h>
using namespace std;
const int N = 5e5+5, M = 105, INF = 0x3f3f3f3f;
int n, K, p, sum[N], f[M][N], t[105];
int main() {
    ios::sync_with_stdio(false);
	#ifndef LOCAL
	cin.tie(0),cout.tie(0);
    #endif
    #ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
	scanf("%d%d%d", &n, &K, &p);

	for (int i = 1; i <= n; i++) 
		scanf("%d", &sum[i]), 
		sum[i] = (sum[i] + sum[i-1]) % p;

	for (int i = 1; i <= n; i++) f[0][i] = INF;
    
	for (int i = 1; i <= K; i++) {
		for (int j = 0; j < p; j++) t[j] = INF;
		if (i == 1) t[0] = 0; 
		for (int j = 1; j <= n; j++) {
			f[i][j] = INF;
			for (int k = 0; k < p; k++)
				f[i][j] = min(f[i][j], t[k] + (sum[j] - k + p) % p);
			t[sum[j]] = min(t[sum[j]], f[i-1][j]);
		}
	}
	printf("%d", f[K][n]);
	return 0;
}