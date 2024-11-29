#include<bits/stdc++.h>
#define N 200005
#define mod 998244353
using namespace std;
int n,a[N];
vector<int> e[N],id[N];
bool vis[N],mvis[N];
int cntd,cnte;
int ans1=1,ans2=0;
void dfs(int u){
	if(vis[u])	return;
	vis[u]=1,cntd++;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i];
		if(!mvis[id[u][i]])	cnte++,mvis[id[u][i]]=1;
		dfs(v);
	}	
}
int f[N];
void solve1(int u,int fa){
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i],w=id[u][i];
		if(v==fa)	continue;
		solve1(v,u);
		f[u]+=f[v]+(a[w]==u);
	}
}
int mxn,cnt;
void solve2(int u,int fa){
	if(f[u]==mxn)	cnt++;
	if(f[u]<mxn)	mxn=f[u],cnt=1;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i],w=id[u][i];
		if(v==fa)	continue;
		f[v]=f[u]+(a[w]==u?-1:1);
		solve2(v,u);
	}
}
vector<int> rng;
vector<int> eng;
int pre[N],pre2[N],visp[N],lf,visr[N];
void query1(int u,int fa,int fid){
	if(u==fa){
		lf=1;
		rng.push_back(u);
		eng.push_back(fid);
		return;
	}
	if(visp[u]){
		for(int i=fa;i!=u;i=pre[i]){
			rng.push_back(i);
			eng.push_back(pre2[i]);
		}
		rng.push_back(u);
		eng.push_back(fid);
		lf=1;
		return;
	}
	visp[u]=1,pre[u]=fa,pre2[u]=fid;
	bool flag=0;
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i],w=id[u][i];
		if(v==fa&&flag==0){
			flag=1;
			continue;
		}
		query1(v,u,w);
		if(lf==1)	return;
	}
}
void query2(int u,int fa){
	for(int i=0;i<e[u].size();i++){
		int v=e[u][i],w=id[u][i];
		if(visr[v]||v==fa)	continue;
		query2(v,u);
		f[u]+=f[v]+(a[w]==u);
	}
}
int main(){
	freopen("card.in","r",stdin);
	freopen("card.out","w",stdout);
	cin>>n;
	for(int i=1,x,y;i<=n;i++){
		cin>>x>>y;
		a[i]=x;
		e[x].push_back(y),e[y].push_back(x);
		id[x].push_back(i),id[y].push_back(i);
	}
	n*=2;
	for(int i=1;i<=n;i++){
		if(vis[i])	continue;
		cnte=cntd=0,dfs(i);
		if(cnte>cntd)	cout<<-1<<' '<<-1,exit(0);
		if(cntd>cnte){
			solve1(i,0);
			mxn=0x3f3f3f3f,cnt=0;
			solve2(i,0);
			ans1=1ll*ans1*cnt%mod,ans2=(ans2+mxn)%mod;
		}
		else{
			rng.clear(),lf=0,eng.clear();
			query1(i,0,0);
			for(auto k:rng)	visr[k]=1;
			for(auto k:rng){
				query2(k,0);
				ans2=(ans2+f[k])%mod;
			}
			if(rng.size()==1)	continue;
			int cnt1=0,cnt2=0;
			for(int h=0;h<rng.size()-1;h++){
				cnt1+=(a[eng[h]]==rng[h]),cnt2+=(a[eng[h]]==rng[h+1]);
			}
			cnt1+=(a[eng.back()]==rng.back());
			cnt2+=(a[eng.back()]==rng[0]);
			ans2=(ans2+min(cnt1,cnt2))%mod;
			if(cnt1==cnt2)	ans1=(1ll*ans1*2)%mod;
		}
	}
	cout<<ans2<<' '<<ans1<<endl;
	return 0;
} 

