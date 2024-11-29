#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7, inf = 1e9;
inline int qpow(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1)
            res = res * a % mod;
    return res;
}
inline void W(int &x, int y) { x = (x + y) % mod; }
int n, D, num[N], ans;
bool f[N], d[N], rt[N], up[N], val[N];
vector<int> e[N];
inline void dfs(int x, int fa) {
    f[x] = 0;
    int len = e[x].size();
    for (int v : e[x]) {
        if (v == fa)
            continue;
        d[v] = f[x];
        dfs(v, x);
        f[x] |= !f[v];
    }
    f[x] = 0;
    for (int i = len - 1; ~i; --i) {
        int v = e[x][i];
        if (v == fa)
            continue;
        d[v] |= f[x];
        f[x] |= !f[v];
        if (d[v])
            val[v] = 0;
        else
            val[v] = 1;
    }
}
inline void change(int x, int fa) {
    if (x == 1) {
        rt[x] = f[x];
    } else {
        up[x] = !(up[fa] | d[x]);
        rt[x] = up[x] | f[x];
    }
    for (int v : e[x]) {
        if (v == fa)
            continue;
        change(v, x);
    }
}
inline void sol(int x, int fa, bool now) {
    if (!now) {
        if (f[1])
            W(ans, n);
    } else {
        if (f[1]) {
            if (f[x])
                W(ans, n);
            else
                W(ans, num[1]);
        } else {
            if (!f[x])
                W(ans, num[0]);
        }
    }
    for (int v : e[x]) {
        if (v == fa)
            continue;
        sol(v, x, now & val[v]);
    }
}
inline void sub() {
    dfs(1, 0);
    change(1, 0);
    for (int i = 1; i <= n; ++i) num[rt[i]]++;
    sol(1, 0, 1);
    cout << ans << '\n';
}
signed main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>D;
    for (int i = 1,u,v; i < n; ++i) {
        cin>>u>>v;
        e[u].pb(v);
        e[v].pb(u);
    }
    if (D == 1) {
        sub();
        exit(0);
    }
    cout << qpow(n, 2 * D) << '\n';
}

