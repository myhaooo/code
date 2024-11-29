#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
const int P = 1e9 + 7;
int m, n, k, s, a[N];
int fac[N * N], inv[N * N];
inline int qpow(int x, int y)
{
    int ans = 1;
    for (; y; x = 1ll * x * x % P, y >>= 1)
        ans = (y & 1) ? 1ll * ans * x % P : ans;
    return ans;
}
void init()
{
    fac[0] = 1;
    for (int i = 1; i <= n * m; i++)
        fac[i] = 1ll * fac[i - 1] * i % P;
    inv[n * m] = qpow(fac[n * m], P - 2);
    for (int i = n * m; i >= 1; i--)
        inv[i - 1] = 1ll * inv[i] * i % P;
}
inline int C(int x, int y) { return x < y ? 0 : 1ll * fac[x] * inv[y] % P * inv[x - y] % P; }
int solve(int a, int s, int p)
{
    int sum = 0;
    for (int k = 0; k <= a && k * m <= s; k++)
    {
        int cur = 1ll * (C(s - k * m + a, a) - C(s - p - k * m + a, a) + P) % P * C(a, k) % P;
        sum = (1ll * sum + ((k & 1) ? -cur : cur) + P) % P;
    }
    return sum;
}
int ans;
signed main()
{
    freopen("dba.in", "r", stdin);
    freopen("dba.out", "w", stdout);
    scanf("%d%d", &m, &n), init();
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i), s += a[i];
    for (int i = 1; i < n; i++)
        ans = (ans + solve(n - i, s, a[i])) % P, s -= a[i];
    printf("%d\n",
           ans);
    return 0;
}
