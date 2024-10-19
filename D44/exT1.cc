
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 6e5 + 8;

struct edge
{
    int from, to;
    ll wt;
};

vector<edge> vec;

int n, m;
pair<int, int> p[maxn];

bool cmp1(pair<int, int> x, pair<int, int> y) { return x.first < y.first; }

bool cmp2(pair<int, int> x, pair<int, int> y) { return x.second < y.second; }

bool cmp(edge x, edge y) { return x.wt < y.wt; }

int fa[maxn];
int rk[maxn];
void init(int n)
{
    for (int i = 1; i <= n; i++)
    {
        fa[i] = i;
        rk[i] = 1;
    }
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)
    {
        return 0;
    }
    if (rk[fx] < rk[fy])
        swap(fx, fy);
    fa[fy] = fx;
    rk[fx] += rk[fy];
    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
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

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i].first;
        p[i].second = i;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sqrt(n); j++)
        {
            if ((i - j) > 0 &&
                (ll)abs(p[i].first - p[i - j].first) * abs(p[i].second - p[i - j].second) <= n)
            {
                vec.push_back({p[i].second, p[i - j].second,
                               (ll)abs(p[i].first - p[i - j].first) * abs(p[i].second - p[i - j].second)});
            }
        }
    }
    sort(p + 1, p + n + 1, cmp1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sqrt(n); j++)
        {
            if ((i - j) > 0 &&
                (ll)abs(p[i].first - p[i - j].first) * abs(p[i].second - p[i - j].second) <= n)
            {
                vec.push_back({p[i].second, p[i - j].second,
                               (ll)abs(p[i].first - p[i - j].first) * abs(p[i].second - p[i - j].second)});
            }
        }
    }
    sort(vec.begin(), vec.end(), cmp);
    init(n);
    ll ans = 0;
    for (auto i : vec)
    {
        int u = i.from, v = i.to;
        ll wt = i.wt;
        if (merge(u, v))
        {
            ans += wt;
        }
    }
    cout << ans << endl;
}
