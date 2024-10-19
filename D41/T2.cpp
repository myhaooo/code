#include <bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define f() cout<<"Pass"<<endl
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch > '9' || ch < '0') {
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
const int N = 5e3 + 10, M = 1e5 + 10, INF = 1e18;
int n, m, K, minn = INF, maxn;

int d1[10] = {0, 0, 0, 1, -1, 1, -1};
int d2[10] = {0, 1, -1, 0, 0, -1, 1};
queue<int> q;
bool vis[M];
vector<int> s[M], p[M];
pair<int, int> id;
int pos(int x, int y) {
	return (x - 1) * m + y;
}
bool check(int mid) {
	memset(vis, true, sizeof(vis));
	int sum = 0;
	while (!q.empty()) {
		q.pop();
	}
	for (int i = 1; i <= n; i++) {
		p[i] = s[i];
		for (int j = 1; j <= m; j++)
			q.push(make_pair(i, j));
	}
	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();
		vis[pos(x, y)] = false;
		int maxn = 0;
		for (int i = 1; i <= 6; i++) {
			int x2 = x + d1[i], y2 = y + d2[i];
			if (x2 <= 0 || y2 <= 0 || x2 > n || y2 > m)
				continue;
			maxn = max(maxn, p[x2][y2]);
		}
		if (maxn - p[x][y] > mid) {
			sum += maxn - p[x][y] - mid;
			p[x][y] = maxn - mid;
		}
		if (sum > K)
			return false;
		for (int i = 1; i <= 6; i++) {
			int x2 = x + d1[i], y2 = y + d2[i];
			if (x2 <= 0 || y2 <= 0 || x2 > n || y2 > m)
				continue;
			if (abs(p[x][y] - p[x2][y2]) > mid) {
				sum += p[x][y] - p[x2][y2] - mid;
				p[x2][y2] = p[x][y] - mid;
				if (!vis[pos(x2, y2)])
					q.push(make_pair(x2, y2)), vis[pos(x2, y2)] = true;
			}
		}
		if (sum > K)
			return false;
	}
	return sum <= K;
}
signed main() {
	n = read();
	m = read();
	K = read();
	for (int i = 1; i <= n; i++)
		s[i].push_back(0);
	for (int i = 1; i <= n; i++)
		for (int j = 1, x; j <= m; j++) {
			x = read();
			s[i].push_back(x);
			minn = min(minn, s[i][j]);
			if (maxn <= s[i][j])
				id = make_pair(i, j);
			maxn = max(maxn, s[i][j]);
		}
	int l = 0, r = maxn - minn, ans = maxn - minn;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			r = mid - 1;
			ans = mid;
		} else
			l = mid + 1;
	}
	printf("%lld", ans);
	return 0;
}