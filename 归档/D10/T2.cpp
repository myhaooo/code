#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 55
#define MOD 998244353
int n,k,raw{1},line{1};
int a[MAXN][MAXN],f[MAXN],siz[MAXN],fac[410]={1,1};
int find(int x){
    return(f[x]==x?x:f[x]=find(f[x]));
}
void add(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return ;
	if(x<y) f[x]=y;
	else f[y]=x;
}

signed main(){
    ios::sync_with_stdio(false);
    #define clear(a) memset(a, 0, sizeof(a))
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
        #define 下面是代码 上面是模版------------------
    #endif
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		f[i]=i;
    for(int i=1;i<=403;i++){
        fac[i]=fac[i-1]*i%MOD;
    }
		for(int x=1;x<=n;x++){
		for(int y=x+1;y<=n;y++){
			for(int i=1;i<=n;i++){
				if(a[x][i]+a[y][i]>k){
                    goto ed1;
				}
            }
			add(x,y);
            ed1:;
		}
    }
	for(int i=1;i<=n;i++)
		siz[find(f[i])]++;
	for(int i=1;i<=n;i++)
		line=line*fac[siz[i]]%MOD;
	for(int i=1;i<=n;i++)
		f[i]=i;
    clear(siz); 
	for(int x=1;x<=n;x++){
		for(int y=x+1;y<=n;y++){
			for(int i=1;i<=n;i++){
				if(a[i][x]+a[i][y]>k){
                    goto ed2;
				}
            }
            add(x,y);
            ed2:;
		}
    }
	for(int i=1;i<=n;i++)
		siz[find(f[i])]++;
	for(int i=1;i<=n;i++)
		raw=raw*fac[siz[i]]%MOD;

	cout<<raw*line%MOD<<endl;
    return 0;
}
