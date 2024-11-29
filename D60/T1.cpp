#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 6e5 + 107;
int n, a[N], pre[N], nxt[N];

int read() {
    int f = 1, s = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = (s << 1) + (s << 3) + (ch ^ 48);
        ch = getchar();
    }
    return f * s;
}

struct lmy {
    int x, y, w;
} e[N << 3];
int cnt;
bool comp(lmy a, lmy b) { return a.w < b.w; }

int fa[N], ans;
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void kruskal() {
    sort(e + 1, e + 1 + cnt, comp);
    int k = n - 1, s = 0;
    while (k) {
        int fx = find(e[s].x), fy = find(e[s].y);
        if (fx != fy) {
            fa[fx] = fy;
            ans += e[s].w;
            k--;
        }
        s++;
    }
}

signed main() {
    freopen("star.in", "r", stdin);
    freopen("star.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = 1; i <= n; i++) fa[i] = i;
    int tmp = 0, maxx = -1e9, minx = 1e9;
    for (int i = 1; i <= n; i++) {
        pre[i] = tmp;
        if (maxx < a[i])
            tmp = i, maxx = a[i];
    }
    tmp = n + 1;
    for (int i = n; i >= 1; i--) {
        nxt[i] = tmp;
        if (minx > a[i])
            tmp = i, minx = a[i];
    }
    for (int i = 1; i <= n; i++) {
        if (pre[i] != 0)
            e[++cnt] = { i, pre[i], a[i] - a[pre[i]] };
        if (nxt[i] != n + 1)
            e[++cnt] = { i, nxt[i], a[nxt[i]] - a[i] };
        if (pre[i] != 0 && nxt[i] != n + 1) {
            e[++cnt] = { pre[i], nxt[i], a[nxt[i]] - a[pre[i]] };
        }
    }
    kruskal();
    printf("%lld\n", ans);
}
