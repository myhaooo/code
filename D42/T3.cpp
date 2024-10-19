#include <bits/stdc++.h>

#define int long long
#define ls (o << 1)
#define rs (o << 1 | 1)

const int REN = 200000, MAXN = REN + 5;
const int INF = 0x3f3f3f3f3f3f;

using namespace std;

int n, m;
multiset<int> defense;

struct seg {
	int live_min, live_min_num, live_min_id, live_num, died_num, change_tag;
} t[MAXN << 2];

void pushup(int o) {
	if (t[ls].live_min == t[rs].live_min) {
		t[o].live_min = t[ls].live_min;
		t[o].live_min_num = t[ls].live_min_num + t[rs].live_min_num;
		t[o].live_min_id = t[ls].live_min_id;
	} else if (t[ls].live_min < t[rs].live_min) {
		t[o].live_min = t[ls].live_min;
		t[o].live_min_num = t[ls].live_min_num;
		t[o].live_min_id = t[ls].live_min_id;
	} else {
		t[o].live_min = t[rs].live_min;
		t[o].live_min_num = t[rs].live_min_num;
		t[o].live_min_id = t[rs].live_min_id;
	}
	t[o].live_num = t[ls].live_num + t[rs].live_num;
	t[o].died_num = t[ls].died_num + t[rs].died_num;
}

void down(int o, int k) {
	t[o].live_min += k;
	t[o].change_tag += k;
}

void pushdown(int o) {
	if (t[o].change_tag != 0) {
		down(ls, t[o].change_tag);
		down(rs, t[o].change_tag);
		t[o].change_tag = 0;
	}
}

void build(int o, int l, int r) {
	if (l == r) {
		cin >> t[o].live_min;
		t[o].live_min_num = 1;
		t[o].live_min_id = l;
		t[o].live_num = 1;
		t[o].died_num = 0;
		t[o].change_tag = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	pushup(o);
}

void change(int o, int l, int r, int L, int R, int k) {
	if (L <= l && r <= R) {
		down(o, k);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if (L <= mid) {
		change(ls, l, mid, L, R, k);
	}
	if (R > mid) {
		change(rs, mid + 1, r, L, R, k);
	}
	pushup(o);
}

array<int, 3> getmin(int o, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return { t[o].live_min, t[o].live_min_id, t[o].live_min_num };
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if (L <= mid && R > mid) {
		array<int, 3> A = getmin(ls, l, mid, L, R), B = getmin(rs, mid + 1, r, L, R);
		if (A[0] < B[0]) {
			return A;
		}
		if (A[0] > B[0]) {
			return B;
		}
		return { A[0], A[1], A[2] + B[2] };
	} else if (L <= mid) {
		return getmin(ls, l, mid, L, R);
	} else {
		return getmin(rs, mid + 1, r, L, R);
	}
}

void kill(int o, int l, int r, int p) {
	if (l == r) {
		t[o].died_num = 1;
		t[o].live_num = 0;
		t[o].live_min = INF;
		t[o].live_min_id = INF;
		t[o].live_min_num = 0;
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(o);
	if (p <= mid) {
		kill(ls, l, mid, p);
	} else {
		kill(rs, mid + 1, r, p);
	}
	pushup(o);
}

int getdied(int o, int l, int r, int L, int R) {
	if (L <= l && r <= R) {
		return t[o].died_num;
	}
	int mid = (l + r) >> 1, res = 0;
	pushdown(o);
	if (L <= mid) {
		res += getdied(ls, l, mid, L, R);
	}
	if (R > mid) {
		res += getdied(rs, mid + 1, r, L, R);
	}
	return res;
}

signed main() {
	freopen("simulator.in", "r", stdin);
	freopen("simulator.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int i, j, k;
	cin >> n;
	build(1, 1, n);
	defense.insert(n + 1);
	cin >> m;
	while (m--) {
		int op;
		cin >> op;
		if (op == 1) {
			int L, R, X;
			cin >> L >> R >> X;
			int lst = L - 1;
			while (lst <= R) {
				auto it = defense.upper_bound(lst);
				int x = *it;
				if (lst + 1 <= min(R, x - 1)) {
					change(1, 1, n, lst + 1, min(R, x - 1), -X);
				}
				if (x <= R) {
					defense.erase(it);
				}
				lst = x;
			}
			int cnt = R - L + 1 - getdied(1, 1, n, L, R);
			array<int, 3> tmp = getmin(1, 1, n, L, R);
			while (cnt && tmp[0] < 0) {
				cnt--;
				kill(1, 1, n, tmp[1]);
				tmp = getmin(1, 1, n, L, R);
			}
		}
		if (op == 2) {
			int L, R, x;
			cin >> L >> R >> x;
			change(1, 1, n, L, R, x);
		}
		if (op == 3) {
			int h;
			cin >> h;
			defense.insert(h);
		}
		if (op == 4) {
			int L, R;
			cin >> L >> R;
			cout << getdied(1, 1, n, L, R) << '\n';
		}
		if (op == 5) {
			int L, R;
			cin >> L >> R;
			array<int, 3> A = getmin(1, 1, n, L, R);
			if (A[0] == 0) {
				cout << A[2] << '\n';
			} else {
				cout << 0 << '\n';
			}
		}
	}
	return 0;
}

