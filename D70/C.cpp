#include <bits/stdc++.h>
#define int long long
using ull = unsigned long long;
using namespace std;

const int N = 1e6 + 10, P = 1e9 + 7;
const ull bas = 998244853; ull pw[N], has[N];
int t, n, m, w, d, a[N], b[N];
int inv[N], fac[N], ifac[N];

inline void init() {
    inv[0] = inv[1] = fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    pw[0] = 1, pw[1] = bas;
    for (int i = 2; i <= 1e6; ++i) {
        inv[i] = inv[P % i] * (P - P / i) % P;
        fac[i] = fac[i - 1] * i % P, ifac[i] = ifac[i - 1] * inv[i] % P;
        pw[i] = pw[i - 1] * bas;
    }
    return ;
}

inline int C(int x, int y) {
    if (x < 0 || y < 0 || x < y) return 0;
    return fac[x] * ifac[y] % P * ifac[x - y] % P;
} inline ull query(int l, int r) {
    return has[r] - pw[r - l + 1] * has[l - 1];
}

inline void solve() {
    vector <int> g, cnt; vector <bool> vis;
    cin >> n >> m >> w >> d; ull H = 0;
    g.push_back(0), cnt.resize(w + 10), vis.resize(w + 10);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) {
        cin >> b[i], vis[b[i]] = true;
        H = H * bas + b[i];
    }
    for (int i = 1; i <= n; ++i) if (vis[a[i]]) g.push_back(i);
    int siz = 0, all = 0, res = 0, len = g.size() - 1;
    if (len < m) return cout << 0 << endl, void();
    for (int i = 1; i <= w; ++i) if (!vis[i]) ++all;
    for (int i = 1; i <= m; ++i) has[i] = has[i - 1] * bas + a[g[i]];
    for (int i = g[1]; i <= g[m]; ++i)
        if (!vis[a[i]]) if (++cnt[a[i]] == 1) ++siz;
    (res += (query(1, m) == H) * C(all - siz, d - siz)) %= P;
    for (int i = 2; i + m - 1 <= len; ++i) {
        for (int j = g[i - 1]; j < g[i]; ++j)
            if (!vis[a[j]]) if (!(--cnt[a[j]])) --siz;
        for (int j = g[i + m - 2] + 1; j <= g[i + m - 1]; ++j)
            if (!vis[a[j]]) if (++cnt[a[j]] == 1) ++siz;
        has[i + m - 1] = has[i + m - 2] * bas + a[g[i + m - 1]];
        (res += (query(i, i + m - 1) == H) * C(all - siz, d - siz)) %= P;
    }
    return cout << res << endl, void();
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    init(); cin >> t; while (t--) solve(); return 0;
}
