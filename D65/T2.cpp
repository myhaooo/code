#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MN = 200005;
ll T, n, m, u[MN], v[MN];
vector<ll> ans[20];
void write(ll n)
{
    if (n > 9)
        write(n / 10);
    putchar(n % 10 + '0');
}
ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll gs(ll x)
{
    ll res = 0;
    while (x)
    {
        x &= (x - 1); 
        res++;
    }
    return res;
} 
void solve()
{
    for (ll i = 0; i < ans[n].size(); i++)
    { 
        bool flag = false;
        for (ll j = 1; j <= m; j++)
            if (ans[n][i] >> (u[j] - 1) & 1 && !(ans[n][i] >> (v[j] - 1) & 1))
            {                
                flag = true; 
                break;
            }
        if (!flag)
        { 
            write(gs(ans[n][i]));
            putchar('\n');
            for (ll j = 1; j <= n; j++)
                if (ans[n][i] >> (j - 1) & 1)
                    write(j), putchar(' ');
            putchar('\n');
            return;
        }
    }
    printf("-1\n");
}
int main()
{
    for (ll i = 5; i <= 19; i++) 
        for (ll s = 1; s < (1 << i); s++)
        {               
            ll num = 0; 
            for (ll j = 1; j <= i; j++)
                if ((s >> (j - 1)) & 1) 
                    for (ll k = j; k <= i; k += j)
                        num ^= (1 << (k - 1)); 
            if (gs(num) <= i / 5)
                ans[i].push_back(s); 
        }
    T = read();
    while (T--)
    {
        n = read();
        m = read();
        for (int i = 1; i <= m; i++)
            u[i] = read(), v[i] = read();
        if (n <= 4)
        {
            printf("-1\n");
            continue;
        } 
        if (n >= 20)
        { 
            write(n);
            putchar('\n');
            for (ll i = 1; i <= n; i++)
                write(i), putchar(' '); 
            putchar('\n');
            continue;
        }
        solve();
    }
    return 0;
}