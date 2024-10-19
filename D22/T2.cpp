#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,P=998244353;

int n,m,cnt=1,tot;
int head[N],dep[N],top[N],faz[N],siz[N],son[N],x[N],y[N],opt[N],v[N],idx[N],ans[N],f[N],e1[N],e2[N];
bool vis[N];
struct Edge{
	int v,to;
}e[N<<1];

void add(int x,int y){
	e[cnt].to=head[x];
	e[cnt].v=y;
	head[x]=cnt++;
	return ;
}

void dfs1(int x,int fa){
	dep[x]=dep[fa]+1;
	faz[x]=fa;
	siz[x]=1;
	for(int i=head[x];i;i=e[i].to){
		int y=e[i].v;
		if(y==fa)continue;
		dfs1(y,x);
		if(siz[y]>siz[son[x]])son[x]=y;
		siz[x]+=siz[y];
	}
	return ;
}

void dfs2(int x,int rt){
	top[x]=rt;
	if(son[x])dfs2(son[x],rt);
	for(int i=head[x];i;i=e[i].to){
		int y=e[i].v;
		if(y==faz[x]||y==son[x])continue;
		dfs2(y,y);
	}
	return ;
}

int Lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=faz[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}

int dis(int x,int y){
	return dep[x]+dep[y]-(dep[Lca(x,y)]<<1);
}

int Find(int x){
	if(f[x]==x)return x;
	return f[x]=Find(f[x]);
}

void Merge(int x,int y){
	int p1=0,p2=0,d=-1,tmp;
	if((tmp=dis(e1[x],e2[x]))>d){
		d=tmp;
		p1=e1[x],p2=e2[x];
	}
	if((tmp=dis(e1[y],e2[y]))>d){
		d=tmp;
		p1=e1[y],p2=e2[y];
	}
	if((tmp=dis(e1[x],e1[y]))>d){
		d=tmp;
		p1=e1[x],p2=e1[y];
	}
	if((tmp=dis(e1[x],e2[y]))>d){
		d=tmp;
		p1=e1[x],p2=e2[y];
	}
	if((tmp=dis(e2[x],e1[y]))>d){
		d=tmp;
		p1=e2[x],p2=e1[y];
	}
	if((tmp=dis(e2[x],e2[y]))>d){
		d=tmp;
		p1=e2[x],p2=e2[y];
	}
	f[y]=x;
	e1[x]=p1,e2[x]=p2;
	return ;
}

int main(){
	cin>>n>>m;
	for(int i=1;i<n;i++){
		cin>>x[i]>>y[i];
		add(x[i],y[i]);
		add(y[i],x[i]);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=m;i++){
		cin>>opt[i]>>v[i];
		if(opt[i]==1)vis[v[i]]=true;
		else idx[i]=++tot;
	}
	for(int i=1;i<=n;i++)f[i]=e1[i]=e2[i]=i;
	for(int i=1;i<n;i++){
		if(!vis[i]){
			int a=x[i],b=y[i];
			int A=Find(a),B=Find(b);
			Merge(A,B);
		}
	}
	for(int i=m;i>=1;i--){
		switch(opt[i]){
			case 1:{
				int a=x[v[i]],b=y[v[i]];
				int A=Find(a),B=Find(b);
				Merge(A,B);
				break;
			}case 2:{
				int F=Find(v[i]);
				ans[idx[i]]=max(dis(v[i],e1[F]),dis(v[i],e2[F]));
				break;
			}
		}
	}
	for(int i=1;i<=tot;i++)cout<<ans[i]<<'\n';
	return 0;
}