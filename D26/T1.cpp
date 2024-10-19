//奇环都包含这条边且偶环都不包含这条边
//MD服了，谁家好人出三道树啊，百分百弱点击破
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
int n,m;
struct edge{
	int v,nxt;
}e[MAXN << 2];

int cnt=1 ,head[MAXN];

void add(int u,int v){
	e[++cnt] = edge{v,head[u]},head[u] = cnt;
	e[++cnt] = edge{u,head[v]},head[v] = cnt;
}
bool rt[MAXN],vis[MAXN];
int ocnt,dep[MAXN],lres[MAXN],rres[MAXN];

void dfs(int u,int fa){
	vis[u] = 1;
	for (int i = head[u];i;i = e[i].nxt) if (i ^ fa ^ 1){
		int v = e[i].v;
		if (!vis[v]) dep[v] = dep[u] + 1,dfs (v,i),lres[u] += lres[v],rres[u] += rres[v];
		else if (dep[v] < dep[u]){
			if ((dep[u] - dep[v]) & 1)/*%2==0*/ rres[u]++,rres[v]--;
			else lres[u]++,lres[v]--,ocnt++;
		}
	}
}

signed main(){
	cin>>n>>m;
	for (int i = 1,u,v;i <= m;++ i) cin>>u>>v,add(u,v);
	for (int i = 1;i <= n;++ i) 
        if (!vis[i]) rt[i] = 1,dfs (i,0); 
	int ans = ocnt ==1;
    for (int i = 1;i <= n;++ i){ 
        if (!rt[i] && !rres[i] && lres[i] == ocnt) ans++;
    }
	cout<<ans<<"\n";
	return 0;
}