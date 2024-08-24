#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 500100, M = 1000100, MOD = 1e9 + 7;
int n, m, p;
int tot, tot2, head[N], head2[N];
int num, top, stk[N], dfn[N], low[N], bel[N];
int deg[N], V[N], E[N], s[N];
bool vis[N];
ll ans, f[N][2];
struct Edge {
    int to, nxt;
} e[M << 1], e2[M << 1];

void add(int u, int v) {
    e[++tot] = Edge{v, head[u]};
    head[u] = tot;
}

void add2(int u, int v) {
    e2[++tot2] = Edge{v, head2[u]};
    head2[u] = tot2;
}

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++num;
    stk[++top] = u;
    vis[u] = 1;
    for (int i = head[u], v; i; i = e[i].nxt) {
        v = e[i].to;
        if (v == fa) continue;
        if (!dfn[v]) tarjan(v, u), low[u] = min(low[u], low[v]);
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        p++; int x;
        while(1) {
            x = stk[top--];
            // 因为不需要知道每个边双连通分量里都有哪些点，只记录每个点属于哪个边双连通分量即可。
            vis[x] = 0;
            bel[x] = p;
            V[p]++; // 累加该边双连通分量内点数
            if(x==u)break;
        } 
    }
}


ll qp(ll base, int e) { 
    ll res = 1;
    while (e) {
        if (e & 1) (res*=base)%=MOD;
        (base*=base)%=MOD;
        e >>= 1;
    }
    return res;
}

void dfs(int u, int fa) { // dfs 计算 s[]
    s[u] = E[u];
    for (int i = head2[u], v; i; i = e2[i].nxt) {
        v = e2[i].to;
        if (v == fa) continue;
        dfs(v, u); s[u] += s[v] + 1;
    }
}


void dp(int u, int fa) {
    for (int i = head2[u], v; i; i = e2[i].nxt) {
        v = e2[i].to;
        if (v == fa) continue;
        dp(v, u);
        f[u][1] = (f[u][1] * (((f[v][0] << 1) + f[v][1]) % MOD) % MOD + f[u][0] * f[v][1] % MOD) % MOD;
        f[u][0] = f[u][0] * ((f[v][0] << 1) % MOD) % MOD;
    }
    if (u == 1) ans = (ans + f[u][1]) % MOD; 
    else ans = (ans + f[u][1] * qp(2, s[1] - s[u] - 1)) % MOD;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        add(u, v), add(v, u);
    }
    tarjan(1, 0); // 边双缩点
    for (int u = 1; u <= n; u++) {
        for (int i = head[u], v; i; i = e[i].nxt) {
            v = e[i].to;
            if (bel[u] != bel[v]) add2(bel[u], bel[v]); // 如果属于两个不同的边双连通分量，则将这两个边双连通分量连边
            else E[bel[u]]++; // 否则该双连通分量内边数 + 1
        }
    }
    for (int i = 1; i <= p; i++) {
        E[i] >>= 1; // 因为是无向边，每一条边会累加 2 次，故 E[i] 需要除以 2
        // 赋初值
        f[i][0] = qp(2, E[i]);
        f[i][1] = qp(2, V[i] + E[i]) - f[i][0];
    }
    dfs(1, 0); dp(1, 0);
    cout << ans;
    return 0;
}