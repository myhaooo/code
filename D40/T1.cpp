#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k, fa[200010];
const int inf = INT_MAX;

struct edge {
	int u, v, w;
} e[200010];

bool cmp(edge a, edge b) {
	return a.w < b.w;
}

int get(int x) {
	if (fa[x] == x)
		return x;
	return fa[x] = get(fa[x]);
}

main() {
	freopen("speed.in", "r", stdin);
	freopen("speed.out", "w", stdout);
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
		cin >> e[i].u >> e[i].v >> e[i].w;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	sort(e + 1, e + 1 + m, cmp);

	int ans1 = inf;
	for (int i = 1; i <= m; i++)
		ans1 = min(ans1, abs(e[i].w - k));
	int ans = 0;
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		int fu = get(e[i].u);
		int fv = get(e[i].v);
		if (fu != fv) {
			fa[fu] = fv;
			if (e[i].w > k)
				ans += e[i].w - k;
			cnt++;
		}
		if (cnt == n - 1) {
			if (e[i].w < k)
				ans = ans1;
			break;
		}
	}
	cout << ans << "\n";
	return 0;
}