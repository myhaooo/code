#include <bits/stdc++.h>
using namespace std;
#define int long long
#define INF 0x3f3f3f3f3f3f3f3f
#define N (int)(3e5+15)
struct Edge
{
    int u,v,w,next;
}e[N<<1];
int n,s,ans=INF;
int pos=1,head[N],x,y,dis[N],pre[N],pd[N];
void addEdge(int u,int v,int w)
{
    e[++pos]={u,v,w,head[u]};
    head[u]=pos;
}
void dfs(int u,int f)
{
    pre[u]=f;
    for(int i=head[u]; i; i=e[i].next)
    {
        int v=e[i].v;
        if(v==f||pd[v])continue;
        dis[v]=dis[u]+e[i].w;
        dfs(v,u);
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin >> n >> s;
    for(int i=1,u,v,w; i<n; i++)
    {
        cin >> u >> v >> w;
        addEdge(u,v,w);
        addEdge(v,u,w);
    }
    dis[1]=1;dfs(1,0);
    x=max_element(dis+1,dis+1+n)-dis;
    dis[x]=0;dfs(x,0);
    y=max_element(dis+1,dis+1+n)-dis;
    for(int i=y,j=y; i; i=pre[i]){
        pd[i]=1;
        while(dis[j]-dis[i]>s)j=pre[j];
        ans=min(ans,max(dis[i],dis[y]-dis[j]));
    }
    for(int i=y; i; i=pre[i])
    {
        dis[i]=0;
        dfs(i,pre[i]);
    }
    for(int i=1; i<=n; i++)
        ans=max(ans,dis[i]);
    cout << ans << endl;
    return 0;
}
