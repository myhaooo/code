#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
#define N 200010
#define ll long long
#define fir first
#define sec second
#define make make_pair
// #define int long long

int n, m;
int **mat, **w;
pair<int, int> rk[N];
const ll mod = 998244353;
inline void md(ll &a, ll b)
{
	a += b;
	a = a >= mod ? a - mod : a;
}
ll mins[N << 2], ans;
int tl[N << 2], tr[N << 2], minf[N << 2], minc[N << 2], tag[N << 2];
#define tl(p) tl[p]
#define tr(p) tr[p]
#define minf(p) minf[p]
#define minc(p) minc[p]
#define mins(p) mins[p]
#define tag(p) tag[p]
void pushup(int p)
{
	minf(p) = min(minf(p << 1), minf(p << 1 | 1));
	minc(p) = mins(p) = 0;
	if (minf(p << 1) == minf(p))
	{
		minc(p) += minc(p << 1);
		md(mins(p), mins(p << 1));
	}
	if (minf(p << 1 | 1) == minf(p))
	{
		minc(p) += minc(p << 1 | 1);
		md(mins(p), mins(p << 1 | 1));
	}
}
void spread(int p)
{
	minf(p << 1) += tag(p);
	tag(p << 1) += tag(p);
	minf(p << 1 | 1) += tag(p);
	tag(p << 1 | 1) += tag(p);
	tag(p) = 0;
}
void build(int p, int l, int r)
{
	tl(p) = l;
	tr(p) = r;
	minf(p) = INF;
	if (l == r)
	{
		minf(p) = INF;
		minc(p) = 1;
		mins(p) = l - 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void upd(int p, int pos, int dat)
{
	if (tl(p) == tr(p))
	{
		minf(p) = dat;
		return;
	}
	if (tag(p))
		spread(p);
	int mid = (tl(p) + tr(p)) >> 1;
	if (pos <= mid)
		upd(p << 1, pos, dat);
	else
		upd(p << 1 | 1, pos, dat);
	pushup(p);
}
void upd(int p, int l, int r, int dat)
{
	if (l <= tl(p) && r >= tr(p))
	{
		minf(p) += dat;
		tag(p) += dat;
		return;
	}
	if (tag(p))
		spread(p);
	int mid = (tl(p) + tr(p)) >> 1;
	if (l <= mid)
		upd(p << 1, l, r, dat);
	if (r > mid)
		upd(p << 1 | 1, l, r, dat);
	pushup(p);
}
void query(int p)
{
	if (tl(p) == tr(p))
	{
		printf("%d ", minf(p));
		return;
	}
	if (tag(p))
		spread(p);
	query(p << 1);
	query(p << 1 | 1);
	if (p == 1)
		printf("\n");
}
void calc(int r, int x1, int x2, int x3)
{
	// if (r==4) cout<<"calc: "<<r<<' '<<x1<<' '<<x2<<' '<<x3<<endl;
	int t[5] = {0, r, x1, x2, x3};
	sort(t, t + 5);
	// if (r==4) {cout<<"t: "; for (int i=0; i<4; ++i) cout<<t[i]<<' '; cout<<endl;}
	if (t[1] == r)
	{
		if (r > 1)
			upd(1, 1, r - 1, 1);
		return;
	}
	int pos = 1, base = 1;
	while (t[pos] != r)
		++pos;
	--pos;
	// cout<<"pos: "<<pos<<endl;
	for (; pos; ++base, --pos)
	{
		if (base == 1)
		{
			upd(1, t[pos - 1] + 1, t[pos], -1); //, cout<<"go cge: "<<t[pos-1]+1<<' '<<t[pos]<<' '<<-1<<endl;
			if (t[pos] + 1 <= t[pos + 1] - 1)
				upd(1, t[pos] + 1, t[pos + 1] - 1, 1);
		}
		else if (base == 2)
			upd(1, t[pos - 1] + 1, t[pos], 1); //, cout<<"go cge: "<<t[pos-1]+1<<' '<<t[pos]<<' '<<1<<endl;
		else if (base == 3)
			upd(1, t[pos - 1] + 1, t[pos], -1); //, cout<<"go cge: "<<t[pos-1]+1<<' '<<t[pos]<<' '<<-1<<endl;
		else
			puts("error");
	}
	// if (r==4) cout<<endl;
}
void solve()
{
	// memset(minf, 127, sizeof(minf));
	build(1, 1, n * m);
	for (int i = 1, x, y; i <= n * m; ++i)
	{
		// cout<<"i: "<<i<<endl;
		upd(1, i, 4);
		// query(1);
		x = rk[i].fir, y = rk[i].sec;
		calc(i, w[x - 1][y], w[x][y - 1], w[x - 1][y - 1]);
		calc(i, w[x - 1][y], w[x][y + 1], w[x - 1][y + 1]);
		calc(i, w[x + 1][y], w[x][y - 1], w[x + 1][y - 1]);
		calc(i, w[x + 1][y], w[x][y + 1], w[x + 1][y + 1]);
		/// query(1);
		// cout<<"minf: "<<minf(1)<<endl;
		if (minf(1) == 4)
		{
			ans = (ans + 1ll * i * minc(1) - mins(1)) % mod;
			// cout<<"ans: "<<ans<<endl;
			// cout<<"minc: "<<minc(1)<<endl;
			// cout<<"mins: "<<mins(1)<<endl;
		}
		else
			ans = (ans + 1) % mod;
		// cout<<endl;
	}
	printf("%lld\n", ans);
	exit(0);
}

signed main()
{
	freopen("pig.in", "r", stdin);
	freopen("pig.out", "w", stdout);

	cin >> n >> m;
	if (n <= m)
	{
		w = new int *[n + 5];
		for (int i = 0; i <= n + 1; ++i)
		{
			w[i] = new int[m + 5];
			memset(w[i], 127, sizeof(int) * (m + 5));
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
			{
				cin >> w[i][j];
				rk[w[i][j]] = make(i, j);
			}
	}
	else
	{
		mat = new int *[n + 5];
		w = new int *[m + 5];
		for (int i = 0; i <= n + 1; ++i)
			mat[i] = new int[m + 5];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				cin >> mat[i][j];
		for (int i = 0; i <= m + 1; ++i)
		{
			w[i] = new int[n + 5];
			memset(w[i], 127, sizeof(int) * (n + 5));
		}
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= n; ++j)
			{
				w[i][j] = mat[j][i];
				rk[w[i][j]] = make(i, j);
			}
		swap(n, m);
	}
	task::solve();

	return 0;
}
