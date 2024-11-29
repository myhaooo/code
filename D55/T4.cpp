#include <cctype>
#include <cstdio>
#include <climits>
#include <algorithm>

template <typename T> inline void read(T& x) {
    int f = 0, c = getchar(); x = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - 48, c = getchar();
    if (f) x = -x;
}
template <typename T, typename... Brgs>
inline void read(T& x, Brgs&... Crgs) {
    read(x); read(Crgs...); 
}
template <typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) write(x / 10);
    putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); puts(""); }
const int maxn = 1e5 + 207;
const int maxm = 307;
const int mod = 1e9 + 7;

int v[maxn << 1], head[maxn], next[maxn << 1], tot;
int dep[maxn], size[maxn], top[maxn], son[maxn], fa[maxn], dfn[maxn], xys;
int n, q;

inline void ae(int x, int y) {
    v[++tot] = y; next[tot] = head[x]; head[x] = tot;
    v[++tot] = x; next[tot] = head[y]; head[y] = tot;
}
void dfs(int x) {
    size[x] = 1; dep[x] = dep[fa[x]] + 1;
    for (int i = head[x]; i; i = next[i])
        if (v[i] != fa[x]) {
            fa[v[i]] = x;
            dfs(v[i]);
            size[x] += size[v[i]];
            if (size[v[i]] > size[son[x]]) son[x] = v[i];
        }
}
void dfs(int x, int t) {
    top[x] = t; dfn[x] = ++xys;
    if (son[x]) dfs(son[x], t);
    for (int i = head[x]; i; i = next[i])
        if (v[i] != son[x] && v[i] != fa[x])
            dfs(v[i], v[i]);
}

int s[maxn];
inline void add(int x, int val) { for (; x <= n; x += x & -x) s[x] += val; }
inline int sum(int l, int r) {
    int ans = 0;
    for (; r; r -= r & -r) ans += s[r];
    for (--l; l; l -= l & -l) ans -= s[l];
    return ans;
}

inline void mark(int x) { add(dfn[x], 1); }
inline void del(int x) { add(dfn[x], -1); }
inline int query(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
        ans += sum(dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    return ans + (dep[x] < dep[y] ? sum(dfn[x], dfn[y]) : sum(dfn[y], dfn[x]));
}

int dp[maxn][maxm];
int f[maxn];
int node[maxn], K, m, r;

inline void clear() {
    for (int i = 1; i <= K; ++i)
        for (int j = 1, _end = std::min(i, m); j <= _end; ++j)
            dp[i][j] = 0;
    for (int i = 1; i <= K; ++i) {
        f[node[i]] = 0;
        del(node[i]);
    }
}

int main() {
	freopen("building.in","r",stdin);
	freopen("building.out","w",stdout);
    read(n, q);
    for (int i = 1, x, y; i < n; ++i)
        read(x, y), ae(x, y);
    dfs(1); dfs(1, 1);
    while (q--) {
        read(K, m, r);
        for (int i = 1; i <= K; ++i) {
            read(node[i]);
            mark(node[i]);
        }
        for (int i = 1; i <= K; ++i)
            f[node[i]] = query(node[i], r) - 1;
        std::sort(node + 1, node + K + 1, [](int a, int b) -> bool { return f[a] < f[b]; });
        dp[1][1] = 1;
        for (int i = 2; i <= K; ++i)
            for (int j = 1, _end = std::min(i, m); j <= _end; ++j)
                if (j - f[node[i]] >= 0)
                    dp[i][j] = (1ll * dp[i - 1][j] * (j - f[node[i]]) % mod + dp[i - 1][j - 1]) % mod;
                else
                    dp[i][j] = dp[i - 1][j - 1];
        int ans = 0;
        for (int i = 1; i <= m; ++i)
            if ((ans += dp[K][i]) >= mod) ans -= mod;
        writeln(ans);
        clear();
    }
    return 0;
}
