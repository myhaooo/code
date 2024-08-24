#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
const int M = 1e7 + 2e5 + 1;
const int mod = 998244353;
int T, n, m, L, R, a[N], c1[N], c2[N], tot;
ll fac[M + 5], inv[M + 5];
inline ll qpow(ll x, ll y)
{
    ll res = 1;
    while (y)
    {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
}
signed main()
{
    #ifndef LOCAL
    #define NDEBUG
    	cin.tie(0), cout.tie(0);
    #define file(a)                               \
    	FILE *FI = freopen(#a ".in", "r", stdin); \
    	FI = freopen(#a ".out", "w", stdout)
    	// file();
    #else
    #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
    #endif
    	freopen("in.in", "r", stdin);
    	freopen("out.out", "w", stdout);
    	// #include "../local.h"
    #endif

    fac[0] = 1;
    for (int i = 1; i <= M; i++)
        fac[i] = fac[i - 1] * i % mod;
    inv[M] = qpow(fac[M], mod - 2);
    for (int i = M; i; i--)
        inv[i - 1] = inv[i] * i % mod;



    cin >> T;
    while (T--)
    {
        cin >> n >> m >> L >> R, tot = n + m;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + 1 + n), a[n + 1] = -1;
        c2[0] = R - L + 1;
        for (int i = 1, cur = 0; i <= n + 1; i++)
            if (a[i] == a[i - 1] || i == 1)
                cur++;
            else if (L <= a[i - 1] && a[i - 1] <= R)
                c2[cur]++, c2[0]--, cur = 1;
            else
                c1[cur]++, cur = 1;
        for (int i = 0; i < n; i++)
            if (m <= c2[i])
            {
                c2[i + 1] += m, c2[i] -= m, m = 0;
                break;
            }
            else
                m -= c2[i], c2[i + 1] += c2[i], c2[i] = 0;
        ll ans = fac[tot];
        if (!m)
            for (int i = 2; i <= n; i++)
                (ans *= qpow(inv[i], c1[i] + c2[i])) %= mod;
        else
        {
            for (int i = 2; i <= n; i++)
                (ans *= qpow(inv[i], c1[i])) %= mod;
            int k = m / c2[n], d = m - k * c2[n];
            (ans *= qpow(inv[n + k], c2[n] - d) * qpow(inv[n + k + 1], d) % mod) %= mod;
        }
        cout << ans << '\n';
        for (int i = 1; i <= n + 1; i++)
            c1[i] = c2[i] = 0;
    }
    return 0;
}