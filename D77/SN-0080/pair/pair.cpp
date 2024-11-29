#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, K = 25;
struct node {
    int id, x[K];
} a[16010];
int n, k, dfn[N], low[N], col[N], num, st[N], top, color;
vector<int> e[N];
inline void add(int x, int y) { e[x].push_back(y); }
inline int inv(int x) { return x <= n ? x + n : x - n; }
void tarjan(int x) {
    dfn[x] = low[x] = ++num, st[++top] = x;
    for (int y : e[x]) {
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if (!col[y])
            low[x] = min(low[x], dfn[y]);
    }
    if (low[x] == dfn[x]) {
        int u;
        color++;
        do {
            u = st[top--];
            col[u] = color;
        } while (x != u);
    }
}
int id;
bool check(int t) {
    for (int i = 1; i <= id; i++) e[i].clear(), dfn[i] = col[i] = 0;
    num = top = color = 0;
    id = 2 * n;
    for (int i = 1; i <= k; i++) {
        sort(a + 1, a + n * 2 + 1, [&](node a, node b) { return a.x[i] < b.x[i]; });
        int pre = ++id;
        for (int r = 1, l = 1; r <= 2 * n; r++) {
            while (a[r].x[i] - a[l].x[i] > t) add(++id, pre), add(pre = id, inv(a[l++].id));
            if (l != 1)
                add(a[r].id, pre);
        }
        int suf = ++id;
        for (int l = 2 * n, r = 2 * n; l; l--) {
            while (a[r].x[i] - a[l].x[i] > t) add(++id, suf), add(suf = id, inv(a[r--].id));
            if (r != n * 2)
                add(a[l].id, suf);
        }
    }
    for (int i = 1; i <= n * 2; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
        if (col[i] == col[i + n])
            return 0;
    return 1;
}
signed main() {
    freopen("pair.in", "r", stdin);
    freopen("pair.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j : { 0, 1 })
            for (int l = 1; l <= k; l++) cin >> a[i + j * n].x[l];
        a[i].id = i, a[i + n].id = i + n;
    }
    long long l = 0, r = 1e9, ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    cout << ans << "\n";
    return 0;
}

