#include <bits/stdc++.h>

using namespace std;

const int Maxn = 6e5 + 5;
const int Inf = 2e9;

int n, m;

int head[Maxn], edgenum;
struct node {
	int nxt, to;
}edge[Maxn];

void add(int u, int v) {
	edge[++edgenum] = {head[u], v};
	head[u] = edgenum;
}

int dfn[Maxn], ind;
int f[Maxn];
struct Edge {
	int u, v, w;
};
vector <Edge> E;
int p[Maxn], cnt;
void dfs(int x) {
	dfn[x] = ++ind;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(dfn[to]) continue;
		dfs(to);
	}
	cnt = 0;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(dfn[to] < dfn[x]) continue;
		if(!f[to]) p[++cnt] = to;
		else {
			E.push_back((Edge){x, to, f[to]});
			f[to] = 0;
		}
	}
	for(int i = 1; i < cnt; i += 2) {
		E.push_back((Edge){p[i], x, p[i + 1]});
	}
	if(cnt & 1) f[x] = p[cnt];
}

int main() {
	freopen("lca.in", "r", stdin);
	freopen("lca.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		add(u, v), add(v, u);
	}
	for(int i = 1; i <= n; i++) {
		if(!dfn[i]) dfs(i);
	}
	cout << E.size() << '\n';
	for(auto x : E) cout << x.u << " " << x.v << " " << x.w << '\n';
	return 0;
}

