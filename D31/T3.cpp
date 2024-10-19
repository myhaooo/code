#include <bits/stdc++.h>
#define int long long
#define rg register
#define file(x)                   \
    freopen(x ".in", "r", stdin); \
    freopen(x ".out", "w", stdout);
using namespace std;
const int mod = 998244353;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9')
        f = (c == '-') ? -1 : 1, c = getchar();
    while (c >= '0' && c <= '9')
        x = x * 10 + c - 48, c = getchar();
    return f * x;
}
int n, m, tot, a[2000010], sum[2000010];
inline int check(int x, int len)
{
    int ans = 0, flag = 0;
    for (int i = 1; i <= tot; i++)
    {
        if (sum[i] > x)
            break;
        ans += sum[i], flag = i;
    }
    int k = (len - tot + flag);
    return m - (k * x - ans);
}
inline int qpow(int a, int b)
{
    int ans = 1;
    while (b)
    {
        if (b & 1)
            ans = ans * a % mod;
        a = a * a % mod, b >>= 1;
    }
    return ans;
}
int fac[20000010];
main()
{
    int T = read(), l, r;
    fac[0] = 1;
    for (int i = 1; i <= 10200000; i++)
        fac[i] = fac[i - 1] * i % mod;
    while (T--)
    {
        n = read(), m = read(), l = read(), r = read(), tot = 0;
        for (int i = 1; i <= n; i++)
            a[i] = read();
        sort(a + 1, a + 1 + n);
        int p = 0, js = 1;
        a[n + 1] = INT_MIN;
        for (int i = 1; i <= n + 1; i++)
        {
            if (a[i] != a[i + 1])
            {
                if (a[i] <= r && a[i] >= l)
                    sum[++tot] = i - p;
                else
                    js = js * fac[(i - p)] % mod;
                p = i;
            }
        }
        sort(sum + 1, sum + 1 + tot);
        int L = 0, R = m + n, maxx = 0;
        while (L <= R)
        {
            int mid = (L + R) >> 1;
            if (check(mid, (r - l + 1)) >= 0)
                L = mid + 1, maxx = max(maxx, mid);
            else
                R = mid - 1;
        }
        
        int ans = 0, flag = 0, len = (r - l + 1);
        
        for (int i = 1; i <= tot; i++)
        {
            if (sum[i] > maxx)
                break;
            ans += sum[i], flag = i;
        }
        int k = (len - tot + flag), c = m - (k * maxx - ans);
        for (int i = flag + 1; i <= tot; i++)
            js = js * fac[sum[i]] % mod;
        js = js * qpow(fac[maxx + 1], c) % mod, js = js * qpow(fac[maxx], k - c) % mod;
        printf("%lld\n", fac[n + m] * qpow(js, mod - 2) % mod);
    }

    return 0;
}