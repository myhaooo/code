#include<bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
#define fi first
#define se second
#define mk make_pair
using namespace std;

const int MAX_N = 5050, MAX_K = 5e5 + 10, MAX_DEPTH = 30;
int n, K;
int to[MAX_N];
int hs[12][MAX_N], ln[12], pb[MAX_N];
int base = 131, mod = 1011451423;
int hsh[MAX_N];
int gh(int l, int r) {
    return (hsh[r] - 1LL * pb[r - l + 1] * hsh[l - 1] % mod + mod) % mod;
}

ll g[MAX_N];
int tr[MAX_N];

struct SegmentTree {
    pii T[MAX_N << 2];
    #define ls p*2
    #define rs p*2+1
    #define mid (l + r) / 2

    void update(int p) {
        T[p] = max(T[ls], T[rs]);
    }

    void build(int p, int l, int r) {
        if (l == r) {
            T[p] = mk(to[l], -l);
            return;
        }
        build(ls, l, mid);
        build(rs, mid + 1, r);
        update(p);
    }

    pii query(int p, int l, int r, int pl, int pr) {
        if (pl <= l && r <= pr) return T[p];
        pii res = mk(-1, 0);
        if (pl <= mid) res = max(res, query(ls, l, mid, pl, pr));
        if (pr > mid) res = max(res, query(rs, mid + 1, r, pl, pr));
        return res;
    }

    #undef ls
    #undef rs
    #undef mid
} segTree;

vector<int> E[MAX_N];
int dep[MAX_N], fa[MAX_N][22];
ll sm[MAX_N][22], val[MAX_N], sum[MAX_N], tg[MAX_N];
bool vis[MAX_N];

void dfs(int u, int pr) {
    vis[u] = 1;
    dep[u] = dep[pr] + 1;
    fa[u][0] = pr;
    sm[u][0] = to[u];
    for (int i = 1; i <= 19; ++i) {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        sm[u][i] = sm[u][i - 1] + sm[fa[u][i - 1]][i - 1];
    }
    for (int v : E[u]) {
        if (!vis[v]) dfs(v, u);
    }
}

void dfs2(int u) {
    vis[u] = 1;
    for (int v : E[u]) {
        if (!vis[v]) {
            dfs2(v);
            val[u] += val[v];
        }
    }
}

void solve() {
    cin >> n >> K;
    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        ln[i] = s.length();
        int h = 0;
        for (int j = 0; j < ln[i]; ++j) {
            h = (1LL * h * base + (s[j] - 'a')) % mod;
            hs[i][j + 1] = h;
        }
    }

    string t;
    cin >> t;
    int len = t.length();
    t = ' ' + t;
    
    //
    for (int i = 1; i <= len; ++i) {
        hsh[i] = (1LL * hsh[i - 1] * base + (t[i] - 'a')) % mod;
    }
    pb[0] = 1;
    for (int i = 1; i <= len; ++i) {
        pb[i] = (1LL * pb[i - 1] * base) % mod;
    }


    for (int i = 1; i <= len; ++i) {
        int l = i - 1, r = len;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            int hsh1 = gh(i, mid);
            int cnt = 0;
            for (int j = 1; j <= n; ++j) {
                if (ln[j] >= mid - i + 1 && hsh1 == hs[j][mid - i + 1]) {
                    ++cnt;
                }
            }
            if (cnt > 0) l = mid;
            else r = mid - 1;
        }
        to[i] = l;
    }
    to[len + 1] = len;

    segTree.build(1, 1, len + 1);

    for (int i = 1; i <= len; ++i) {
        tr[i] = -segTree.query(1, 1, len + 1, i, to[i] + 1).se;
    }

    for (int i = 1; i <= len; ++i) {
        E[tr[i]].push_back(i);
    }

    memset(vis, 0, sizeof(vis));
    for (int i = len; i >= 1; --i) {
        if (!vis[i]) dfs(i, i);
    }

    ll ans = 0;
    for (int i = 1; i <= len; ++i) {
        ll s = 0;
        int now = i;
        for (int j = 19; j >= 0; --j) {
            if ((K >> j) & 1) {
                s += sm[now][j];
                now = fa[now][j];
            }
        }
        ans += s;
        sum[i] = s;
        if (dep[i] > K) {
            val[i]++;
            val[now]--;
        } else {
            val[i]++;
            val[now]--;
            tg[now] += K - (dep[i] - 1);
        }
        vis[i] = 0;
        sum[i] += K;
        sum[i] -= 1LL * K * i;
    }

    ans += 1LL * len * K;
    ans -= 1LL * K * (1LL * len * (len + 1) / 2);

    memset(vis, 0, sizeof(vis));
    for (int i = len; i >= 1; --i) {
        if (!vis[i]) dfs2(i);
    }
    
    for (int i = 1; i <= len; ++i) {
        val[i] += tg[i];
        g[i + 1] -= K;
        g[i] += sum[i];
        g[i + 1] -= sum[i];
        g[to[i] + 2] += val[i];
    }
    for (int i = 1; i <= len; ++i) {
        g[i] += g[i - 1];
    }
    for (int i = 1; i <= len; ++i) {
        g[i] += g[i - 1];
    }

    cout << ans << endl;
    for (int i = 1; i <= len; ++i) {
        cout << g[i] << ' ';
    }
    cout << endl;
}

int main() {
    int sub;
    cin >> sub;
    solve();
    return 0;
}

