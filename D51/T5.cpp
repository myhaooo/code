#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 1000100;

int n, lsh[maxn], tot, fa[maxn];
pii b[maxn];

struct node {
	int l, r, x;
} a[maxn];

struct edg {
	int u, v, d;
	edg(int a = 0, int b = 0, int c = 0) : u(a), v(b), d(c) {}
} E[maxn];

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

inline bool merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		fa[x] = y;
		return 1;
	} else {
		return 0;
	}
}

void solve() {
	tot = 0;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].l >> a[i].r >> a[i].x;
		lsh[++tot] = a[i].l;
		lsh[++tot] = (++a[i].r);
	}
	int m = 0;
	sort(lsh + 1, lsh + tot + 1);
	tot = unique(lsh + 1, lsh + tot + 1) - lsh - 1;
	for (int i = 1; i <= n; ++i) {
		a[i].l = lower_bound(lsh + 1, lsh + tot + 1, a[i].l) - lsh;
		a[i].r = lower_bound(lsh + 1, lsh + tot + 1, a[i].r) - lsh;
		b[++m] = mkp(a[i].l, i);
		b[++m] = mkp(a[i].r, -i);
	}
	set<pii> S;
	sort(b + 1, b + m + 1);
	int tt = 0;
	for (int i = 1; i <= m; ++i) {
		int j = b[i].scd;
		if (j > 0) {
			auto it = S.insert(mkp(a[j].x, j)).fst;
			if (it != S.begin()) {
				int k = prev(it)->scd;
				E[++tt] = edg(j, k, abs(a[j].x - a[k].x));
			}
			if (next(it) != S.end()) {
				int k = next(it)->scd;
				E[++tt] = edg(j, k, abs(a[j].x - a[k].x));
			}
		} else {
			j = -j;
			S.erase(mkp(a[j].x, j));
		}
	}
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
	}
	sort(E + 1, E + tt + 1, [&](const edg &a, const edg &b) {
		return a.d < b.d;
	});
	ll ans = 0, cnt = 0;
	for (int i = 1; i <= tt; ++i) {
		if (merge(E[i].u, E[i].v)) {
			++cnt;
			ans += E[i].d;
		}
	}
	cout << (cnt == n - 1 ? ans : -1) << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}