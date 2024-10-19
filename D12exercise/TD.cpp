#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
bool be;
stack<int> sta;
int n,m,h[N],vis[N],low[N],dfn[N],num,tot,top,cnt,col[N],siz[N];
int u[N<<2],v[N<<2],in[N],flag,ans;
struct node{
    int nex,to;
}edge[N<<2];
bool ed;
inline void add(int u,int v){
    edge[++tot].nex=h[u];
    edge[tot].to=v;
    h[u]=tot;
}
inline void tarjan(int x){
    dfn[x]=low[x]=++num;
    sta.push(x);vis[x]=1;
    int vi=0;
    for(int i=h[x];i;i=edge[i].nex){
        int v=edge[i].to;
        if(v == fa) vi=1;
		if( v == fa) continue;
        if(!dfn[v]){
            tarjan(v,x);
            low[x]=min(low[x],low[v]);
        }
        else if(vis[v])low[x]=min(low[x],dfn[v]);
    }
    if(low[x]==dfn[x]){
        int now=-1;cnt++;
        while(now!=x){
            now=sta.top();
            sta.pop();
            vis[now]=0;
            siz[cnt]++;
            col[now]=cnt;
        }
    }
}



int main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
    	fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif
    cin>>n>>m;
    for(int i=1;i<=m;i++)
       cin>>u[i],cin>>v[i],add(u[i],v[i]);
    for(int i=1;i<=n;i++)
        if(!dfn[i])tarjan(i,0);

    //
    memset(h,0,sizeof(h));tot=0;
    memset(edge,0,sizeof(edge));
    for(int i=1;i<=m;i++)
        if(col[u[i]]!=col[v[i]]){
            in[col[v[i]]]++;
            add(col[u[i]],col[v[i]]);
        }
    for(int i=1;i<=cnt;i++){
        if(!flag&&!in[i]&&siz[i]==1){
        	int pd=0;
            for(int j=h[i];j;j=edge[j].nex){
                int v=edge[j].to;
                if(in[v]==1)pd=1;
            }
            if(!pd)flag=1;
        }
        if(!in[i])ans++;
    }
    if(flag)ans--;
    printf("%.6f\n",((double)n-(double)ans)/(double)n);
    return 0;
}

