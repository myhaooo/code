#include <bits/stdc++.h>
#define ll long long
#define mod 1000000007
using namespace std;
const int N = 5005;
int n, d[N], dep[N], son[N];
vector<int> e[N];
ll *f[N], *g[N], p[N<<2], *o = p, ans;

void dfs(int x, int fa) {
	d[x] = d[fa] + 1;
	for (auto y : e[x])
		if (y != fa) {
			dfs(y, x);
			if (dep[y] > dep[son[x]]) son[x] = y;
		}
	dep[x] = dep[son[x]] + 1;
}

void dp(int x, int fa) {
	if (son[x])
		f[son[x]] = f[x] + 1, g[son[x]] = g[x] - 1, dp(son[x], x);
	f[x][0] = 1, ans += g[x][0];
	for (auto y : e[x])
		if (y != fa && y != son[x]) {
			f[y] = o, o += dep[y] << 1, g[y] = o, o += dep[y] << 1;
			dp(y, x);
			for (int i = 0; i < dep[y]; i++) {
				if (i) ans += f[x][i-1] * g[y][i];
				ans += g[x][i+1] * f[y][i];
			}
			for (int i = 0; i < dep[y]; i++) {
				g[x][i+1] += f[x][i+1] * f[y][i];
				if (i) g[x][i-1] += g[y][i];
				f[x][i+1] += f[y][i];
			}
		}
}

int main() {
	cin>>n;
	for (int i = 1, x, y; i < n; i++){
        cin>>x>>y;
        e[x].push_back(y), e[y].push_back(x);
    }
		
	dfs(1, 0), f[1] = o, o += dep[1] << 1, g[1] = o, o += dep[1] << 1;
	dp(1, 0), cout<<ans<<"\n";
	return 0;
}