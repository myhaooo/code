#include <bits/stdc++.h>
using namespace std;
const int N = 2000005;
const long long mod = 998244353;
int n, k, len, sum[N];
long long ans1, ans2, p[N], pw[N], jc[N], ny[N];
char s[N];
long long mi(long long t, long long v)
{
    if (!v)
        return 1;
    long long re = mi(t, v / 2);
    re = re * re % mod;
    if (v & 1)
        re = re * t % mod;
    return re;
}
void init()
{
    jc[0] = 1;
    pw[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        jc[i] = jc[i - 1] * i % mod;
        pw[i] = pw[i - 1] * 2 % mod;
    }
    ny[N] = mi(jc[N], mod - 2);
    for (int i = N - 1; i >= 0; i--)
        ny[i] = ny[i + 1] * (i + 1) % mod;
}
long long C(int x, int y) { return jc[x] * ny[y] % mod * ny[x - y] % mod; }
long long hsh(int l, int r) { return (p[r] - p[l - 1] * pw[r - l + 1] % mod + mod) % mod; }
int gt(int i, int j)
{
    int l = 1, r = len, mid;
    while (l <= r)
    {
        mid = l + r >> 1;
        if (hsh(i, i + mid - 1) == hsh(j, j + mid - 1))
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l - 1;
}
int main()
{
    freopen("divide.in", "r", stdin);
    freopen("divide.out","w",stdout);
    init();
    scanf("%d%d", &n, &k);
    len = n - k + 1;
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + s[i] - '0';
        p[i] = (p[i - 1] * 2 + s[i] - '0') % mod;
    }
    if (!sum[n])
    {
        for (int i = k; i <= n; i++)
        {
            ans2 = (ans2 + C(n - 1, i - 1)) % mod;
        }
        printf("0 %lld", ans2);
        return 0;
    }
    if (k == n)
    {
        printf("%lld 1", sum[n]);
        return 0;
    }
    if (sum[n - len + 1] == 0)
    {
        int fst = 1;
        while (s[fst] != '1')
            ++fst;
        ans1 = hsh(fst, n);
        for (int i = k; i <= fst; i++)
        {
            ans2 = (ans2 + C(fst - 1, i - 1)) % mod;
        }
        printf("%lld %lld", ans1, ans2);
        return 0;
    }
    int l = 1;
    ans2 = 1;
    for (int i = 2; i + len - 1 <= n; i++)
    {
        int vt = gt(l, i);
        if (vt == len)
            ++ans2;
        else if (s[l + vt] < s[i + vt])
        {
            l = i;
            ans2 = 1;
        }
    }
    if (s[l + len - 1] == '1')
    {
        int hs = (hsh(l, l + len - 1) - 1) % mod;
        for (int i = 1; i + len - 1 <= n; i++)
        {
            if (hs == hsh(i, i + len - 1))
                ++ans2;
        }
    }
    ans1 = hsh(l, l + len - 1) + sum[l - 1] + sum[n] - sum[l + len - 1];
    printf("%lld %lld", ans1, ans2);
    return 0;
}
