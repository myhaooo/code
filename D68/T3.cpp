#pragma GCC optimize(3)

#include <bits/stdc++.h>
using namespace std;

#define ll long long
constexpr int B = 1 << 25;
char buf[B], *p1 = buf, *p2 = buf;
#define gt() (p1==p2 && (p2=(p1=buf)+fread(buf, 1, B, stdin), p1==p2) ? EOF : *p1++)
template <typename T> inline void read(T &x){
	x = 0; int f = 0; char ch = gt();
	for(; !isdigit(ch); ch = gt()) f ^= ch == '-';
	for(; isdigit(ch); ch = gt()) x = (x<<1) + (x<<3) + (ch^48);
	x = f ? -x : x;
}
template <typename T, typename ...TT> inline void rd(T &x, TT &...y){ rd(x), rd(y...); }
const int N = 1e6 + 7;
const int M = 3e7 + 8;

int T, cnt[N], ch[M][2], sz[M], idx;
ll a[N], lsh[N];


inline void insert(ll x)
{
    register int p = 0;
    sz[p]++;
    for (register int i = 0; i <= 60; i++)
    {
        if (!ch[p][x & 1])
            ch[p][x & 1] = ++idx;
        p = ch[p][x & 1], x >>= 1, sz[p]++;
    }
    return;
}

inline ll query(ll x)
{
    register ll res = 0;
    register int p = 0, op = 1;
    res += op * sz[p], op *= -1;
    for (register int i = 0; i <= 60; i++)
    {
        p = ch[p][x & 1], res += op * sz[p];
        op *= -1, x >>= 1;
    }
    return res;
}


#define int register int
signed main()
{ll ans,n,m;
        freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    cin>>T;
    while (T--)
       {read(n), ans = (1ll * n * (n - 1) * (n - 2) / 6 );
    for (int i = 0; i <= idx; i++)
        ch[i][0] = ch[i][1] = sz[i] = 0;
    idx = 0;
    for (int i = 1; i <= n; i++)
        read(a[i]), lsh[i] = a[i], insert(a[i]), cnt[i] = 0;
    sort(lsh + 1, lsh + n + 1), m = unique(lsh + 1, lsh + n + 1) - lsh - 1;
    for (int i = 1; i <= n; i++)
        cnt[a[i] = lower_bound(lsh + 1, lsh + m + 1, a[i]) - lsh]++;
    for (int i = 1; i <= n; i++)
        if (cnt[a[i]])
            ans -= 1ll * cnt[a[i]] * (cnt[a[i]] - 1) / 2 * query(lsh[a[i]]) + (1ll * cnt[a[i]] * (cnt[a[i]] - 1) * (cnt[a[i]] - 2) / 6 ), cnt[a[i]] = 0;
    printf("%lld\n", ans);}
    return 0;
}
