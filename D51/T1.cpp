#include<bits/stdc++.h>
using namespace std;
vector<int>e[200001];
int dfn[200001];
int size[200001],deep[200001],top[200001],fa[200001],maxson[200001];
int dfsorder[200001];
int cnt;
int n,q;
void dfs1(int now,int last){
	size[now]=1;
	deep[now]=deep[last]+1;
	fa[now]=last;
	for(auto i:e[now]){
		if(i!=last){
			dfs1(i,now);
			size[now]+=size[i];
			if(size[i]>size[maxson[now]]){
				maxson[now]=i;
			}
		}
	}
}
void dfs2(int now,int nowtop){
	dfn[now]=++cnt;
	dfsorder[cnt]=now;
	top[now]=nowtop;
	if(maxson[now]){
		dfs2(maxson[now],nowtop);
	}
	for(auto i:e[now]){
		if(i!=fa[now] and i!=maxson[now]){
			dfs2(i,i);
		}
	}
}
int lca(int a,int b){
	while(top[a]!=top[b]){
		if(deep[top[a]]<deep[top[b]]) swap(a,b);
		a=fa[top[a]];
	}
	if(deep[a]<deep[b]) swap(a,b);
	return b;
}
int lca(int a,int b,int c){
	int x1=lca(a,b),x2=lca(a,c),x3=lca(b,c);
	if(deep[x1]<deep[x2]) swap(x1,x2);
	if(deep[x1]<deep[x3]) swap(x1,x3);
	return x1;
}
int dis(int x,int y){
	int p=lca(x,y);
	return deep[x]+deep[y]-2*deep[p];
} 
int getfa(int u,int k){
	int D=deep[u]-k;
	while(deep[fa[top[u]]]>=D) u=fa[top[u]];
	return dfsorder[dfn[u]-(deep[u]-D)];
}
int getfa(int a,int b,int k){
	int p=lca(a,b);
	int d1=deep[a]-deep[p],d2=deep[b]-deep[p];
	if(d1>=k) return getfa(a,k);
	return getfa(b,d1+d2-k);
}
signed main(){
	freopen("chase.in","r",stdin);
	freopen("chase.out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n-1;i++){
		int a,b;cin>>a>>b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	dfs1(1,0);dfs2(1,1);
	while(q--){
		int u,v,x;
		cin>>u>>v>>x;
		int p=lca(u,v,x);
		int d1=dis(x,p),d2=dis(u,p),d3=dis(p,v);
		if(d2<d1){
			cout<<d1+d3<<" "<<v<<"\n"; 
		}
		else{
			cout<<(d1+d2+1)/2<<" "<<getfa(u,x,(d1+d2+1)/2)<<"\n";
		}
	}
}