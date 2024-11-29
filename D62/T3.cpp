#include <bits/stdc++.h>
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define lb(x) (x & -x)
#define id(x, y) ((x - 1) * m + y)
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, ll>;
inline int read() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x;
}
const int N = 5e5 + 5;
int n, m, a[N], p[N], L[N], ans[N];
vector<pii> q[N];
struct tree {
    int t[N << 2];
    void push_up(int x) { t[x] = t[lc(x)] + t[rc(x)]; }
    void build(int x, int l, int r) {
        t[x] = 0;
        if (l == r)
            return;
        int mid = l + r >> 1;
        build(lc(x), l, mid), build(rc(x), mid + 1, r);
    }
    void upd(int x, int l, int r, int p) {
        t[x]++;
        if (l == r)
            return;
        int mid = l + r >> 1;
        p <= mid ? upd(lc(x), l, mid, p) : upd(rc(x), mid + 1, r, p), push_up(x);
    }
    int ask(int x, int l, int r, int u, int v) {
        if (l > v || r < u)
            return 0;
        if (u <= l && r <= v)
            return t[x];
        int mid = l + r >> 1;
        return ask(lc(x), l, mid, u, v) + ask(rc(x), mid + 1, r, u, v);
    }
    int query(int x, int l, int r, int p, int k) {
        if (r <= p || k < 0)
            return 0;
        if (l == r)
            return t[x] <= k && !t[x];
        int mid = l + r >> 1;
        if (l <= p) {
            if (mid <= p)
                return query(rc(x), mid + 1, r, p, k);
            int y = query(lc(x), l, mid, p, k);
            return y + query(rc(x), mid + 1, r, p, k - (mid - p - y));
        }
        if (t[x] <= k)
            return r - l + 1 - t[x];
        return t[lc(x)] <= k ? mid - l + 1 - t[lc(x)] + query(rc(x), mid + 1, r, p, k - t[lc(x)])
                             : query(lc(x), l, mid, p, k);
    }
} t;
int main() {
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    n = read(), t.build(1, 1, n);
    for (int i = 1; i <= n; i++)
        a[i] = read(), p[a[i]] = i, L[i] = t.ask(1, 1, n, a[i], n), t.upd(1, 1, n, a[i]);
    m = read(), t.build(1, 1, n);
    int k, x;
    for (int i = 1; i <= m; i++) {
        k = read(), x = read();
        ans[i] = p[x] - min(k, L[p[x]]);
        q[x].push_back({ k - L[p[x]] - 1, i });
    }
    for (int i = n; i; i--) {
        for (pii x : q[i]) ans[x.second] += t.query(1, 1, n, p[i], x.first);
        t.upd(1, 1, n, p[i]);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}

