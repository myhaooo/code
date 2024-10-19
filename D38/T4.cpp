#include<bits/stdc++.h>
#define rg register
#define qwq 0
using namespace std;
const int N = 1e5 + 3;
int n;
int fa[N];
inline int find(int x) {
	if (fa[x] ^ x) fa[x] = find(fa[x]);
	return fa[x];
}
inline void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x ^ y) fa[x] = y;
}
struct jux {
	int x, y, xx, yy;
	bool operator<(const jux& tmp) const { return y < tmp.y; }
} ju[N];
struct Segment_Tree {
	#define ls rt << 1
	#define rs rt << 1 | 1
	struct Tree {
		int id, lim;  //当前被哪个矩形覆盖，上界是多少 
		bool typ, tag;  //是否只被一个矩形覆盖（0为是1为否），懒标记 
	} t[N << 2];
	void pushup(int rt) {
		if (t[ls].id == t[rs].id) {  //如果左右子区间都被同一个矩形完全覆盖则当前区间被同一个矩形完全覆盖 
			t[rt].id = t[ls].id;
			t[rt].lim = t[ls].lim;
			t[rt].typ = false;
		} else t[rt].typ = true;
		if (t[ls].typ || t[rs].typ) t[rt].typ = true;  //如果左右子区间有被多个矩形覆盖的，则当前区间一定被多个矩形覆盖 
	}
	void pushdown(int rt) {
		if (!t[rt].tag) return ;
		t[ls].tag = t[rs].tag = true;
		t[ls].id = t[rs].id = t[rt].id;
		t[ls].lim = t[rs].lim = t[rt].lim;
		t[rt].tag = false;
	}
	void modify(int rt, int l, int r, int ql, int qr, int lim, int id) {
		if (ql <= l && r <= qr && !t[rt].typ) {  //注意判断该区间是否只被一个矩形覆盖 
			if (t[rt].lim > lim) return ;
			//如果当前矩形的上界更高则更新 
			t[rt].tag = true;
			t[rt].id = id;
			t[rt].lim = lim;
			return ;
		}
		pushdown(rt);
		rg int mid = l + r >> 1;
		if (ql <= mid) modify(ls, l, mid, ql, qr, lim, id);
		if (qr > mid) modify(rs, mid + 1, r, ql, qr, lim, id);
		pushup(rt);
	}
	void Merge(int rt, int l, int r, int ql, int qr, int lim, int id) {
		if (ql <= l && r <= qr && !t[rt].typ) {  //注意判断该区间是否只被一个矩形覆盖 
			if (t[rt].lim >= lim) merge(id, t[rt].id);  //如果当前矩形的下边低于区间上界则两矩形相交，合并
			return ;
		}
		pushdown(rt);
		rg int mid = l + r >> 1;
		if (ql <= mid) Merge(ls, l, mid, ql, qr, lim, id);
		if (qr > mid) Merge(rs, mid + 1, r, ql, qr, lim, id);
		pushup(rt);
	}
} ST;
int ans;
bool vis[N];
int main() {
	freopen("jux.in", "r", stdin);
	freopen("jux.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (rg int i = 1, x, y, xx, yy; i <= n; i++) {
		cin >> x >> y >> xx >> yy;
		ju[i] = {x, y, xx, yy};
	}
	sort(ju + 1, ju + n + 1);
	for (rg int i = 1; i <= n; i++) fa[i] = i;
	for (rg int i = 1; i <= n; i++) {
		//先对当前矩形的下边进行查询合并，再去更新区间 
		ST.Merge(1, 1, 1e5, ju[i].x, ju[i].xx, ju[i].y, i);
		ST.modify(1, 1, 1e5, ju[i].x, ju[i].xx, ju[i].yy, i);
	}
	for (rg int i = 1; i <= n; i++) {
		rg int fi = find(i);
		if (!vis[fi]) {
			ans++;
			vis[fi] = true;
		}
	}
	cout << ans << "\n";
	return qwq;
}

