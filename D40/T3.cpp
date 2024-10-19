#include <bits/stdc++.h>
using namespace std;
#define ll long long
constexpr int N = 5e5 + 5, M = 1e9 + 7;
int n, a[N], b[N], ans[N], dfn[N], siz[N], rnk[N], tot;
vector<int> G[N];

inline void dfs(int u, int fa) {
	rnk[dfn[u] = ++tot] = u;
	siz[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			dfs(v, u);
			siz[u] += siz[v];
		}
}

int main() {
	//freopen("distance.in", "r", stdin); freopen("distance.out", "w", stdout);
	cin >> n;
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for (int i = 1; i <= n; ++i)
		cin >> a[i] >> b[i];
	dfs(1, 0);
	for (int i = 1; i <= n; ++i) {
		for (int u = dfn[i]; u < dfn[i] + siz[i]; ++u) {
			for (int v = dfn[i]; v < dfn[i] + siz[i]; ++v) {
				ans[i] = ((ll)ans[i] + (ll)min(abs(a[rnk[u]] - a[rnk[v]]), abs(b[rnk[u]] - b[rnk[v]]))) % M;
			}
		}
	}
	for (int i = 1; i <= n; ++i)
		cout << ans[i] << endl;
	return 0;
}