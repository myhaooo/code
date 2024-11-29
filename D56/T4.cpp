// ubsan: undefined
// accoders
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define Mem(A, B) fill(A + 1, A + B + 1, 0)
#define lowbit(x) (x & (-x))
#pragma GCC optimize(2)
#pragma GCC optimize(3)
const int maxn = 1e5 + 10;
const int inf = 1e18;
int t, n, a[maxn], head[maxn], to[maxn << 1], nxt[maxn << 1], ver[maxn << 1], tot, x, y, z, f[maxn];
int siz[maxn], dfn[maxn], DFN, st[maxn], ed[maxn], w[maxn], M, T, id[maxn];
inline void graph_cls() {
    Mem(head, n);
    Mem(to, tot);
    Mem(nxt, tot);
    tot = DFN = M = 0;
}
inline void add(int x, int y, int z) {
    to[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
    ver[tot] = z;
}
inline void dfs1(int x, int fa, int up) {
    siz[x] = a[x];
    dfn[x] = ++DFN;
    st[x] = DFN;
    w[x] = up;
    M += a[x];
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa)
            continue;
        dfs1(y, x, ver[i]);
        siz[x] += siz[y];
    }
    ed[x] = DFN;
}
struct BIT {
    int c[maxn];
    inline void cls() { Mem(c, n); }
    inline void add(int x, int w) {
        for (int i = x; i <= n; i += lowbit(i)) c[i] += w;
    }
    inline int query(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res += c[i];
        return res;
    }
    inline int qq(int l, int r) {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
} T1, T2;  // T1:w*siz,T2:w
struct Q {
    int l, r, id, typ, lim, X;
} q[maxn << 2];
struct node {
    int ls, rs, sum;
};
struct SGT {
    node t[maxn * 40];
    int rt, tot_dot;
    inline void update(int x) { t[x].sum = t[t[x].ls].sum + t[t[x].rs].sum; }
    inline void cls() {
        rt = 0;
        for (int i = 0; i <= tot_dot; i++) t[i].ls = t[i].rs = t[i].sum = 0;
        tot_dot = 0;
    }
    inline void modify(int &x, int l, int r, int pos, int w) {
        if (!x)
            x = ++tot_dot;
        if (l == r) {
            t[x].sum += w;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            modify(t[x].ls, l, mid, pos, w);
        else
            modify(t[x].rs, mid + 1, r, pos, w);
        update(x);
    }
    inline int qq(int x, int l, int r, int ql, int qr) {
        if (!x || ql > qr)
            return 0;
        if (ql <= l && r <= qr)
            return t[x].sum;
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid)
            res += qq(t[x].ls, l, mid, ql, qr);
        if (mid < qr)
            res += qq(t[x].rs, mid + 1, r, ql, qr);
        return res;
    }
} TT1, TT2;
inline void dfs2(int x, int fa) {
    int X = (M - siz[x]), k = siz[x];
    int del = TT2.qq(TT2.rt, 1, M, 1, X / 2) * k;
    int add = TT2.qq(TT2.rt, 1, M, X / 2 + siz[x] + 1, M) * k;
    // printf("padd %lld\n",add);
    add = (add + TT1.qq(TT1.rt, 1, M, X / 2 + 1, X / 2 + siz[x]) * 2 -
           (k + X) * TT2.qq(TT2.rt, 1, M, X / 2 + 1, X / 2 + siz[x]));
    // printf("x %lld,add %lld,del %lld\n",x,add,del);
    f[x] += (add - del);
    TT1.modify(TT1.rt, 1, M, siz[x], siz[x] * w[x]);
    TT2.modify(TT2.rt, 1, M, siz[x], w[x]);
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if (y == fa)
            continue;
        dfs2(y, x);
    }
    TT1.modify(TT1.rt, 1, M, siz[x], -siz[x] * w[x]);
    TT2.modify(TT2.rt, 1, M, siz[x], -w[x]);
}
signed main() {
    freopen("banking.in", "r", stdin);
    freopen("banking.out", "w", stdout);
    scanf("%lld", &t);
    TT1.tot_dot = TT2.tot_dot = maxn * 40 - 1;
    TT1.cls();
    TT2.cls();
    while (t--) {
        scanf("%lld", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        graph_cls();
        for (int i = 1; i < n; i++) {
            scanf("%lld%lld%lld", &x, &y, &z);
            add(x, y, z);
            add(y, x, z);
        }
        dfs1(1, 0, 0);
        Mem(f, n);
        T = 0;
        // bigger
        for (int i = 1; i <= n; i++) {
            q[++T] = (Q){ st[i], ed[i], i, 1, siz[i] / 2, siz[i] };
            q[++T] = (Q){ st[i], ed[i], i, -1, (M - siz[i]) / 2, M - siz[i] };
        }
        sort(q + 1, q + T + 1, [&](Q A, Q B) { return A.lim < B.lim; });
        T1.cls();
        T2.cls();
        iota(id + 1, id + n + 1, 1);
        sort(id + 1, id + n + 1, [&](int x, int y) { return siz[x] < siz[y]; });
        int now = 0;
        for (int i = 1; i <= T; i++) {
            while (now < n && siz[id[now + 1]] <= q[i].lim) {
                now++;
                x = id[now];
                T1.add(dfn[x], siz[x] * w[x]);
            }
            if (q[i].typ == 1)
                f[q[i].id] += T1.qq(q[i].l, q[i].r);
            else
                f[q[i].id] += (T1.qq(1, q[i].l - 1) + T1.qq(q[i].r + 1, n));
        }
        // first part
        T1.cls();
        sort(q + 1, q + T + 1, [&](Q A, Q B) { return A.lim > B.lim; });
        sort(id + 1, id + n + 1, [&](int x, int y) { return siz[x] > siz[y]; });
        now = 0;
        for (int i = 1; i <= T; i++) {
            while (now < n && siz[id[now + 1]] > q[i].lim) {
                now++;
                x = id[now];
                // printf("pos %lld,T1 add %lld,T2 %lld\n",dfn[x],siz[x]*w[x],w[x]);
                T1.add(dfn[x], siz[x] * w[x]);
                T2.add(dfn[x], w[x]);
            }
            if (q[i].typ == 1) {
                int add = T2.qq(q[i].l, q[i].r);
                int del = T1.qq(q[i].l, q[i].r);
                f[q[i].id] += (add * q[i].X - del);
                // if(q[i].id==4)printf("add %lld,del %lld\n",add,del);
            } else {
                int add = T2.qq(1, q[i].l - 1) + T2.qq(q[i].r + 1, n);
                int del = T1.qq(1, q[i].l - 1) + T1.qq(q[i].r + 1, n);
                // if(q[i].id==4)printf("range [%lld %lld],add %lld,del %lld\n",q[i].l,q[i].r,add,del);
                f[q[i].id] += (add * q[i].X - del);
            }
        }
        T1.cls();
        T2.cls();
        // for(int i=1;i<=n;i++)printf("f:%lld\n",f[i]);
        // puts("");
        dfs2(1, 0);
        int res = inf;
        for (int i = 1; i <= n; i++) res = min(res, f[i]);
        // for(int i=1;i<=n;i++)printf("f:%lld\n",f[i]);
        printf("%lld\n", res);
        TT1.cls();
        TT2.cls();
    }
    return 0;
}

