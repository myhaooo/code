#include<bits/stdc++.h>
#define pos(x, y) ((x - 1) * m + y)
using namespace std;
const int N = 5e4 + 3;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
int n, m, K, Q;
string s[N];
int fa[N];
inline int find(int x) {
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
inline void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) fa[y] = x;
}


int id[N], cnt;
bool vis[N];
void dfs(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 1 || nx > n || ny < 1 || ny > m || s[nx][ny] == '#' || vis[pos(nx, ny)]) continue;
		vis[pos(nx, ny)] = true;
		merge(pos(x, y), pos(nx, ny));
		dfs(nx, ny);
	}
}
vector<int> e[N];
bool vis2[N];
bool check(int st, int ed) {
	memset(vis2, 0, (cnt + 1) * sizeof(bool));
	queue<int> q;
	q.push(st);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (vis2[u]) continue;
		vis2[u] = true;
		for (int v : e[u]) {
			if (vis2[v]) continue;
			if (v == ed) return true;
			q.push(v);
		}
	}
	return false;
}
int main() {
	freopen("treasure.in", "r", stdin);
	freopen("treasure.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> n >> m >> K >> Q;
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		s[i] = '0' + s[i];
	}
	for (int i = 1; i <= n * m; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!vis[pos(i, j)] && s[i][j] == '.') {
				dfs(i, j);
				id[find(pos(i, j))] = ++cnt;
			}
		}
	}
	for (int i = 1, x, y, xx, yy; i <= K; i++) {
		cin >> x >> y >> xx >> yy;
		int fx = find(pos(x, y)), fy = find(pos(xx, yy));
		if (fx != fy) e[id[fx]].push_back(id[fy]);
	}
	for (int i = 1, x, y, xx, yy; i <= Q; i++) {
		cin >> x >> y >> xx >> yy;
		int fx = find(pos(x, y)), fy = find(pos(xx, yy));
		if (fx == fy) {
			cout << 1 << "\n";
			continue;
		}
		if (check(id[fx], id[fy])) cout << 1 << "\n";
		else cout << 0 << "\n";
	}
	return 0;
}
