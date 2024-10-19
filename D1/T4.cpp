#include<bits/stdc++.h>
#define lid id<<1
#define rid id<<1|1
using namespace std;
int n,m,a[100005],head[100005],edgenum;
struct edge{
	int to,nxt;
}e[200005];
void add_edge(int u,int v)
{
	e[++edgenum].nxt=head[u];
	e[edgenum].to=v;
	head[u]=edgenum;
}
int in[100005],out[100005],tot,f[100005];
bool vis[100005];
void dfs(int u,int fa)
{
	in[u]=++tot;
	f[u]=fa;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs(v,u);
	}
	out[u]=tot;
}
struct seg_tree{
	int l,r,mx,lazy;
}tr[1600005];
void build(int id,int l,int r)
{
	tr[id].l=l,tr[id].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(lid,l,mid);
	build(rid,mid+1,r);
}
void pushdown(int id)
{
	tr[lid].lazy=max(tr[id].lazy,tr[lid].lazy);
	tr[lid].mx=max(tr[id].lazy,tr[lid].mx);
	tr[rid].lazy=max(tr[id].lazy,tr[rid].lazy);
	tr[rid].mx=max(tr[id].lazy,tr[rid].mx);
	tr[id].lazy=0;
}
void update(int id,int l,int r,int x)
{
	if(l>r) return;
	if(tr[id].l==l&&tr[id].r==r)
	{
		tr[id].mx=max(tr[id].mx,x);
		tr[id].lazy=max(tr[id].lazy,x);
		return;
	}
	pushdown(id);
	int mid=(tr[id].l+tr[id].r)>>1;
	if(mid>=r) update(lid,l,r,x);
	else if(mid<l) update(rid,l,r,x);
	else update(lid,l,mid,x),update(rid,mid+1,r,x);
	tr[id].mx=max(tr[lid].mx,tr[rid].mx);
}
int query(int id,int c)
{
	if(tr[id].l==tr[id].r)
	{
		return tr[id].mx;
	}
	pushdown(id);
	int mid=(tr[id].l+tr[id].r)>>1;
	if(c<=mid) return query(lid,c);
	else return query(rid,c);
}
void add(int x)
{
	int fa=f[x];
	while(fa)
	{
		update(1,in[fa],in[x]-1,a[fa]);
	//	printf("%d %d %d\n",in[fa],in[x]-1,a[fa]);
		update(1,out[x]+1,out[fa],a[fa]);
	//	printf("%d %d %d\n",out[x]+1,out[fa],a[fa]);
		if(vis[x]) break;
		vis[x]=1;
		x=fa,fa=f[x];
	}
}
int main()
{
//	freopen("lca2.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	build(1,1,n);
//	for(int i=1;i<=n;i++)
//	{
//		printf("%d %d\n",in[i],out[i]);
//	}
	int cnt=0;
	while(m--)
	{
		string opt;
		cin>>opt;
		int x;
		scanf("%d",&x);
		if(opt=="Query")
		{
			if(cnt<1) printf("-1\n");
			else
			{
				printf("%d\n",query(1,in[x]));
			}
		}
		else
		{
			cnt++;
			update(1,in[x],out[x],a[x]);
	//		printf("%d %d %d\n",in[x]+1,out[x],a[x]);
			add(x);
		}
	}
	return 0;
}
