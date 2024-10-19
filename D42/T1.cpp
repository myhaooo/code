#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
typedef pair<int, int> pii;

struct Edge {
	int to, cost;
	Edge(int to, int cost) : to(to), cost(cost) {}
};

vector<vector<Edge>> graph;
vector<int> dist;
vector<pii> points;

int manhattan(int i, int j) {
	return min(abs(points[i].first - points[j].first), abs(points[i].second - points[j].second));
}

void dijkstra(int l) {
	priority_queue<pii, vector<pii>, greater<pii>> pq;
	dist[l] = 0;
	pq.push({0, l});

	while (!pq.empty()) {
		int d = pq.top().first;
		int u = pq.top().second;
		pq.pop();

		if (d > dist[u])
			continue;
		for (auto &edge : graph[u]) {
			int v = edge.to;
			int w = edge.cost;
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
		for (int v = 0; v < points.size(); ++v) {
			if (v != u) {
				int teleport_cost = manhattan(u, v);
				if (dist[u] + teleport_cost < dist[v]) {
					dist[v] = dist[u] + teleport_cost;
					pq.push({dist[v], v});
				}
			}
		}
	}
}

int main() {
	freopen("teleport.in", "r", stdin);
	freopen("teleport.out", "w", stdout);
	int n, M;
	cin >> n >> M;

	points.resize(n);
	graph.resize(n);
	dist.assign(n, INF);

	for (int i = 0; i < n; ++i) {
		cin >> points[i].first >> points[i].second;
	}

	for (int i = 0; i < M; ++i) {
		int U, V, W;
		cin >> U >> V >> W;
		--U, --V;
		graph[U].emplace_back(V, W);
		graph[V].emplace_back(U, W);
	}

	dijkstra(0);

	for (int i = 1; i < n; ++i) {
		cout << dist[i] << " ";
	}
	cout << endl;

	return 0;
}
