#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

set<int> pos[N];
multiset<int> val[N];
int a[N], b[N];

struct SGT {
    int t[N * 4];
    void pushup(int p) { t[p] = max(t[p * 2], t[p * 2 + 1]); }
    void build(int p, int l, int r) {
        if (l == r)
            return t[p] = b[l], void();
        int m = (l + r) / 2;
        build(p * 2, l, m);
        build(p * 2 + 1, m + 1, r);
        pushup(p);
    }
    void modify(int p, int l, int r, int x, int v) {
        if (l == r)
            return t[p] = v, void();
        int m = (l + r) / 2;
        x <= m ? modify(p * 2, l, m, x, v) : modify(p * 2 + 1, m + 1, r, x, v);
        pushup(p);
    }
    int query(int p, int l, int r, int x) {
        if (l == r)
            return l;
        int m = (l + r) / 2;
        if (t[p * 2] > x)
            return query(p * 2, l, m, x);
        return query(p * 2 + 1, m + 1, r, x);
    }
} sgt;

void del(int x) {
    auto it = pos[a[x]].find(x);
    val[a[x]].erase(val[a[x]].find(x - *prev(it)));
    val[a[x]].erase(val[a[x]].find(*next(it) - x));
    val[a[x]].insert(*next(it) - *prev(it));
    pos[a[x]].erase(it);
}

void ins(int x) {
    auto it = pos[a[x]].insert(x).first;
    val[a[x]].erase(val[a[x]].find(*next(it) - *prev(it)));
    val[a[x]].insert(x - *prev(it));
    val[a[x]].insert(*next(it) - x);
}

int main() {
    freopen("star.in", "r", stdin);
    freopen("star.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) pos[i].insert(0);
    for (int i = 1; i <= n; i++) cin >> a[i], pos[a[i]].insert(i);
    for (int i = 0; i <= n; i++) pos[i].insert(n + 1);
    for (int i = 0; i <= n; i++) {
        auto it = next(pos[i].begin());
        while (it != pos[i].end()) {
            val[i].insert(*it - *prev(it));
            it++;
        }
        b[i] = *prev(val[i].end());
    }
    sgt.build(1, 0, n);
    while (m--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) {
            if (a[x] == a[x + 1])
                continue;
            del(x), del(x + 1);
            swap(a[x], a[x + 1]);
            ins(x), ins(x + 1);
            sgt.modify(1, 0, n, a[x], *prev(val[a[x]].end()));
            sgt.modify(1, 0, n, a[x + 1], *prev(val[a[x + 1]].end()));
        } else
            cout << sgt.query(1, 0, n, x) << '\n';
    }
    return 0;
}
