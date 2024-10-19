#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 3000 + 10;
struct edge {
	int v, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

void add(int u, int v) {
	e[++tot] = { v, head[u] }, head[u] = tot;
}

int p[MAXN], rk[MAXN], s[MAXN], c[MAXN];

struct node {
	int x, y, ts, tc, w, t;
} q[MAXN]; int cnt, res;

int find(int k) {
	return k == p[k] ? k : find(p[k]);
}

void merge(int x, int y) {
	if (rk[x = find(x)] > rk[y = find(y)]) swap(x, y);
	if (x == y) {
		q[++cnt] = { x, y, s[x], c[x], res, 0 };
		if (c[x] < s[x]) res++, c[x] = s[x] + 1;
		return ;
	}
	q[++cnt] = { x, y, s[y], c[y], res, rk[x] == rk[y] };
	res -= min(s[x], c[x]) + min(s[y], c[y]);
	p[x] = y, rk[x] == rk[y] && rk[y]++, s[y] += s[x], c[y] += c[x] + 1;
	res += min(s[y], c[y]);
}


void undo() {
	int x = q[cnt].x, y = q[cnt].y, t = q[cnt].t; res = q[cnt].w;
	p[x] = x, s[y] = q[cnt].ts, c[y] = q[cnt].tc, cnt--;
}

int a[MAXN], b[MAXN], ans[MAXN];


void dfs(int u, int f) {
	merge(a[u], b[u]), ans[u] = res;
	for (int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].v;
		if (v == f) continue; 
        dfs(v, u);
	}
	undo();
}

int n;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) p[i] = i, s[i] = 1;
	for (int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dfs(1, 0);
	for (int i = 2; i <= n; i++) printf("%d ", ans[i]);
}