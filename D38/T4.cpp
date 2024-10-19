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
		int id, lim;  //��ǰ���ĸ����θ��ǣ��Ͻ��Ƕ��� 
		bool typ, tag;  //�Ƿ�ֻ��һ�����θ��ǣ�0Ϊ��1Ϊ�񣩣������ 
	} t[N << 2];
	void pushup(int rt) {
		if (t[ls].id == t[rs].id) {  //������������䶼��ͬһ��������ȫ������ǰ���䱻ͬһ��������ȫ���� 
			t[rt].id = t[ls].id;
			t[rt].lim = t[ls].lim;
			t[rt].typ = false;
		} else t[rt].typ = true;
		if (t[ls].typ || t[rs].typ) t[rt].typ = true;  //��������������б�������θ��ǵģ���ǰ����һ����������θ��� 
	}
	void pushdown(int rt) {
		if (!t[rt].tag) return ;
		t[ls].tag = t[rs].tag = true;
		t[ls].id = t[rs].id = t[rt].id;
		t[ls].lim = t[rs].lim = t[rt].lim;
		t[rt].tag = false;
	}
	void modify(int rt, int l, int r, int ql, int qr, int lim, int id) {
		if (ql <= l && r <= qr && !t[rt].typ) {  //ע���жϸ������Ƿ�ֻ��һ�����θ��� 
			if (t[rt].lim > lim) return ;
			//�����ǰ���ε��Ͻ��������� 
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
		if (ql <= l && r <= qr && !t[rt].typ) {  //ע���жϸ������Ƿ�ֻ��һ�����θ��� 
			if (t[rt].lim >= lim) merge(id, t[rt].id);  //�����ǰ���ε��±ߵ��������Ͻ����������ཻ���ϲ�
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
		//�ȶԵ�ǰ���ε��±߽��в�ѯ�ϲ�����ȥ�������� 
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

