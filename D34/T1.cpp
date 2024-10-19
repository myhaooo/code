#include <bits/stdc++.h>
using namespace std;
#define int long long 
#define inf 0x3f3f3f3f
bool be;
const int N = 5e5 + 5;
int a, b[300003], maxn, minn, num;
int l[N << 2], r[N << 2];
bool use[N];
bool ed
struct ST
{
    int num[N << 2];
#define lson x << 1
#define rson x << 1 | 1
    void up(int x)
    {
        num[x] = max(num[lson], num[rson]);
    }
    void build(int x, int lt, int rt)
    {
        l[x] = lt;
        r[x] = rt;
        if (lt == rt)
        {
            num[x] = 0;
            return;
        }
        int mid = (lt + rt) >> 1;
        build(lson, lt, mid);
        build(rson, mid + 1, rt);
        up(x);
    }
    void update(int x, int a, int b)
    {
        if (l[x] == r[x])
        {
            num[x] = b;
            return;
        }
        int mid = (l[x] + r[x]) >> 1;
        if (a <= mid)
        {
            update(lson, a, b);
        }
        else
        {
            update(rson, a, b);
        }
        up(x);
    }
    int quary(int x, int lt, int rt)
    {
        if (lt > rt)
        {
            return 0;
        }
        if (lt <= l[x] && r[x] <= rt)
        {
            return num[x];
        }
        int mid = (l[x] + r[x]) >> 1, maxn = -inf;
        if (lt <= mid)
        {
            maxn = max(maxn, quary(lson, lt, rt));
        }
        if (rt > mid)
        {
            maxn = max(maxn, quary(rson, lt, rt));
        }
        return maxn;
    }
} tree[2];
int main()

{
#define LEN
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

    cin >> a;
    maxn = -inf, minn = inf;
    for (int i = 1; i <= a; i++)
    {
        cin >> b[i];
        maxn = max(maxn, b[i]);
        minn = min(minn, b[i]);
    }
    tree[0].build(1, 1, maxn);
    tree[1].build(1, 1, maxn);
    for (int i = 1; i <= a; i++)
    {
        if (use[b[i]])
        {
            cout << num << " ";
            continue;
        }
        use[b[i]] = true;
        int j = tree[0].quary(1, b[i] + 2, maxn);
        tree[0].update(1, b[i], j + 1);
        num = max(num, j + 1);
        j = tree[1].quary(1, minn, b[i] - 2);
        tree[1].update(1, b[i], j + 1);
        num = max(num, j + 1);
        cout << num << " ";
    }
    return 0;
}
