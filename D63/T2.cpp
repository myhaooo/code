#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
#define ll long long
#define lll __int128
int n;
struct edge{
	int to,nxt,w;
}e[N<<1];
int hd[N],ect;
void add(int u,int v,int w){
	e[++ect]={v,hd[u],w};
	hd[u]=ect;
}
const int inf=1e9;
int ct[3],su[3][N];
int vis[N];
lll ans;
int mark[3][N];
struct node{
	int id,dis;
};
int siz[3][N],fa[N],dep[N],tot;
void dfs(int u,int f){
	for(int j=0;j<3;j++){
		siz[j][u]=mark[j][u];
	}
	dep[u]=dep[f]+1;
	fa[u]=f;
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)continue;
		dfs(v,u);
		for(int j=0;j<3;j++){
			siz[j][u]+=siz[j][v];
		}
	}
}
void dfs2(int u,int f){
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].to;
		if(v==f)continue;
		dfs2(v,u);
		lll in[3],out[3];
		for(int j=0;j<3;j++){
			in[j]=siz[j][v];
			out[j]=ct[j]-siz[j][v];
		}
		lll vall=e[i].w;
		ans=ans+(in[0]*out[1]*ct[2]+in[0]*out[2]*ct[1])*vall;
		ans=ans+(in[1]*out[0]*ct[2]+in[1]*out[2]*ct[0])*vall;
		ans=ans+(in[2]*out[0]*ct[1]+in[2]*out[1]*ct[0])*vall;
	}
}
void write(lll x){
	if(!x)return;
	write(x/10);
	putchar(x%10+'0');
}
int main(){
	#ifndef LOCAL
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	for(int i=0;i<3;i++){
		scanf("%d",&ct[i]);
		for(int j=1;j<=ct[i];j++){
			scanf("%d",&su[i][j]);
			mark[i][su[i][j]]=1;
		}
	}
	dfs(1,0);
	dfs2(1,1);
	ans=ans/2;
	write(ans);
	return 0;
}
