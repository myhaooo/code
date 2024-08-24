#include<bits/stdc++.h>
using namespace std;
int n;
const int MAXN=2e5+10;
struct node{
    int to,next;
}edge[MAXN<<1];
int head[MAXN],tot;
long long cnt[2],dep[MAXN],size[MAXN];
void add(int x,int y){
    edge[++tot].to=y;
    edge[tot].next=head[x];
    head[x]=tot;
}
long long ans=0;
void dfs(int now,int fa){
    size[now]=1ll;
    dep[now]=dep[fa]+1;
    cnt[dep[now]%2]++;
    for(int i=head[now];i;i=edge[i].next){
        int y=edge[i].to;
        if(y==fa) continue;
        dfs(y,now);
        size[now]+=size[y];
        ans+=size[y]*(n-size[y]);//当前节点 和 (其邻接节点 的 子树节点数量 之差)的 乘积
    }
}
int main(){
    
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    #ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
    cin>>n;
    for(int i=1,u,v;i<n;i++){
        cin>>u>>v;
        add(u,v);
        add(v,u);
    }
    
    dfs(1,0);
    ans+=cnt[0]*cnt[1];
    cout<<(ans>>1)<<"\n";
    return 0;
}
/*
先处理出每个点的深度(dep)和子树大小(size)，我们把原树上的边称为老边，新建的边是新边。

首先因为隔了一个点有一条新边，假设新边跨过的点为 u ，那么这条新边产生的价值就是size[i]*(n-size[i])/2，也就是两边点对数量。那么老边会不会产生价值呢？如果原树上两点之间的距离为奇数，那么新图上肯定需要经过一条老边。所以答案还需要加上 (深度为奇的点数×深度为偶的点数)/2。

*/