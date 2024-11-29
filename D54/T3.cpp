#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
const int maxn=1e5+5;
int N,V,x,y,tot,top,F[maxn],sta[maxn];
int son[maxn<<1],nxt[maxn<<1],lnk[maxn];
long long g[maxn],c[maxn][105],b[maxn][105],ans;
inline int read() {
	int ret=0,f=1,ch=getchar();
	for (; !isdigit(ch); ch=getchar()) if (ch=='-') f=-f;
	for (; isdigit(ch); ch=getchar()) ret=ret*10+ch-48;
	return ret*f;
}
inline void add_edge(int x,int y) {
	son[++tot]=y,nxt[tot]=lnk[x],lnk[x]=tot;
	son[++tot]=x,nxt[tot]=lnk[y],lnk[y]=tot;
}
inline void DP(int x,int y,int f) {
	for (int i=1; i<=V; ++i) ans=max(ans,c[x][i]+b[y][V-i]);
	for (int i=1; i<=V; ++i)
		c[x][i]=max(c[x][i],max(c[y][i],c[y][i-1]+g[x]-F[y])),
		b[x][i]=max(b[x][i],max(b[y][i],b[y][i-1]+g[x]-F[f]));
}
void dfs(int x,int pre) {
	for (int i=1; i<=V; ++i) c[x][i]=g[x],b[x][i]=g[x]-F[pre];
	for (int k=lnk[x]; k; k=nxt[k]) if (son[k]^pre) dfs(son[k],x),DP(x,son[k],pre);
	for (int i=1; i<=V; ++i) c[x][i]=g[x],b[x][i]=g[x]-F[pre];
	top=0;for (int k=lnk[x]; k; k=nxt[k]) if (son[k]^pre) sta[++top]=son[k];
	for (int i=top; i; --i) DP(x,sta[i],pre);
	ans=max(ans,max(c[x][V],b[x][V]));
}
int main() {
	freopen("park.in","r",stdin);
	freopen("park.out","w",stdout);
	N=read(),V=read();
	for (int i=1; i<=N; ++i) F[i]=read();
	for (int i=1; i<N; ++i) add_edge(x=read(),y=read()),g[x]+=F[y],g[y]+=F[x];
	return dfs(1,0),printf("%lld",ans),0;
}
