#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, ans = 1, pos1 = 1, pos2 = 1, fac[N], inv[N], fro[N], nex[N];
int qpow(int x, int y)
{
    int temp = 1;
    x %= mod;
    y %= (mod - 1);
    while (y)
    {
        if (y & 1)
            temp = temp * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return temp;
}
void init()
{
    fac[0] = inv[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = fac[i - 1] * i % mod;
    inv[n] = qpow(fac[n], mod - 2);
    for (int i = n - 1; i >= 1; i--)
        inv[i] = inv[i + 1] * (i + 1) % mod;
}
int C(int x, int y) { return fac[x] * inv[y] % mod * inv[x - y] % mod; }
signed main()
{

    ios::sync_with_stdio(false);
#ifndef LOCAL
#define NDEBUG
    cin.tie(0), cout.tie(0);
#define file(a)                               \
    FILE *FI = freopen(#a ".in", "r", stdin); \
    FI = freopen(#a ".out", "w", stdout)
    file(silhouette);
#else
#ifdef LEN
    fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
#endif
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    // #include "../local.h"
#endif

    cin >> n;
    init();
    for (int i = 1; i <= n; i++)
        cin >> fro[i];
    sort(fro + 1, fro + n + 1);
    reverse(fro + 1, fro + n + 1);
    for (int i = 1; i <= n; i++)
        cin >> nex[i];
    sort(nex + 1, nex + n + 1);
    reverse(nex + 1, nex + n + 1);
    while (pos1 <= n || pos2 <= n)
    {
        int tot = 0, temp = max(fro[pos1], nex[pos2]);
        int cnt1, cnt2, pre1 = pos1, pre2 = pos2;
        while (pos1 <= n && fro[pos1] == temp)
            pos1++;
        cnt1 = pos1 - pre1;
        while (pos2 <= n && nex[pos2] == temp)
            pos2++;
        cnt2 = pos2 - pre2;
        for (int i = 0, base = 1; i <= cnt1; i++, base *= -1)
            tot = (tot + base * C(cnt1, i) * qpow(qpow(temp, i) * (qpow(temp + 1, pos1 - i - 1) - qpow(temp, pos1 - i - 1) + mod), cnt2) % mod * qpow(qpow(temp, i) * qpow(temp + 1, cnt1 - i), pos2 - cnt2 - 1) % mod + mod) % mod;
        ans = ans * tot % mod;
    }
    cout << ans;
    return 0;
}