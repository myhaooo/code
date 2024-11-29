#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5;
int n, m;
int dis[MAXN + 10], vis[MAXN + 10];
int fa[MAXN + 10], dep[MAXN + 10];

struct A {
	int to, w;
};
vector<A> g[MAXN];

void dij(int s) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>q;
	q.push(make_pair(0, s));
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[s] = 0;
	dep[s] = 0;
	while (!q.empty()) {
		pair<int, int> ex = q.top();
		q.pop();
		if (vis[ex.second])
			continue;
		vis[ex.second] = 1;
		for (int i = 0; i < g[ex.second].size(); i++) {
			int v = g[ex.second][i].to, w = g[ex.second][i].w;
			if (!vis[v] && dis[v] > dis[ex.second] + w) {
				dis[v] = dis[ex.second] + w;
				fa[v] = ex.second;
				dep[v] = dep[ex.second] + 1;
				q.push(make_pair(dis[v], v));
			}
		}
	}
}
int ans[MAXN + 10];
queue<int>q;

void spfa(int s) {
	vis[s] = 1;
	dis[s] = 0, memset(dis, 0x3f3f3f3f, sizeof(dis));
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = 0;
		for (auto ed : g[u]) {
			int v = ed.to, w = ed.w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				dep[v] = dep[u] + 1;
				if (!vis[v])
					q.push(v), vis[v] = 1;
			}

		}
	}
}

void work(int x, int y, int w) {
	while (x != y) {
		if (dep[x] < dep[y]) {
			swap(x, y);
		}
		ans[x] = min(ans[x], w - dis[x]);
		x = fa[x];
	}
}

int main() {
	freopen("path.in", "r", stdin);
	freopen("path.out", "w", stdout);
	cin >> n >> m;
	for (int i = 1, a, b, c; i <= m; i++) {
		cin >> a >> b >> c;
		g[a].push_back(A{b, c});
		g[b].push_back(A{a, c});
	}
	dij(1);
	memset(ans, 0x3f, sizeof(ans));
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < g[i].size(); j++) {
			int v = g[i][j].to, w = g[i][j].w;
			if (dis[v] != dis[i] + w && dis[i] != dis[v] + w) {
				work(i, v, dis[v] + dis[i] + w);
			}
		}
	}
	for (int i = 2; i <= n; i++) {
		if (ans[i] == 0x3f3f3f3f)
			printf("-1\n");
		else
			printf("%d\n", ans[i]);
	}
	return 0;
}