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

	// ��һ�� DFS���ӽڵ� 1 ��ʼ
	dfs(1, -1, 0);

	// �ҵ��� 1 ��Զ�ĵ�
	int farthest_node = 1;
	for (int i = 1; i <= n; ++i) {
		if (dist[i] > dist[farthest_node]) {
			farthest_node = i;
		}
	}

	// �ڶ��� DFS���� farthest_node ��ʼ
	dfs(farthest_node, -1, 0);

	// �ҵ�����ֱ��
	int diameter = 0;
	for (int i = 1; i <= n; ++i) {
		diameter = max(diameter, dist[i]);
	}

	// �����
	cout << diameter + 1 << endl;

	return 0;
}
