#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 5;
int n, m, Q, K;
int ch[N * 30][2], tot, w[N];
struct E {
    int u, v;
} e[N];
vector<E> g[N * 30];
vector<int> bk[N * 30];
void ins(int x, int id) {
    int u = 0, c;
    for (int i = 30; i >= 0; --i) {
        c = (x >> i) & 1;
        if (!ch[u][c])
            ch[u][c] = ++tot;
        u = ch[u][c];
    }
    bk[u].push_back(id);
}
void add(int x, E tmp) {
    int u = 0, c, k;
    for (int i = 30; i >= 0; --i) {
        c = (x >> i) & 1;
        k = (K >> i) & 1;
        if (k == 1)
            g[ch[u][c]].push_back(tmp);
        if (ch[u][c ^ k])
            u = ch[u][c ^ k];
        else
            return;
    }
}
int fa[N], top;
ll ans[N], sz[N], h[N], res;
struct nd {
    int x, y, w, id;
} s[N];
inline int getf(int x) {
    if (fa[x] == x)
        return x;
    return getf(fa[x]);
}
inline void merge(int x, int y, int id) {
    if (h[x] < h[y])
        swap(x, y);
    fa[y] = x;
    res += sz[x] * sz[y];
    sz[x] += sz[y];
    s[++top] = { x, y, h[x] == h[y], id };
    h[x] += (h[x] == h[y]);
}
void solve(int x) {
    ll tp = res;
    for (E i : g[x]) {
        int tu = getf(i.u), tv = getf(i.v);
        if (tu != tv)
            merge(tu, tv, x);
    }
    for (int i : bk[x]) ans[i] = res;
    if (ch[x][0])
        solve(ch[x][0]);
    if (ch[x][1])
        solve(ch[x][1]);
    while (top && s[top].id == x) {
        nd tp = s[top];
        h[tp.x] -= tp.w;
        sz[tp.x] -= sz[tp.y];
        fa[tp.y] = tp.y;
        top--;
    }
    res = tp;
}
int main() {
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    cin >> n >> m >> Q >> K;
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &e[i].u, &e[i].v, &w[i]);
    for (int i = 1; i <= Q; ++i) {
        int x;
        scanf("%d", &x);
        ins(x, i);
    }
    for (int i = 1; i <= m; ++i) add(w[i], e[i]);
    for (int i = 1; i <= n; ++i) fa[i] = i, sz[i] = h[i] = 1;
    g[0].clear();
    solve(0);
    for (int i = 1; i <= Q; ++i) printf("%lld\n", ans[i]);
    return 0;
}
/*
将询问插入01trie.
再把边挂到合法区间上。
从高到低，在某位四种情况：
          (trie)
c=0 k=0:  0 sub 1 no
c=0 k=1:  0 yes 1 sub
c=1,k=0:  0 no  1 sub
c=1,k=1:  0 sub 1 yes
显然每条边最多挂在log个节点上。
*/
