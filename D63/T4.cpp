#include<bits/stdc++.h>
#define x first
#define y second
// #define int long long 
const int N = 40010, M = 16384;
using namespace std;
typedef pair<int, int>PII;
int n, m, a[N], b[N], id[N], now, fa[N], sz[N], son[N];
long long dp[16][M], ans[N];
vector<int>g[N];

void dfs1(int u)
{
	son[u] = 0;
	sz[u] = 1;
	for(auto j : g[u])
	{
		dfs1(j);
		sz[u] += sz[j];
		if(sz[son[u]] < sz[j]) son[u] = j;
	}
}

void dfs2(int u, int dep, int sxor)
{
	ans[u] = dp[dep][sxor];
	for(auto j : g[u])
		if(j != son[u])
		{
			for(int i = 0; i < M; i ++ )
				dp[dep + 1][i] = min(dp[dep][i], dp[dep][i ^ a[j]] + b[j]);
			dfs2(j, dep + 1, sxor ^ a[j]);
		}
	if(son[u]) 
	{
		for(int i = 0; i < M; i ++ )
				dp[dep][i] = min(dp[dep][i], dp[dep][i ^ a[son[u]]] + b[son[u]]);
		dfs2(son[u], dep, sxor ^ a[son[u]]);
	}
}

signed main()
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin >> m;
	now = 1, n = 1;
	for(int i = 1; i <= m; i ++ )
	{
		string s;
		cin >> s;
		if(s == "ADD")
		{
			n ++;
			cin >> a[n] >> b[n];
			g[now].push_back(n);
			fa[n] = now;
			now = n;
		}
		else now = fa[now];
		id[i] = now;
	}

	dfs1(1);
	for(int i = 1; i < M; i ++ ) dp[0][i] = 1e18;
	dfs2(1, 0, 0);
	for(int i = 1; i <= m; i ++ ) cout << ans[id[i]] << '\n';
}

