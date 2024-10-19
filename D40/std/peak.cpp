#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)

#define N 100007

#define ls (rt << 1)
#define rs (rt << 1 | 1)
#define mid ((l + r) / 2)

ll a[N], b[N];

struct SEG1 {
	bool tag[N << 2][3];
	void build(int rt, int l, int r) {
		if (l == r) {
			tag[rt][0] = (b[l] == 0);
			tag[rt][1] = (b[l] > 0);
			tag[rt][2] = (b[l] < 0);
			return;
		}
		build(ls, l, mid);
		build(rs, mid + 1, r);
		rep(i, 0, 2) tag[rt][i] = tag[ls][i] && tag[rs][i];
	}
	void upd(int rt, int l, int r, int p) {
		if (l == r) {
			tag[rt][0] = (b[l] == 0);
			tag[rt][1] = (b[l] > 0);
			tag[rt][2] = (b[l] < 0);
			return;
		}
		p <= mid ? upd(ls, l, mid, p) : upd(rs, mid + 1, r, p);
		rep(i, 0, 2) tag[rt][i] = tag[ls][i] && tag[rs][i];
	}
	bool query(int rt, int l, int r, int L, int R, int op) {
		if (L <= l && r <= R) return tag[rt][op];
		bool ret = true;
		if (L <= mid) ret = ret && query(ls, l, mid, L, R, op);
		if (R > mid) ret = ret && query(rs, mid + 1, r, L, R, op);
		return ret;
	}
} seg1;

pair<ll, int> max(pair<ll, int> a, pair<ll, int> b) {
	if (a.first > b.first) return a;
	return b;
}

struct SEG2 {
	int mxpos[N << 2];
	ll mx[N << 2], tag[N << 2];
	void pushdown(int rt) {
		if (tag[rt]) {
			mx[ls] += tag[rt];
			mx[rs] += tag[rt];
			tag[ls] += tag[rt];
			tag[rs] += tag[rt];
			tag[rt] = 0;
		}
	}
	void pushup(int rt) {
		if (mx[ls] > mx[rs]) {
			mx[rt] = mx[ls]; 
			mxpos[rt] = mxpos[ls];
		} else {
			mx[rt] = mx[rs]; 
			mxpos[rt] = mxpos[rs];
		}
	}
	void build(int rt, int l, int r) {
		tag[rt] = 0;
		if (l == r) {
			mx[rt] = a[l];
			mxpos[rt] = l;
			return;
		}
		build(ls, l, mid);
		build(rs, mid + 1, r);
		pushup(rt);
	}
	void upd(int rt, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R) {
			mx[rt] += x;
			tag[rt] += x;
			return;
		}
		pushdown(rt);
		if (L <= mid) upd(ls, l, mid, L, R, x);
		if (R > mid) upd(rs, mid + 1, r, L, R, x);
		pushup(rt);
	}
	pair<ll, int> maxpos(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) return make_pair(mx[rt], mxpos[rt]);
		pushdown(rt);
		pair<ll, int> ret = {-1e18, 0};
		if (L <= mid) ret = max(ret, maxpos(ls, l, mid, L, R));
		if (R > mid) ret = max(ret, maxpos(rs, mid + 1, r, L, R));
		return ret;
	}
} seg2;

int main() {
	freopen("peak.in", "r", stdin);
	freopen("peak.out", "w", stdout);
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n; cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 2, n) b[i] = a[i] - a[i - 1];
	seg1.build(1, 2, n);
	seg2.build(1, 1, n);
	int q; cin >> q;
	rep(i, 1, q) {
		int op, l, r; 
		cin >> op >> l >> r;
		if (op == 1) {
			int x; cin >> x;
			b[l] += x;
			b[r + 1] -= x;
			seg1.upd(1, 2, n, l);
			seg2.upd(1, 1, n, l, r, x);
			if (r + 1 <= n) seg1.upd(1, 2, n, r + 1);
		} else if (op <= 4) {
			if (l == r) cout << 1 << endl;
			else cout << seg1.query(1, 2, n, l + 1, r, op - 2) << endl;
		} else {
			int pos = seg2.maxpos(1, 1, n, l, r).second;
			if (pos == l || pos == r) {cout << 0 << endl; continue;}
			bool resl = seg1.query(1, 2, n, l + 1, pos, 1);
			bool resr = seg1.query(1, 2, n, pos + 1, r, 2);
			cout << (resl && resr) << endl;
		}
	}
	return 0;
}