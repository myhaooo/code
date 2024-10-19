#include<bits/stdc++.h>
using namespace std;

const int MAXN=3e5+5;
struct EDGE
{
	int u,v,w;
}edge[MAXN];
set<int>s[MAXN];
int fa[MAXN],p[MAXN],tot;
int cnt[MAXN],sum=0;
bool ans[MAXN];

int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}
void add(int x,int y){s[x].insert(y);}
void erase(int x,int y){s[x].erase(y);}

void del(int x)
{
	if(s[x].size()<=2 && !cnt[x])
	{
		--sum;
		int tmp[3],len=0;
		for(auto y:s[x]) tmp[++len]=y;
		s[x].clear();
		for(int i=1;i<=len;++i)
		{
			for(int j=1;j<=len;++j) if(i!=j) add(tmp[i],tmp[j]);
			erase(tmp[i],x);
		}
		for(int i=1;i<=len;++i) del(tmp[i]);
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout); 
	int n;
	cin>>n;
	for(int i=1;i<=n;++i) fa[i]=i;
	int u,v,w;
	for(int i=1;i<n;++i)
	{
		cin>>u>>v>>w;
		edge[i]=(EDGE){u,v,w};
		if(!w) fa[getfa(u)]=getfa(v);
	}
	for(int i=1;i<n;++i) if(edge[i].w) add(getfa(edge[i].u),getfa(edge[i].v)),add(getfa(edge[i].v),getfa(edge[i].u));
	for(int i=1;i<=n;++i) cin>>p[i],++cnt[getfa(p[i])];
	for(int i=n;i>=1;--i)
	{
		ans[i]=(!sum);
		if(--cnt[getfa(p[i])]==0) ++sum,del(getfa(p[i]));
	}
	for(int i=1;i<=n;++i) cout<<ans[i];
	return 0;
}
