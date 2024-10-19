#include <bits/stdc++.h>
#define int long long

using namespace std;

typedef unsigned long long ull;
const int Maxn = 5e5 + 5;
const int Inf = 2e9;
const ull base = 131;
ull p[Maxn];

int T;
int n;
int u[Maxn], v[Maxn], w[Maxn], t[Maxn];
int head[Maxn], edgenum;
struct node {
	int nxt, to, w;
}edge[Maxn << 1];

void add(int u, int v, int w) {
	edge[++edgenum] = {head[u], v, w};
	head[u] = edgenum;
}

int cnt[Maxn];

unordered_map <ull, int> vis;
ull mdf(ull S, int x, int val) {
	ull T = S + p[x] * val;
	return T;
}

void dfs(int x, int fa, ull S) {
//	cout << " " << x << " " << fa << '\n';
	vis[S]++;
	for(int i = head[x]; i; i = edge[i].nxt) {
		int to = edge[i].to;
		if(to == fa) continue;
		cnt[edge[i].w]++;
		ull T;
		if(cnt[edge[i].w] & 1) {
			T = mdf(S, edge[i].w, 1);
		}
		else {
			T = mdf(S, edge[i].w, -1);
		}
		dfs(to, x, T);
		cnt[edge[i].w]--;
	}
}

void init() {
	vis.clear();
	edgenum = 0;
	for(int i = 1; i <= n; i++) {
		cnt[i] = head[i] = 0;
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> T;
	p[0] = 1;
	for(int i = 1; i < Maxn; i++) {
		p[i] = p[i - 1] * base;
	}
	while(T--) {
		init();
		cin >> n;
		for(int i = 1; i < n; i++) {
			cin >> u[i] >> v[i] >> w[i];
			t[i] = w[i]; 
		}
		sort(t + 1, t + n);
		int cnt = unique(t + 1, t + n) - t - 1;
		for(int i = 1; i < n; i++) {
			w[i] = lower_bound(t + 1, t + cnt + 1, w[i]) - t;
			add(u[i], v[i], w[i]), add(v[i], u[i], w[i]);
		}
		dfs(1, 0, 0);
		int ans = n * (n - 1) / 2;
		for(auto i : vis) {
			ans -= i.second * (i.second - 1) / 2;
		}
		cout << ans << '\n';
	}
	return 0;
}