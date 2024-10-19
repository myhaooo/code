#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define int long long 
using namespace std;
typedef long long int;
const int N = 4e3+10,M = 5e5+10;
const int LOGN = 20;
struct Node
{
	int x,y,v;
}a[M+1];

int n,m,q,now,fa[N][LOGN+2],val[N],dep[N];
vector<int>e[N];
int ls[N],rs[N],sum[N],c[N],dp[N];

int f[N];
void init(int x) {for(int i = 1;i<=x;i++) f[i] = i;}
int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}
void merge(int x, int y) {
	int u = find(x), v = find(y);
	if(u == v) return;
	f[u] = v;
}

bool cmp(Node x,Node y){
	return x.v > y.v;
}
void kruskalRebuildTree()
{
	init(2*n-1);
	sort(a+1, a+1+m,cmp);
	now = n;
	for(int i = 1;i<=m;i++) {
		int u = find(a[i].x), v = find(a[i].y), w = a[i].v;
		if(u != v) {
			val[++now] = w;
			merge(u, now);
			merge(v, now);
			ls[now] = u;
			rs[now] = v;
		}
	}
}


void dfs(int u)
{
	if(!ls[u]||!rs[u])
	{
		sum[u] = c[u];
		dp[u] = INF;
		return;
	}
	dfs(ls[u]),dfs(rs[u]);
	sum[u] = sum[ls[u]] + sum[rs[u]];
	//               先吃ls[u]
	dp[u] = max(min(dp[rs[u]],val[u])-sum[ls[u]],min(dp[ls[u]],val[u])-sum[rs[u]]);
}


main()
{
	cin>>n>>m;
	for(int i = 1;i<=n;i++)cin>>c[i];
	for(int i = 1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].y>>a[i].v;
	}
	kruskalRebuildTree();
	dfs(now);
	if(dp[now]<=0)
		cout<<-1<<"\n";
	else cout<<dp[now]<<"\n";
	
	return 0;
}