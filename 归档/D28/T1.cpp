#include<bits/stdc++.h>
using namespace std;
#define pii pair<int ,int>
const int N = 2e5 + 10,mod = 1e9 + 7;
struct EDGE{int to,next;}edge[N<<1];
int head[N],cnt;
inline void add(int u,int v){edge[++cnt] = {v,head[u]};head[u] = cnt;}
priority_queue<pii,vector<pii>,greater<pii> > q;
bitset<N> vis;
unordered_set<int> pre[N];
int dis[N],num[N];
int n,s,t,m,mn;
inline void dijkstra(int s){
    vis.reset();
    memset(dis,0x3f,sizeof dis);
    dis[s] = 0;num[s] = 1;
    queue<int> q;q.push(s);vis[s] = true;
    while(q.size()){
        int x = q.front();q.pop();vis[x] = false;
        for(int i = head[x]; i;i = edge[i].next){
            int y = edge[i].to;
            if(dis[y] > dis[x] + 1){
                dis[y] = dis[x] + 1;
                num[y] = num[x] % mod;
                unordered_set<int> ().swap(pre[y]);
                pre[y].insert(x);
                if(!vis[y]){
                    vis[y] = true;
                    q.push(y);
                }
            }
            else if(dis[y] == dis[x] + 1) 
                num[y] = (num[y] + num[x]) % mod,pre[y].insert(x);
        }
    }
}
int ans = 0;
int mp[N];
int dfs(int x){
    if(vis[x])return mp[x];
    vis[x] = true;
    int ans = 0;
    for(int i = head[x]; i;i = edge[i].next){
        int y = edge[i].to;
        if(pre[x].find(y) != pre[x].end()) continue;
        if(dis[y] == dis[x]) ans = (ans + num[y]) % mod;
    }
    for(auto i : pre[x]) ans = (ans + dfs(i)) % mod;
    mp[x]=ans;
    return ans;
}
signed main(){
    cin>>n>>m>>s>>t;
    for(int i = 1,u,v;i <= m; ++i){
        cin>>u>>v;
        add(u,v);add(v,u);
    }
    dijkstra(s);
    cout<<dfs(t)<<'\n';
}