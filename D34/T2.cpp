#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f
int a;
const int mod = 1e9 + 7;
int b, c, d;
map<int, int> kk, bb;
int K(int x)
{
    if (x == 1)
    {
        return 1;
    }
    if (kk[x])
    {
        return kk[x];
    }
    kk[x] = ((K(x >> 1) << 1) + (K(((x + 1) >> 1)) << 1) + 1) % mod;
    return kk[x];
}
int B(int x)
{
    if (x == 1)
    {
        return 0;
    }
    if (bb[x])
    {
        return bb[x];
    }
    bb[x] = (B(x >> 1) + B((x + 1) >> 1) + K(x >> 1)) % mod;
    return bb[x];
}
int got(int x, int y)
{
    return (K(x) * y + B(x)) % mod;
}
int found(int x, int lt, int rt, int left, int right)
{
    if (lt <= left && right <= rt)
    {
        return got(right - left + 1, x);
    }
    register int me = (left + right) >> 1, rn = 0;
    if (lt <= me)
    {
        rn += found((x << 1) % mod, lt, rt, left, me);
        rn %= mod;
    }
    if (rt > me)
    {
        rn += found((x << 1 | 1) % mod, lt, rt, me + 1, right);
        rn %= mod;
    }
    return rn;
}
main()
{
    cin >> a;
    while (a--)
    {
        cin >> b >> c >> d;
        cout << found(1, c, d, 1, b) << "\n";
    }
    return 0;
}
