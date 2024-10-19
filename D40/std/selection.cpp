#include <bits/stdc++.h>
#define LL long long
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

inline int read() {
	char c = getchar();
	int x = 0;
	while (c < '0' || c > '9')
		c = getchar();
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + c - 48, c = getchar();
	return x;
}
const int mod = 998244353, maxn = 100005;

struct sode {
	int l, r, v;
} st[maxn], bl[maxn];

struct node {
	int l, r, x, v;
} A[maxn * 30], B[maxn * 30];

struct Seg {
	int l, r, v;
} seg[2][maxn];

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

inline int dqm(int x) {
	return x < 0 ? x + mod : x;
}

inline int qm(int x) {
	return x >= mod ? x - mod : x;
}

inline int cmp(const node &A, const node &B) {
	return A.v == B.v ? A.x < B.x : A.v < B.v;
}

inline int ctp(const node &A, const node &B) {
	return A.v == B.v ? A.x > B.x : A.v < B.v;
}
int n, a[maxn], top, sa, sb, lp, sz[2], ans, pre[maxn];
int l[maxn * 3], r[maxn * 3], tag[maxn * 3], d[maxn * 3];

inline void pushup(int i) {
	d[i] = qm(d[i << 1] + d[i << 1 | 1]);
}

inline void pushr(int i, int v) {
	tag[i] = v;
	d[i] = 1ll * (r[i] - l[i] + 1) * v % mod;
}

inline void pushdown(int i) {
	if (tag[i] == -1)
		return;
	pushr(i << 1, tag[i]);
	pushr(i << 1 | 1, tag[i]);
	tag[i] = -1;
}

void bud(int x, int y, int i) {
	l[i] = x, r[i] = y, tag[i] = -1;
	if (x == y)
		return;
	int mid = x + y >> 1;
	bud(x, mid, i << 1), bud(mid + 1, y, i << 1 | 1);
}

void chg(int x, int y, int v, int i) {
	if (x <= l[i] && y >= r[i]) {
		pushr(i, v);
		return;
	}
	int mid = l[i] + r[i] >> 1;
	pushdown(i);
	if (x <= mid)
		chg(x, y, v, i << 1);
	if (y > mid)
		chg(x, y, v, i << 1 | 1);
	pushup(i);
}

int qry(int x, int y, int i) {
	if (x <= l[i] && y >= r[i])
		return d[i];
	int mid = l[i] + r[i] >> 1;
	pushdown(i);
	return qm((x <= mid ? qry(x, y, i << 1) : 0) + (y > mid ? qry(x, y, i << 1 | 1) : 0));
}

inline void ins(int l, int r, int v, int o) {
	if (r > n)
		r = n;
	if (l < 1)
		l = 1;
	if (l > r)
		return;
	seg[o][++sz[o]] = (Seg) {
		l, r, v
	};
}

inline void calc(int l, int r, int v) {
	pre[l] = qm(pre[l] + v), pre[r + 1] = dqm(pre[r + 1] - v);
}

inline void solve(int L, int R) {
	int lst = 0, v = 0;
	sz[0] = sz[1] = 0;
	for (int i = L; i <= R; ++i) {
		chg(lst, A[i].x - 1, v, 1);
		ins(lst + 1, A[i].x, qm(v + 1), 0);
		lst = A[i].x;
		v = qm(v + qry(A[i].l - 1, A[i].r - 1, 1));
		v = qm(v + A[i].r - A[i].l + 1);
	}
	chg(lst, n, v, 1);
	ins(lst + 1, n + 1, qm(v + 1), 0);
	lst = n + 1, v = 0;
	int rp = lp;
	while (lp <= sb && B[lp].v == A[L].v)
		++lp;
	for (int i = rp; i < lp; ++i) {
		chg(B[i].x + 1, lst, v, 1);
		ins(B[i].x, lst - 1, qm(v + 1), 1);
		lst = B[i].x;
		v = qm(v + qry(B[i].l + 1, B[i].r + 1, 1));
		v = qm(v + B[i].r - B[i].l + 1);
	}
	chg(1, lst, v, 1);
	ans = qm(ans + v);
	ins(0, lst - 1, qm(v + 1), 1);
	std::reverse(seg[1], seg[1] + sz[1] + 1);
	int x, y;
	x = 0, y = 0;
	while (x <= sz[0] && y <= sz[1]) {
		calc(max(seg[0][x].l, seg[1][y].l), min(seg[0][x].r, seg[1][y].r), dqm(1ll * seg[0][x].v * seg[1][y].v % mod - 1));
		if (seg[0][x].r < seg[1][y].r)
			++x;
		else if (seg[0][x].r > seg[1][y].r)
			++y;
		else if (seg[0][x].r == seg[1][y].r)
			++y, ++x;
	}
}

int main() {
	freopen("selection.in", "r", stdin);
	freopen("selection.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= top; ++j)
			st[j].v = gcd(st[j].v, a[i]);
		st[++top] = (sode) {
			i, i, a[i]
		};
		int tot = 0, x = i, y = i;
		for (int j = top - 1; j >= 0; --j) {
			if (st[j].v != st[j + 1].v) {
				bl[++tot].l = x, bl[tot].r = y;
				bl[tot].v = st[j + 1].v;
				x = st[j].l, y = st[j].r;
			} else
				x = st[j].l;
		}
		top = 0;
		while (tot)
			st[++top] = bl[tot--];
		for (int j = 1; j <= top; ++j)
			A[++sa] = (node) {
			st[j].l, st[j].r, i, st[j].v
		};
	}
	top = 0;
	for (int i = n; i; i--) {
		for (int j = 1; j <= top; ++j)
			st[j].v = gcd(st[j].v, a[i]);
		st[++top] = (sode) {
			i, i, a[i]
		};
		int tot = 0, x = i, y = i;
		for (int j = top - 1; j >= 0; --j)
			if (st[j].v != st[j + 1].v) {
				bl[++tot].l = x, bl[tot].r = y;
				bl[tot].v = st[j + 1].v;
				x = st[j].l, y = st[j].r;
			} else
				y = st[j].r;
		top = 0;
		while (tot)
			st[++top] = bl[tot--];
		for (int j = 1; j <= top; ++j)
			B[++sb] = (node) {
			st[j].l, st[j].r, i, st[j].v
		};
	}
	std::sort(A + 1, A + sa + 1, cmp);
	std::sort(B + 1, B + sb + 1, ctp);
	int L = 1;
	lp = 1;
	bud(0, n + 1, 1);
	for (int i = 2; i <= sa + 1; ++i)
		if (A[i].v != A[i - 1].v)
			solve(L, i - 1), L = i;
	for (int i = 1; i <= n; i++)
		pre[i] = qm(pre[i - 1] + pre[i]);
	for (int i = 1; i <= n; i++)
		printf("%d ", dqm(ans - pre[i]));
	return 0;
}