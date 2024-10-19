
#include <bits/stdc++.h>
using namespace std;

namespace IO {
	inline int read() {
		int x = 0, f = 1;
		char ch = getchar();
		while (ch < '0' || ch > '9') {
			if (ch == '-')
				f = -1;
			ch = getchar();
		}
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48);
			ch = getchar();
		}
		return x * f;
	}
	inline void write(int x, char sp) {
		char ch[20];
		int len = 0;
		if (x < 0) {
			putchar('-');
			x = ~x + 1;
		}
		do {
			ch[len++] = x % 10 + (1 << 5) + (1 << 4);
			x /= 10;
		} while (x);
		for (int i = len - 1; ~i; i--)
			putchar(ch[i]);
		putchar(sp);
	}
} using namespace IO;

const int NN = 3005;
int n, m;
long long f[NN][NN], g[NN][NN], p[NN][NN], ans[NN];

signed main() {
	n = read();
	m = read();
	f[0][0] = g[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		g[0][i] = 1;
		for (int j = 1; j <= i; j++)
			f[i][j] = (f[i - 1][j] * j % m + f[i - 1][j - 1]) % m;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n - i; j++)
			g[i][j] = (g[i - 1][j] * j % m + g[i - 1][j + 1]) % m;
	for (int i = 1; i <= n; i++)
		for (int j = i; j; j--) {
			p[i][j] = (p[i][j + 1] + f[i - 1][j] * (g[n - i][j] + 2 * (n - i) * g[n - i - 1][j] % m) % m) % m;
			ans[j] = (ans[j] + p[i][j] + f[i - 1][j - 1] * (g[n - i][j] + 2 * (n - i) * g[n - i - 1][j] % m) % m) % m;
		}
	for (int i = 1; i <= n; i++)
		write(ans[i], ' ');
	puts("");
	return 0;
}