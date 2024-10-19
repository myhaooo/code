#include<cstdio>
//#define ot e[i].to
struct edge{
    int to,next;
}e[400005];
int n,tot=0,last[200005],cnt[2],sz[200005];long long ans=0;
inline void add(int u,int v) {
    e[++tot]=(edge){v,last[u]},
    last[u]=tot;
    return;
}
void dfs(int root,int fa,int dep) {
    ++cnt[dep^=1],sz[root]=1;//记录下子树大小以及深度奇偶性
	for (register int i=last[root];i;i=e[i].next) 
    if (e[i].to^fa) dfs(e[i].to,root,dep),sz[root]+=sz[e[i].to];
    ans+=1LL*(n-sz[root])*sz[root];//更新子树大小
	return ;//更新答案
}
int main() {
    int u,v;
	scanf("%d",&n);
    for (register int i=1;i<n;++i) 
    scanf("%d%d",&u,&v),add(u,v),add(v,u);
	dfs(1,0,0);printf("%lld",ans+1LL*cnt[0]*cnt[1]>>1);//计算答案
}