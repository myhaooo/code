#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e6+5;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
int n,cnt,idnex,l[MAXN],r[MAXN],head[MAXN],dep[MAXN],sz[MAXN],son[MAXN];
int book[MAXN*10],vis[MAXN],ans[MAXN],dis[MAXN],id[MAXN];
struct node{
    int to,next,w;
}e[MAXN];
void add(int u,int v,int w){
    e[++cnt].to=v;
    e[cnt].w=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}


// void add( int x, int y, int w ) {
// 	e[++ cnt] = (node){ y, head[x], w }, head[x] = cnt ; 
// }
void dfs(int x,int fa){
    sz[x]=1,l[x]=++idnex,dep[x]=dep[fa]+1,id[idnex]=x;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;
        dis[v]=dis[x]^e[i].w;dfs(v,x),sz[x]+=sz[v];
        if(sz[son[x]]<sz[v])son[x]=v;
    }
    r[x]=idnex;
}
// void dfs( int x, int fa ) {
// 	sz[x] = 1, l[x] = ++ idnex, dep[x] = dep[fa] + 1, id[idnex] = x ; 
// 	Next( i, x ) {
// 		int v = e[i].to ; dis[v] = dis[x] ^ e[i].w, dfs( v, x ), sz[x] += sz[v] ;
// 		if( sz[son[x]] < sz[v] ) son[x] = v ; 
// 	} r[x] = idnex ; 
// }


void dfs2(int x,int keep){
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;if(v==son[x])continue;
        dfs2(v,0),ans[x]=max(ans[x],ans[v]);
    }
     if(son[x])dfs2(son[x],1),ans[x]=max(ans[x],ans[son[x]]);
     if(book[dis[x]]) ans[x]=max(ans[x],book[dis[x]]-dep[x]);

    for(int i=0;i<=21;i++){
        if(book[dis[x]^(1<<i)])ans[x]=max(ans[x],book[dis[x]^(1<<x)]-dep[x]);
    }
    //rep( i, 0, 21 ) if( book[dis[x] ^ ( 1 << i )] ) ans[x] = max( ans[x], book[dis[x] ^ ( 1 << i )] - dep[x]);
    book[dis[x]] = max( dep[x] , book[dis[x]] ) ;
    for(int i=head[x];i;i=e[i].next){
        int v=e[i].to;if(v==son[x])continue;   
        for(int j=l[v];j<=r[v];j++){
            int u=id[j];
            if( book[dis[u]] ) ans[x] = max( ans[x], book[dis[u]] + dep[u] - 2 * dep[x] ) ; 
            for(int k=0;k<=21;k++){
                if(book[dis[u]^(1<<k)]) ans[x]=max(ans[x], book[dis[u]^(1<<k)] + dep[u] - 2 * dep[x] );

            }

        }
        for(int j=l[v];j<=r[v];j++)
            book[dis[id[j]]]=max(dep[id[j]],book[dis[id[j]]]);
        
        

    }
    if(!keep)for(int i=l[x];i<=r[x];i++) book[dis[id[i]]]=0;

}


// void dfs2( int x, int keep ) {
// 	Next( i, x ) {
// 		int v = e[i].to ; if( v == son[x] ) continue ; 
// 		dfs2( v, 0 ), ans[x] = max( ans[x], ans[v] ) ; 
// 	}
// 	if( son[x] ) dfs2( son[x], 1 ), ans[x] = max( ans[x], ans[son[x]] ) ; 
// 	if( book[dis[x]] ) ans[x] = max( ans[x], book[dis[x]] - dep[x] ) ; 
// 	rep( i, 0, 21 ) if( book[dis[x] ^ ( 1 << i )] ) ans[x] = max( ans[x], book[dis[x] ^ ( 1 << i )] - dep[x] ) ; 
// 	book[dis[x]] = max( dep[x] , book[dis[x]] ) ;
// 	Next( i, x ) {
// 		int v = e[i].to ; if( v == son[x] ) continue ; 
// 		rep( j, l[v], r[v] ) {
// 			int u = id[j] ; 
// 			if( book[dis[u]] ) ans[x] = max( ans[x], book[dis[u]] + dep[u] - 2 * dep[x] ) ; 
// 			rep( k, 0, 21 ) if( book[dis[u] ^ ( 1 << k )] ) ans[x] = max( ans[x], book[dis[u] ^ ( 1 << k )] + dep[u] - 2 * dep[x] ) ; 
// 		}
// 		rep( j, l[v], r[v] ) book[dis[id[j]]] = max( book[dis[id[j]]], dep[id[j]] ) ; 
// 	}
// 	if( !keep ) rep( i, l[x], r[x] ) book[dis[id[i]]] = 0 ; 
// }


signed main()
{
	cin>>n; int x; char ch ; 
	for(int i=2;i<=n;i++){
		cin>>x >> ch, add( x, i, 1ll << ( ch - 'a' ) ) ; 
	}
	dfs( 1, 1 ), dfs2( 1, 1 ) ;
	for(int i=1;i<=n;i++) {
        cout<<ans[i]<<" ";
    }
	return 0;
}
// signed main()
// {
// 	cin>>n; int x; char ch ; 
// 	rep( i, 2, n ) {
// 		scanf("%d", &x), cin >> ch, add( x, i, 1ll << ( ch - 'a' ) ) ; 
// 	}
// 	dfs( 1, 1 ), dfs2( 1, 1 ) ;
// 	rep( i, 1, n ) printf("%d ", ans[i] ) ;
// 	return 0;
// }