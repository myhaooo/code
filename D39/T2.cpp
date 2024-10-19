#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 5;
int n, xx, yy, fa[maxn], siz[maxn], ans = 0x3f3f3f3f, ans1 = 0, cnt, tot;
pair<int, int> edge[maxn];
int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
struct Node
{
    int x, y, id;
} p[maxn];
bool cmpx(Node a, Node b)
{
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}
bool cmpy(Node a, Node b)
{
    return a.y != b.y ? a.y < b.y : a.x < b.x;
}
int find(int x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    fa[x] = y;
    siz[y] += siz[x];
    return;
}
void add(int x, int y)
{
    if (x > y)
        swap(x, y);
    edge[++cnt] = make_pair(x, y);
    return;
}
signed main()
{
    freopen("sky.in","r",stdin);
	freopen("sky.out","w",stdout);
    n = read();
    for (int i = 1; i <= n; i++)
    {
        xx = read();
        yy = read();
        p[i].x = xx + yy;
        p[i].y = xx - yy;
        fa[i] = i;
        siz[i] = 1;
        p[i].id = i;
    }

    sort(p + 1, p + n + 1, cmpx);
    for (int i = 1; i <= n; i++)
    {
        int j = i + 1;
        while ((p[j].x == p[i].x || p[j].y == p[i].y) && j <= n)
        {
            merge(p[i].id, p[j].id);
            j++;
        }
        if (j <= n)
            ans = min(ans, p[j].x - p[i].x);
    }
    sort(p + 1, p + n + 1, cmpy);
    for (int i = 1; i <= n; i++)
    {
        int j = i + 1;
        while ((p[j].y == p[i].y || p[j].x == p[i].x) && j <= n)
        {
            merge(p[i].id, p[j].id);
            j++;
        }
        if (j <= n)
            ans = min(ans, p[j].y - p[i].y);
    }

    for (int i = 1; i <= n; i++)
    {
        int j = i + 1;
        while ((p[j].y == p[i].y || p[j].x == p[i].x) && j <= n)
        {
            j++;
        }
        if (j <= n && p[j].y - p[i].y == ans)
            add(find(p[i].id), find(p[j].id)); 
    }
    sort(p + 1, p + n + 1, cmpx);
    for (int i = 1; i <= n; i++)
    {
        int j = i + 1;
        while ((p[j].x == p[i].x || p[j].y == p[i].y) && j <= n)
        {
            j++;
        }
        if (j <= n && p[j].x - p[i].x == ans)
            add(find(p[i].id), find(p[j].id));
    }

    sort(edge + 1, edge + cnt + 1);
    tot = unique(edge + 1, edge + cnt + 1) - edge - 1;
    for (int i = 1; i <= tot; i++)
    {
        int x = edge[i].first;
        int y = edge[i].second;
        ans1 += siz[x] * siz[y];
    }
    cout << ans << endl
         << ans1;
    return 0;
}
