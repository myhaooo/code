#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

typedef long long ll;
typedef unsigned ui;
constexpr int max_n = 200000, max_lgn = 18;

struct nd
{
	int l, r; ui v;
}
tr[(1 << (max_lgn + 1)) + (max_lgn + 1) * max_n];
int a[max_n], b[max_n], grt[max_n + 1], ind = 0;
ui rv[max_n];

inline int nnode(ui val = 0)
{
	tr[ind].l = tr[ind].r = -1;
	tr[ind].v = val;
	return ind++;
}

int build(int l, int r)
{
	int id = nnode();
	if (l < r)
	{
		int mid = (l + r) >> 1;
		tr[id].l = build(l, mid);
		tr[id].r = build(mid + 1, r);
	}
	return id;
}

int modify(int rt, int l, int r, int pos, int val)
{
	if (l == r)
		return nnode(tr[rt].v ^ val);
	int mid = (l + r) >> 1, id = ind++;
	tr[id] = tr[rt];
	
	if (pos <= mid)
		tr[id].l = modify(tr[rt].l, l, mid, pos, val);
	else
		tr[id].r = modify(tr[rt].r, mid + 1, r, pos, val);
	
	tr[id].v = (tr[tr[id].l].v ^ tr[tr[id].r].v);
	return id;
}

int query(int l, int r, int lrt, int rrt)
{
	if ((tr[rrt].v ^ tr[lrt].v) == 0)
		return r + 1;
	if (l == r)
		return l;
	int mid = (l + r) >> 1, lrs = query(l, mid, tr[lrt].l, tr[rrt].l);
	
	if (lrs != mid + 1)
		return lrs;
	return query(mid + 1, r, tr[lrt].r, tr[rrt].r);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
	
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b, b + n);
	int m = unique(b, b + n) - b;
	for (int i = 0; i < m; i++)
		rv[i] = rnd();
	
	grt[0] = build(0, m - 1);
	for (int i = 0; i < n; i++)
	{
		int pos = lower_bound(b, b + m, a[i]) - b;
		grt[i + 1] = modify(grt[i], 0, m - 1, pos, rv[pos]);
	}
	
	int q, l, r, lastans = 0;
	
	cin >> q;
	while (q--)
	{
		cin >> l >> r;
		l ^= lastans, r ^= lastans;
		
		int res = query(0, m - 1, grt[l - 1], grt[r]);
		cout << (lastans = (res < m ? b[res] : 0)) << "\n";
	}
	
	return 0;
}
