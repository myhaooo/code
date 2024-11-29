#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, inf = 1073741823;
int n, q;
int a[N], p[N], Or[31], And[31];
struct Node {
    int Or, And, siz, val;
};
struct Seg {
#define lid (id<<1)
#define rid ((id<<1)|1)
    Node nod[N << 2];
    Node PushUp(Node l, Node r) {
        return {
                l.Or | r.Or, 
                l.And & r.And, 
                l.siz + r.siz, 
                (l.val == -1 || r.val == -1) ? max(l.val, r.val) : (l.val ^ r.val) ? inf + 1 : l.val 
        };
    }
    void Build(int id, int l, int r, int typ) {
        if (l == r) {
            if (p[l] == typ)
                nod[id] = { a[l], a[l], 1, a[l] };
            else
                nod[id] = { 0, inf, 0, -1 };
            return;
        }
        int mid = (l + r) >> 1;
        Build(lid, l, mid, typ);
        Build(rid, mid + 1, r, typ);
        nod[id] = PushUp(nod[lid], nod[rid]);
        return;
    }
    Node Query(int id, int l, int r, int p, int q) {
        if (p <= l && r <= q)
            return nod[id];
        int mid = (l + r) >> 1;
        if (q <= mid)
            return Query(lid, l, mid, p, q);
        else if (p > mid)
            return Query(rid, mid + 1, r, p, q);
        else
            return PushUp(Query(lid, l, mid, p, q), Query(rid, mid + 1, r, p, q));
    }
} t[31];

bool Check(int l, int r) {
    int cntor = 0, cntand = r - l + 1;
    for (int i = 0; i <= 30; i++) {
        Or[i] = t[i].Query(1, 1, n, l, r).Or;
        And[i] = t[i].Query(1, 1, n, l, r).And;
    }
    for (int i = 1; i <= 30; i++) Or[i] |= Or[i - 1];
    for (int i = 29; i >= 0; i--) And[i] &= And[i + 1];
    for (int i = 0; i <= 30; i++) {
        Node ifm = t[i].Query(1, 1, n, l, r);
        cntand -= ifm.siz;
        if (ifm.val != inf + 1) {
            int cnt = ifm.siz, valor = (i == 0) ? 0 : Or[i - 1], valand = (i == 30) ? inf : And[i + 1],
                val = ifm.val;
            if (cnt == 0 && (valor == valand && cntor && cntand))
                return true;
            if (cnt == 1 && (((valor | val) == valand && cntand) || (valor == (valand & val) && cntor)))
                return true;
            if (cnt >= 2 && ((valor | val) == (valand & val)))
                return true;
        }
        cntor += ifm.siz;
    }
    return false;
}

int main() {
    freopen("peace.in", "r", stdin);
    freopen("peace.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) p[i] = __builtin_popcount(a[i]);
    for (int i = 0; i <= 30; i++) t[i].Build(1, 1, n, i);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (Check(l, r) ? "YES\n" : "NO\n");
    }
    return 0;
}
