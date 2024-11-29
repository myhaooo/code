#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
const int mod=998244353;
struct node{
	int nxt,to;
	node(int x=0,int y=0,int z=0):nxt(x),to(y){}
}e[MAXN<<1];
int tot=1,head[MAXN];
inline void add(int from,int to){
	e[++tot]=node(head[from],to),head[from]=tot;
}
int n,k,size[MAXN];
long long ans;
void dfs1(int u,int fa){
	size[u]=1;
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		dfs1(v,u);
		size[u]+=size[v];
	}
}
void dfs2(int u,int fa){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;if(v==fa)continue;
		ans=(ans+(long long)size[v]*(n-size[v]))%mod;
		dfs2(v,u);
	}
}
int main(){
	freopen("pathpath.in","r",stdin);
	freopen("pathpath.out","w",stdout);
	cin>>n>>k;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs1(1,0);
	dfs2(1,0);
	cout<<ans<<endl;
	return 0;
}
