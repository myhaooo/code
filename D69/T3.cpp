#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, id, a[N];
struct BIT
{
    int t[N];
    void init() { memset(t, 0, sizeof(t)); }
    inline int lowbit(int x) { return x & (-x); }
    inline void add(int x, int v)
    {
        for (; x <= n; x += lowbit(x))
            t[x] += v;
    }
    inline int sum(int x)
    {
        int s = 0;
        for (; x; x -= lowbit(x))
            s += t[x];
        return s;
    }
    inline int query(int l, int r) { return l > r ? 0 : sum(r) - sum(l - 1); }
} T;
int q[N];
int lmi[N], lmx[N];
int rmi[N], rmx[N];
vector<pair<int, int>> v[N];
void init()
{
    T.init();
    for (int i = 1; i <= n; i++)
        v[i].clear();
    for (int i = 1; i <= n; i++)
        lmi[i] = lmx[i] = 0, rmi[i] = rmx[i] = n + 1;
    for (int i = n, top = 0; i >= 1; i--)
    {
        while (top && a[q[top]] > a[i])
            lmi[q[top--]] = i;
        q[++top] = i;
    }
    for (int i = n, top = 0; i >= 1; i--)
    {
        while (top && a[q[top]] < a[i])
            lmx[q[top--]] = i;
        q[++top] = i;
    }
    for (int i = 1, top = 0; i <= n; i++)
    {
        while (top && a[q[top]] > a[i])
            rmi[q[top--]] = i;
        q[++top] = i;
    }
    for (int i = 1, top = 0; i <= n; i++)
    {
        while (top && a[q[top]] < a[i])
            rmx[q[top--]] = i;
        q[++top] = i;
    }
}
int ans[N];
void solve()
{
    init();
    for (int i = 1; i <= n; i++)
    {
        int j = min(lmi[i], lmx[i]);
        if (!j)
            continue;
        v[1].push_back({i, 1});
        v[j].push_back({i, -1});
    }
    for (int i = 1; i <= n; i++)
    {
        for (auto [x, y] : v[i])
            T.add(x, y);
        int j = max(rmi[i], rmx[i]);
        ans[i] = T.query(j, n);
    }
}

int main()
{
    freopen("interval.in", "r", stdin);
    freopen("interval.out", "w", stdout);
    scanf("%d%d", &n, &id);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    solve();
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    putchar(10);
    reverse(a + 1, a + n + 1), solve();
    reverse(ans + 1, ans + n + 1);
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    putchar(10);
    return 0;
}