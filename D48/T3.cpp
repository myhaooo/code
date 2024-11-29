#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,cnt,ans=1,dist[1000005];
vector<int> gv[1000005],pre[1000005];
bool vis[1000005];
map<pair<int,int>,int> mp;
void bfs(){
	queue<int> q;
	q.push(1);
	while(!q.empty()){
		int p=q.front();
		q.pop();
		for(auto nx:gv[p]){
			if(!dist[nx]){
				pre[nx].push_back(mp[{p,nx}]);
				q.push(nx);
				dist[nx]=dist[p]+1;
			}
			else if(dist[nx]==dist[p]+1){
				pre[nx].push_back(mp[{p,nx}]);
			}
		}
	}
}
void dfs(int now){
	if(now==n){
		for(int i=1;i<=m;i++) cout<<vis[i];
		cnt++;
		if(cnt==ans) exit(0);
		cout<<'\n';
		return;
	}
	for(auto nx:pre[now+1]){
		vis[nx]=1;
		dfs(now+1);
		vis[nx]=0;
	}
}
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		gv[x].push_back(y);
		gv[y].push_back(x);
		mp[{x,y}]=i,mp[{y,x}]=i;
	}
	bfs();
	for(int i=2;i<=n;i++){
		if(pre[i].size()) ans*=pre[i].size();
		if(ans>k){
			ans=k;
			break;
		}
	}
	cout<<ans<<'\n';
	dfs(1);
}