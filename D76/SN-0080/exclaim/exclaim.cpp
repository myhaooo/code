#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define lowbit(x) x&-x
#define ll long long
int T, n, mod;
ll ans, now, t[N];
void update(int x, int v)
{
    for (int i = x; i <= mod; i += lowbit(i))
        t[i] += v;
}
ll getsum(int x)
{
    ll ans = 0;
    for (int i = x; i; i -= lowbit(i))
        ans += t[i];
    return ans;
}
int main()
{
    freopen("exclaim.in", "r", stdin);
    freopen("exclaim.out", "w", stdout);
    cin>>T;
    for (int cas = 1; cas <= T; cas++)
    {
        cin>>n>>mod;
        ans = now = 0;
        memset(t, 0, sizeof(t));
        for (int i = 1; i <= n; i++)
        {
            int l =(1ll * i * i + 1)% mod + 1, r =(1ll * i * i + i)% mod + 1;
            if (l <= r)
                update(l, 1), update(r + 1, -1);
            else
                update(1, 1), update(r + 1, -1), update(l, 1);
            int c = 1ll * i * i % mod * i % mod;
            now +=(i - 1)/ mod;
            ans += getsum(c + 1) + now;
        }
        printf("Case %d: ", cas);
        cout << ans;
        putchar(10);
    }
}
