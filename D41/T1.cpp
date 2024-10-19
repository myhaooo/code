#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 100005;
vector<int> adj[MAXN];
int dist[MAXN];

void dfs(int u, int parent, int d) {
	dist[u] = d;
	for (int v : adj[u]) {
		if (v != parent) {
			dfs(v, u, d + 1);
		}
	}
}

int main() {
	int n;
	cin >> n;

	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	// 第一次 DFS，从节点 1 开始
	dfs(1, -1, 0);

	// 找到离 1 最远的点
	int farthest_node = 1;
	for (int i = 1; i <= n; ++i) {
		if (dist[i] > dist[farthest_node]) {
			farthest_node = i;
		}
	}

	// 第二次 DFS，从 farthest_node 开始
	dfs(farthest_node, -1, 0);

	// 找到树的直径
	int diameter = 0;
	for (int i = 1; i <= n; ++i) {
		diameter = max(diameter, dist[i]);
	}

	// 输出答案
	cout << diameter + 1 << endl;

	return 0;
}
