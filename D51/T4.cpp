#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
const int mod = 998244353;
int n, m;
int a[N], kmp[N];
int ans;
int qpow(int x, int y)
{
    int res = 1;
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
    freopen("x.in", "r", stdin), freopen("x.out", "w", stdout);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> m >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        int j = 0;
        for (int i = 2; i <= n; i++)
        {
            while (j && a[j + 1] != a[i])
                j = kmp[j];
            if (a[j + 1] == a[i])
                j++;
            kmp[i] = j;
        }
        ans = 0;
        int now = n;
        while (now)
            ans = (ans + qpow(m, now)) % mod, now = kmp[now];
        cout<<ans<<endl;
    }
    return 0;
}
