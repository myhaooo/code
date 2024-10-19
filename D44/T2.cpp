#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int maxn = 200005;
int n, m, c;
int a[maxn], b[maxn];
vector<int> v;

int t[maxn];

int lowbit(int u) {
	return u & (-u);
}

void update(int u, int w) {
	for (int i = u; i <= c; i += lowbit(i))
		t[i] += w;
}

int query(int u) {
	int w = 0;
	for (int i = u; i; i -= lowbit(i))
		w += t[i];
	return w;
}

int main() {
	ios::sync_with_stdio(false);
    #ifndef LOCAL
    #define NDEBUG
    	cin.tie(0), cout.tie(0);
    #define file(a)                               \
    	FILE *FI = freopen(#a ".in", "r", stdin); \
    	FI = freopen(#a ".out", "w", stdout)
    	file(cardgame);
    #else
    #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
    #endif
    	freopen("in.in", "r", stdin);
    	freopen("out.out", "w", stdout);
    	// #include "../local.h"
    #endif
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> a[i], v.push_back(a[i]);
	for (int i = 0; i < m; ++i)
		cin >> b[i], v.push_back(b[i]);
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (int i = 0; i < n; ++i)
		a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
	for (int i = 0; i < m; ++i)
		b[i] = lower_bound(v.begin(), v.end(), b[i]) - v.begin() + 1;

	c = v.size();
	int p = __gcd(n, m);
	ll win = 0, draw = 0;
	for (int r = 0; r < p; ++r) {
		for (int i = r; i < m; i += p)
			update(b[i], 1);
		for (int i = r; i < n; i += p) {
			int new_win = query(a[i] - 1);
			int new_draw = query(a[i]) - new_win;
			win += new_win, draw += new_draw;
		}
		for (int i = r; i < m; i += p)
			update(b[i], -1);
	}
	win *= p, draw *= p;
	ll lose = 1ll * n * m - win - draw;
	cout << win << '\n' << lose << '\n' << draw << '\n';
	return 0;
}