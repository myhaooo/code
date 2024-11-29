#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5;
const ll MOD = 1e9 + 9;
int n, m, a[300005], num[300005], ans[300005];
ll f[300005], fac[300005], ifac[300005];
bool flag[300005];
#define gcd __gcd 
ll Pow(ll a, ll b) {
    ll s = 1;
    while (b) {
        if (b & 1)
            s = s * a % MOD;
        a = a * a % MOD, b = b >> 1;
    }
    return s;
}
ll C(int n, int m) {
    if (n < m)
        return 0;
    return fac[n] * ifac[m] % MOD * ifac[n - m];
}
int main() {
    freopen("sor.in", "r", stdin);
    freopen("sor.out", "w", stdout);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= N; i++) fac[i] = fac[i - 1] * i % MOD;
    ifac[N] = Pow(fac[N], MOD - 2);
    for (int i = N - 1; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        for (int j = 1; j * j <= a[i]; j++)
            if (a[i] % j == 0) {
                num[j]++;
                if (j * j != a[i])
                    num[a[i] / j]++;
            }
    }
    for (int j = 7; j; j--) {
        memset(f, 0, sizeof(f));
        for (int i = N; i; i--) {
            f[i] = C(num[i], j);
            for (int j = i + i; j <= N; j += i) f[i] = (f[i] + MOD - f[j]) % MOD;
        }
        for (int i = 1; i <= m; i++)
            if (f[i] != 0)
                ans[i] = j;
    }
    for (int i = 1; i <= m; i++) {
        if (!ans[i])
            puts("-1 -1");
        else
            printf("%d %d\n", ans[i], num[i]);
    }
    return 0;
}
