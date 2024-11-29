#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e3 + 5;
const int mod = 998244353;
int n, m;
char s[maxn][maxn];
int f[maxn][maxn], g[maxn][maxn], h[maxn][maxn], p[maxn][maxn];
signed main() {
//    freopen("grid.in", "r", stdin);
//    freopen("grid.out", "w", stdout);
    cin>>n>>m;
    for (int i = 1; i <= n; i++) {
        scanf("%s", s[i] + 1);
    }
    g[1][0] = 1;
    p[1][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            p[i][j] = (p[i - 1][j] + p[i][j - 1]) % mod;
            f[i][j] = (f[i - 1][j] + f[i][j - 1]) % mod;
            g[i][j] = (g[i - 1][j] + g[i][j - 1]) % mod;
            h[i][j] = (h[i - 1][j] + h[i][j - 1]) % mod;
            if (s[i][j] == '+') {
                f[i][j] = (f[i][j] + h[i][j]) % mod;
                g[i][j] = p[i][j];
                h[i][j] = 0;
            } else if (s[i][j] == '*') {
                g[i][j] = h[i][j];
                h[i][j] = 0;
            } else {
                h[i][j] = (h[i][j] * 10ll + (s[i][j] - '0') * g[i][j]) % mod;
            }
        }
    }
    cout<<(f[n][m] + h[n][m]) % mod;
    return 0;
}
