#include <bits/stdc++.h>
#define int long long

using namespace std;

const int Maxn = 2e5 + 5;
const int Inf = 0x3f3f3f3f;
const int Mod = 998244353;

int n, s[Maxn], p[Maxn];
int calc(int n, int p[], int s[])
{
    int ret = p[1];
    for(int i = 2; i <= n; i++) {
        if(s[i - 1] == 1)
			ret = max(ret, p[i]);
        else 
			ret = min(ret, p[i]);
	}
    return ret;
}

int sum[2][Maxn];

int f[Maxn], inv[Maxn];

int qpow(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) {
			res = res * a % Mod;
		}
		a = a * a % Mod;
		b >>= 1;
	}
	return res;
}

void init() {
	f[0] = 1;
	for(int i = 1; i <= n; i++) {
		f[i] = f[i - 1] * i % Mod;
	}
	inv[n] = qpow(f[n], Mod - 2);
	for(int i = n - 1; i >= 0; i--) {
		inv[i] = inv[i + 1] * (i + 1) % Mod;
	}
}

int C(int n, int m) {
	if(n < m) return 0;
	return f[n] * inv[n - m] % Mod * inv[m] % Mod;
}

signed main() {
//	freopen("2.in", "r", stdin); 
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	if(n <= 10) {
		for(int i = 1; i < n; i++) {
			cin >> s[i];
		}
		for(int i = 1; i <= n; i++) {
			p[i] = i;
		}
		int ans = 0;
		do {
			int tot = calc(n, p, s);
			(ans += tot) %= Mod;	
		}while(next_permutation(p + 1, p + n + 1));
		cout << ans << '\n';
		return 0;
	}
	init();
	for(int i = 2; i <= n; i++) {
		cin >> s[i];
	}
	for(int i = n; i >= 2; i--) {
		if(s[i] == 1) {
			sum[1][i] = sum[1][i + 1] + 1;
			sum[0][i] = sum[0][i + 1];
		}
		else {
			sum[1][i] = sum[1][i + 1];
			sum[0][i] = sum[0][i + 1] + 1;
		}
	}
	sum[1][1] = sum[1][2], sum[0][1] = sum[0][2];
	int ans = 0;
	for(int i = 1; i <= n; i++) {//ans
		for(int j = 1; j <= n; j++) {//pos
			if(j == 1 || s[j] == 0) {
				sum[0][1]++;
				(ans += i * C(i - 1, sum[1][j]) % Mod * C(n - i, sum[0][j] - 1) % Mod 
				* ((f[sum[1][j] + 1] - f[sum[1][j]] + Mod) % Mod) % Mod * f[sum[0][j] - 1] % Mod * f[j - 1] % Mod) %= Mod;
				sum[0][1]--;
			}
			if(j == 1 || s[j] == 1) {
				sum[1][1]++;
				(ans += i * C(i - 1, sum[1][j] - 1) % Mod * C(n - i, sum[0][j]) % Mod 
				* f[sum[1][j] - 1] % Mod * ((f[sum[0][j] + 1] - f[sum[0][j]] + Mod) % Mod) % Mod * f[j - 1] % Mod) %= Mod;
				sum[1][1]--;
			}
			if(j == 1) {
				(ans += i * C(i - 1, sum[1][j]) % Mod * C(n - i, sum[0][j]) % Mod
				* f[sum[1][j]] % Mod * f[sum[0][j]] % Mod) %= Mod;
			}
//			cout << ans << " ";
		}
//		cout << '\n';
	}
	cout << ans << '\n';
	return 0; 
}