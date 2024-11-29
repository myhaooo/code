#include <bits/stdc++.h>
#define int long long
using namespace std;
int mod;
int ksm(int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1)
            ans = ans * x % mod;
        x = x * x % mod, y /= 2;
    }
    return ans;
}
int solve(int x, int y) {
    if (y < 0)
        return 0;
    if (!y)
        return 1;
    if (y == 1)
        return x + 1;
    if (y % 2 == 1)
        return (ksm(x, y / 2 + 1) + 1) * solve(x, y / 2) % mod;
    return (ksm(x, y) + (ksm(x, y / 2) + 1) * solve(x, y / 2 - 1) % mod) % mod;
}
int n, k, a[1000001], ans, m = 1, q[1000001], t, w, s, p;
main() {
    freopen("animism.in", "r", stdin);
    freopen("animism.out", "w", stdout);
    cin >> n >> k >> mod;
    q[0] = 1;
    for (int i = 0; i < k; i++) scanf("%lld", &a[i]);
    if (k % 2) {
        k *= 2;
        for (int i = k / 2; i < k; i++) a[i] = a[i - k / 2];
    }
    for (int i = 0; i < k; i++) (m *= a[i]) %= mod, q[i + 1] = q[i] * a[i] % mod;
    t = n / k;
    n -= t * k;
    for (int i = n % 2; i < k; i += 2) w += q[i];
    s = ksm(m, t);
    w %= mod;
    ans = w * solve(m, t - 1) % mod;
    for (int i = n % 2; i <= n; i += 2) ans = (ans + s * q[i] % mod) % mod;
    cout << ans;
    return 0;
}
