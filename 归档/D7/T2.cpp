#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,k,a[N],b[N];
int h[N],to[N],nxt[N];
void add(int x,int y){
	nxt[++k]=h[x];
	h[x]=k;to[k]=y;
}//0问题解决 
int f[N],g[N],sz[N];
void dfs1(int x,int fa){
	f[x]=g[x]=sz[x]=0;
	for(int i=h[x];i;i=nxt[i]){
		if(to[i]==fa) continue;
		int y=to[i];dfs1(y,x);
		sz[x]+=sz[y];
		f[x]+=f[y]+sz[y];
	}sz[x]+=a[x];
}void dfs2(int x,int fa){
	if(x!=1) g[x]=g[fa]+f[fa]-f[x]+sz[1]-2*sz[x];
	for(int i=h[x];i;i=nxt[i])
		if(to[i]!=fa) dfs2(to[i],x);
}void solve0(){
	for(int i=1;i<=n;i++)
		cin>>a[i]; 
	dfs1(1,0);dfs2(1,0);
	for(int i=1;i<=n;i++)
		cout<<f[i]+g[i]<<" ";
	cout<<"\n";
}//1问题解决
int rt;
void get_sz(int x,int fa){
	for(int i=h[x];i;i=nxt[i]){
		if(to[i]==fa) continue;
		int y=to[i];
		sz[y]=(b[x]-b[y]+sz[rt])/2;
		get_sz(y,x);a[x]-=sz[y];
	}a[x]+=sz[x];
}void solve1(){
	for(int i=1;i<=n;i++)
		cin>>b[i]; 
	int sn=0;
	for(int i=1;i<=n;i++)
		if(!nxt[h[i]]) rt=i;
	sn=to[h[rt]];
	for(int i=1;i<=100;i++){
		for(int j=1;j<=n;j++)
			a[j]=sz[j]=0;
		sz[sn]=b[rt]-b[sn]+i;
		a[rt]=i;sz[rt]=sz[sn]+i;
		get_sz(sn,rt);int fl=1;
		dfs1(1,0);dfs2(1,0);
		for(int j=1;j<=n;j++)
			if(f[j]+g[j]!=b[j]){fl=0;break;}
		if(fl){
			for(int j=1;j<=n;j++)
				cout<<a[j]<<" ";
			cout<<"\n";return;
		}
	}
}signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;k=0;
		memset(h,0,sizeof(h));
		memset(nxt,0,sizeof(nxt));
		memset(to,0,sizeof(to));
		for(int i=1;i<n;i++){
			int x,y;cin>>x>>y;
			add(x,y);add(y,x);
		}int x;cin>>x;
		if(!x) solve0();
		else solve1();
	}return 0;
} 