#include <bits/stdc++.h>
using namespace std;
#define read(x) cin >> x
#define int long long
const int inf = 1e18;
const int maxn = 2e5 + 5;
const int LEN = (1 << 20);
struct node
{
    int l, r;
    bool operator<(const node q) const { return r < q.r; }
};
node t;
node p[maxn];
int a[maxn], Bit[maxn];
priority_queue<node> q;
int T, n, m, k, u, l, r, mid, ans, la, cnt;
inline bool cmp(node x, node y) { return x.l < y.l; }
inline int lowbit(int x) { return x & -x; }
inline void Add(int x, int k)
{
    for (int i = x; i <= n; i += lowbit(i))
        Bit[i] += k;
    return;
}
inline int Query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += Bit[i];
    return res;
}

inline bool check(int x)
{
    while (!q.empty())
        q.pop();
    memset(Bit, 0, sizeof(Bit));
    la = 1;
    cnt = 0;
    for (int i = 1; i <= n; ++i)
        Add(i, a[i] - a[i - 1]);
    for (int i = 1; i <= n; ++i)
    {
        while (la <= m && p[la].l <= i)
            q.push(p[la++]);
        while (Query(i) < x && q.size())
        {
            do
            {
                t = q.top();
                q.pop();
            } while (t.r < i && q.size());
            if (t.r < i || ++cnt > k)
                return 0;
            Add(t.l, u);
            Add(t.r + 1, -u);
        }
        if (Query(i) < x)
            return 0;
    }
    return 1;
}

signed main()
{
    cin >> T;
    while (T--)
    {
        cin>>n>>m>>k>>u;
        l = inf;
        r = 0;
        for (int i = 1; i <= n; ++i)
            read(a[i]), l = min(l, a[i]), r = max(r, a[i]);
        for (int i = 1; i <= m; ++i)
            read(p[i].l), read(p[i].r);
        sort(p + 1, p + m + 1, cmp);
        r += k * u;
        ans = r;
        while (l <= r)
        {
            mid = l + r >> 1;
            if (check(mid))
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
