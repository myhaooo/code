#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=260,M=N*N,INF=0x3f3f3f3f3f3f3f3f;
int n,m,s[N],dis[N][N];
int tot,head[N],nxt[M],ver[M];
int tot2,head2[N],nxt2[M],ver2[M];
bool vis[N][N];
bitset<N> bit[N][N];
struct Node
{
	int dat,x,y;
	bool friend operator < (Node x,Node y)
	{
		return x.dat>y.dat;
	} 
};
priority_queue<Node> q;
void add_edge(int x,int y)
{
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void add_edge2(int x,int y)
{
	ver2[++tot2]=y;
	nxt2[tot2]=head2[x];
	head2[x]=tot2;
}
void Dij()
{
	memset(dis,0x3f,sizeof(dis));
	dis[1][1]=s[1];	
	bit[1][1][1]=true;
	q.push((Node){dis[1][1],1,1});
	while(!q.empty())
	{
		int x=q.top().x,y=q.top().y;q.pop();
		if(vis[x][y])	continue;
		vis[x][y]=true;
		for(int i=head[x];i;i=nxt[i])
		{
			int to=ver[i],temp=0;
			if(!bit[x][y][to])	temp=s[to];
			if(dis[x][y]+temp<dis[to][y])
			{
				bit[to][y]=bit[x][y];
				bit[to][y][to]=true;
				dis[to][y]=dis[x][y]+temp;
				q.push((Node){dis[to][y],to,y});
			}
		}
		for(int i=head2[y];i;i=nxt2[i])
		{
			int to=ver2[i],temp=0;
			if(!bit[x][y][to])	temp=s[to];
			if(dis[x][y]+temp<dis[x][to])
			{
				bit[x][to]=bit[x][y];
				bit[x][to][to]=true;
				dis[x][to]=dis[x][y]+temp;
				q.push((Node){dis[x][to],x,to});
			}
		}
	}
}
signed main()
{
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=1,x,y;i<=m;i++)
	{
		cin>>x>>y;
		add_edge(x,y);
		add_edge2(y,x);
	}
	Dij();
	printf("%lld",dis[n][n]==INF?-1ll:dis[n][n]);
	return 0;
}