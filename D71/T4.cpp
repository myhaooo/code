#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, k, a[N], b[11];
string s;
struct node {
    int a[11][11], tag, l, r;
    node() {
        memset(a, 0, sizeof(a));
        tag = 0;
    }
    void init() {
        memset(a, 0, sizeof(a));
        tag = l = r = 0;
    }
} t[N << 2];
inline node add(node a, node b) {
    static node c;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) c.a[i][j] = a.a[i][j] + b.a[i][j];
    c.a[a.r][b.l]++;
    c.l = a.l, c.r = b.r;
    return c;
}
#define mid ((l + r) >> 1)
#define ls u << 1
#define rs u << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
inline void pushup(int u, int l, int r) {
    int w = t[u].tag;
    t[u] = add(t[ls], t[rs]);
    t[u].tag = w;
}
inline void work(int u, int l, int r, int c) {
    static node b;
    b.init();
    b.tag = (t[u].tag + c) % k;
    b.l = (t[u].l + c) % k, b.r = (t[u].r + c) % k;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) b.a[(i + c) % k][(j + c) % k] = t[u].a[i][j];
    t[u] = b;
}
void pushdown(int u, int l, int r) {
    if (!t[u].tag)
        return;
    work(lson, t[u].tag);
    work(rson, t[u].tag);
    t[u].tag = 0;
}
void build(int u, int l, int r) {
    if (l == r) {
        memset(t[u].a, 0, sizeof(t[u].a));
        t[u].l = t[u].r = a[l];
        return;
    }
    build(lson);
    build(rson);
    pushup(u, l, r);
}
void upd(int u, int l, int r, int x, int y, int c) {
    if (x <= l && r <= y) {
        work(u, l, r, c);
        return;
    }
    pushdown(u, l, r);
    if (x <= mid)
        upd(lson, x, y, c);
    if (y > mid)
        upd(rson, x, y, c);
    pushup(u, l, r);
}
node query(int u, int l, int r, int x, int y) {
    if (x <= l && r <= y)
        return t[u];
    pushdown(u, l, r);
    if (y <= mid)
        return query(lson, x, y);
    if (x > mid)
        return query(rson, x, y);
    node res = add(query(lson, x, y), query(rson, x, y));
    return res;
}
void print(node x) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) cerr << x.a[i][j] << " ";
        cerr << "\n";
    }
    cerr << "\n";
}
signed main() {
    freopen("d.in", "r", stdin);
    freopen("d.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> k;
    cin >> s;
    for (int i = 0; i < n; i++) a[i + 1] = s[i] - 'a';
    build(1, 1, n);
    while (m--) {
        int op, l, r, c;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> c;
            upd(1, 1, n, l, r, c);
        } else {
            string t;
            cin >> t;
            if (l == r) {
                cout << "1\n";
                continue;
            }
            node res = query(1, 1, n, l, r);
            // print(res);
            int ans = 1;
            for (int i = 0; i < k; i++)
                for (int j = 0; j <= i; j++) ans += res.a[t[i] - 'a'][t[j] - 'a'];
            cout << ans << "\n";
        }
        // print(t[1]);
    }
    return 0;
}

