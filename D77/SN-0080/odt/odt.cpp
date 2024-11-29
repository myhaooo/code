#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n, m;
struct node {
    int res, len, a1, a2, b1, b2;
    void init() { res = len = a1 = a2 = b1 = b2 = 0; }
    void ins(int x) {
        len++;
        if (!a2)
            a2 = x;
        else if (!a1)
            a1 = a2, a2 = x;
        else
            res += (b1 < b2) ^ (b2 < x);
        b1 = b2, b2 = x;
    }
} t[N << 2];
#define mid ((l + r) >> 1)
#define ls u << 1
#define rs u << 1 | 1
#define lson ls, l, mid
#define rson rs, mid + 1, r
void merge(node &x, node y) {
    if (y.a1)
        x.ins(y.a1);
    x.ins(y.a2);
    if (y.len <= 2)
        return;
    x.len += y.len - 2, x.res += y.res;
    if (y.len >= 2)
        x.b1 = y.b1, x.b2 = y.b2;
    else
        x.b1 = x.b2, x.b2 = y.b2;
}
void pushdown(int u) {
    if (!t[u].len)
        return;
    merge(t[ls], t[u]);
    merge(t[rs], t[u]);
    t[u].init();
}
void upd(int u, int l, int r, int x, int y, int val) {
    if (x <= l && r <= y)
        return t[u].ins(val);
    pushdown(u);
    if (x <= mid)
        upd(lson, x, y, val);
    if (y > mid)
        upd(rson, x, y, val);
}
node query(int u, int l, int r, int x) {
    if (l == r)
        return t[u];
    pushdown(u);
    return x <= mid ? query(lson, x) : query(rson, x);
}
signed main() {
    freopen("odt.in", "r", stdin);
    freopen("odt.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    while (m--) {
        int op, l, r, x;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            upd(1, 1, n, l, r, x);
        } else {
            cin >> x;
            node res = query(1, 1, n, x);
            cout << (res.len <= 2 ? res.len : res.res + 2) << "\n";
        }
    }
}

