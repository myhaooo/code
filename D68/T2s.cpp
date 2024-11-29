#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e3 + 7;
const int mod = 1e9 + 7;
int T, n, m, lsum[MAXN], csum[MAXN], minj[MAXN], maxj[MAXN], mink[MAXN], maxk[MAXN], f[MAXN][MAXN];
int t[MAXN], lj, rk[MAXN], lk[MAXN];
int dif(int x, int y) { return ((x - y) % mod + mod) % mod; }
void del(int j, int k)
{
    lsum[j] = dif(lsum[j], f[j][k]);
    csum[k] = dif(csum[k], f[j][k]);
    f[j][k] = 0;
}
void clear(int i)
{
    for (int j = lj; j <= i - 1; j++)
    {
        if (j < minj[i] || j > maxj[i])
        {
            for (int k = 0; k <= n; k++)
                del(j, k);
            lk[j] = n;
            rk[j] = 0;
        }
        else
        {
            for (int k = lk[j]; k < mink[i]; k++)
                del(j, k);
            for (int k = rk[j]; k > maxk[i]; k--)
                del(j, k);
            lk[j] = max(lk[j], mink[i]);
            rk[j] = min(rk[j], maxk[i]);
        }
    }
    lj = max(lj, minj[i]);
}
int main()
{
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    cin >> T;
    while (T--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n; i++)
        { 
            for (int j = 0; j <= n; j++)
                f[i][j] = 0;
            lsum[i] = csum[i] = 0;
            minj[i] = mink[i] = 0;
            maxj[i] = maxk[i] = n;
            lk[i] = 0;
            rk[i] = n;
        }
        int l, r, x;
        for (int i = 1; i <= m; i++)
        { 
            scanf("%d%d%d", &l, &r, &x);
            if (x == 1)
                maxj[r] = min(maxj[r], l - 1);
            else if (x == 2)
            {
                minj[r] = max(minj[r], l);
                maxk[r] = min(maxk[r], l - 1);
            }
            else
            {
                minj[r] = max(minj[r], l + 1);
                mink[r] = max(mink[r], l);
            }
        }
        lj = 0;
        f[0][0] = 1;
        lsum[0] = csum[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int k = 0; k < i; k++)
                t[k] = (lsum[k] + csum[k]) % mod;
            if (minj[i] <= i - 1 && maxj[i] >= i - 1)
            {
                for (int k = mink[i]; k <= min(maxk[i], max(0, i - 2)); k++)
                {
                    f[i - 1][k] = (f[i - 1][k] + t[k]) % mod;
                    csum[k] = (csum[k] + t[k]) % mod;
                    lsum[i - 1] = (lsum[i - 1] + t[k]) % mod;
                }
            }
            clear(i); 
        }
        int ans = 0;
        for (int i = 0; i <= n; i++)
            ans = (ans + lsum[i]) % mod;
        printf("%d\n", ans);
    }
    return 0;
}