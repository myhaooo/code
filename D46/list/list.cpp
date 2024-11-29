#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10;
int n, m, a[N], pos[N];

struct node {
	int mi, sum;
} t[N << 2];

struct SegmentTree {
	void pushup(int x) {
		t[x].sum = t[x << 1].sum + t[x << 1 | 1].sum;
		t[x].mi = min(t[x << 1].mi, t[x << 1 | 1].mi - t[x << 1].sum);
	}
	void build(int x, int l, int r) {
		if (l == r) {
			t[x].mi = l, t[x].sum = 0;
			return;
		}
		int mid = l + r >> 1;
		build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
		pushup(x);
	}
	void update(int x, int l, int r, int p, int v) {
		if (l == r) {
			t[x].mi -= v, t[x].sum += v;
			return;
		}
		int mid = l + r >> 1;
		if (p <= mid)
			update(x << 1, l, mid, p, v);
		else
			update(x << 1 | 1, mid + 1, r, p, v);
		pushup(x);
	}
} T;

int main() {
	freopen("list.in", "r", stdin);
	freopen("list.out", "w", stdout);
	scanf("%d", &n), m = n << 1 | 1;
	for (int i = 1; i <= m; i++)
		scanf("%d", a + i);
	for (int i = 1; i <= m; i++)
		pos[a[i]] = min(i, m - i + 1);
	T.build(1, 1, n + 1);
	int ans = 0;
	for (int l = 1, r = 1; r <= m; r++) {
		T.update(1, 1, n + 1, pos[r], 1);
		while (t[1].mi < 0)
			T.update(1, 1, n + 1, pos[l++], -1);
		ans = max(ans, r - l + 1);
	}
	printf("%d\n", ans);
	return 0;
}
