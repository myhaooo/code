#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m, k;

struct edge {
	ll u, v, w;
} E[200010];

bool cmp(edge A, edge B) {
	return A.w < B.w;
}
ll fa[200010];

ll get(ll x) {
	if (fa[x] == x)
		return x;
	return fa[x] = get(fa[x]);
}

int main() {
	freopen("speed.in", "r", stdin);
	freopen("speed.out", "w", stdout);
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
		cin >> E[i].u >> E[i].v >> E[i].w;
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	sort(E + 1, E + 1 + m, cmp);

	ll ans1 = abs(E[1].w - k);
	for (int i = 2; i <= m; i++)
		ans1 = min(ans1, abs(E[i].w - k));
	ll ans = 0;
	ll cnt = 0;
	for (int i = 1; i <= m; i++) {
		ll fu = get(E[i].u);
		ll fv = get(E[i].v);
		if (fu != fv) {
			fa[fu] = fv;
			if (E[i].w > k)
				ans += E[i].w - k;
			cnt++;
		}
		if (cnt == n - 1) {
			if (E[i].w < k)
				ans = ans1;
			break;
		}
	}
	printf("%lld\n", ans);
	return 0;
}