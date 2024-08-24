#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m;
struct edge {
	int to, nxt;
} e[N << 1];
int head[N], tot;
inline void add(int u, int v) {
	e[++tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
bool vis[N];
int DEP[N << 1][20], dep[N], in[N], logg[N << 1], cnt;
inline void dfs(int u, int fath) {
	dep[u] = dep[fath] + 1;
	in[u] = ++cnt;
	DEP[in[u]][0] = dep[u];
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fath) continue;
		dfs(v, u);
		DEP[++cnt][0] = dep[u];
	}
}
inline int LCADEP(int u, int v) {
	u = in[u], v = in[v];
	if (u > v) swap(u, v);
	int k = logg[v - u + 1];
	return min(DEP[u][k], DEP[v - (1 << k) + 1][k]);
}
inline int DIS(int u, int v) {
	if (u == -1 || v == -1) return -1;
	return dep[u] + dep[v] - 2 * LCADEP(u, v);
}
#define ls rt << 1
#define rs rt << 1 | 1
struct tree {
	int u, v;
} t[N << 2];
inline void pushup(int rt) {
	if (t[ls].u == -1 && t[ls].v == -1) {
		t[rt] = t[rs];
		return ;
	}
	if (t[rs].u == -1 && t[rs].v == -1) {
		t[rt] = t[ls];
		return ;
	}
	if (DIS(t[ls].u, t[ls].v) > DIS(t[rs].u, t[rs].v)) t[rt] = t[ls];
	else t[rt] = t[rs];
	if (DIS(t[ls].u, t[rs].u) > DIS(t[rt].u, t[rt].v)) t[rt].u = t[ls].u, t[rt].v = t[rs].u;
	if (DIS(t[ls].u, t[rs].v) > DIS(t[rt].u, t[rt].v)) t[rt].u = t[ls].u, t[rt].v = t[rs].v;
	if (DIS(t[ls].v, t[rs].u) > DIS(t[rt].u, t[rt].v)) t[rt].u = t[ls].v, t[rt].v = t[rs].u;
	if (DIS(t[ls].v, t[rs].v) > DIS(t[rt].u, t[rt].v)) t[rt].u = t[ls].v, t[rt].v = t[rs].v;
}
inline tree add(tree a, tree b) {
	//cout << "add:\n";
	//cout << "a: " << a.u << " " << a.v << " b: " << b.u << " " << b.v << "\n";
	if (a.u == -1 && a.v == -1) return b;
	if (b.u == -1 && b.v == -1) return a;
	tree c;
	if (DIS(a.u, a.v) > DIS(b.u, b.v)) c = a;
	else c = b;
	//cout << "c: " << c.u << " " << c.v << "\n";
	if (DIS(a.u, b.u) > DIS(c.u, c.v)) c.u = a.u, c.v = b.u;
	if (DIS(a.u, b.v) > DIS(c.u, c.v)) c.u = a.u, c.v = b.v;
	if (DIS(a.v, b.u) > DIS(c.u, c.v)) c.u = a.v, c.v = b.u;
	if (DIS(a.v, b.v) > DIS(c.u, c.v)) c.u = a.v, c.v = b.v;
	return c;
}
inline void build(int rt, int l, int r) {
	if (l == r) {
		t[rt].u = t[rt].v = -1;
		return ;
	}
	int mid = l + r >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(rt);
}
inline void modify(int rt, int l, int r, int x) {
	if (x < l || x > r) return ;
	if (l == r) {
		if (t[rt].u == -1 && t[rt].v == -1) t[rt].u = t[rt].v = x;
		else t[rt].u = t[rt].v = -1;
		return ;
	}
	int mid = l + r >> 1;
	modify(ls, l, mid, x);
	modify(rs, mid + 1, r, x);
	pushup(rt);
}
inline tree query(int rt, int l, int r, int ql, int qr) {
	//cout << "begin: " << rt << " " << l << " " << r << " " << ql << " " << qr << "\n";
	if (ql > r || qr < l || l > r || ql > qr) return {-1, -1};
	if (ql <= l && r <= qr) {
		//cout << "return: " << rt << " " << t[rt].u << " " << t[rt].v << "\n";
		return t[rt];
	}
	int mid = l + r >> 1;
	tree ans = {-1, -1};
	ans = add(ans, query(ls, l, mid, ql, qr));
	//cout << rt << " ans: " << ans.u << " " << ans.v << "\n";
	ans = add(ans, query(rs, mid + 1, r, ql, qr));
	//cout << rt << " ans: " << ans.u << " " << ans.v << "\n";
	//cout << "end: " << rt << "\n";
	return ans;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1, u, v; i <= n - 1; i++) {
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	for (int i = 2; i <= cnt; i++) logg[i] = logg[i >> 1] + 1;
	for (int j = 1; j <= logg[cnt]; j++) {
		for (int i = 1; i + (1 << j) - 1 <= cnt; i++) {
			DEP[i][j] = min(DEP[i][j - 1], DEP[i + (1 << (j - 1))][j - 1]);
		}
	}

	build(1, 1, n);
	while (m--) {
		int opt, u, l, r;
		cin >> opt;
		if (opt == 1) {
			cin >> u;
			modify(1, 1, n, u);
		} else {
			cin >> l >> r;
			tree top;
			top = query(1, 1, n, l, r);
			cout << DIS(top.u, top.v) << "\n";
		}
	}
	return 0;
}