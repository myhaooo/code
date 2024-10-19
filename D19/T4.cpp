#include<bits/stdc++.h>
using namespace std;
const int N=55;
int n,a,b,w[N],f[N][N],g[N][N][N][N],d[N];
int tot;
int main(){
	cin>>n>>a>>b;

	for(int i=1;i<=n;++i) cin>>w[i],d[i]=w[i];
	sort(d+1,d+n+1);
    tot=unique(d+1,d+n+1)-d-1;
	for(int i=1;i<=n;++i) w[i]=lower_bound(d+1,d+tot+1,w[i])-d,f[i][i]=a;
	
    memset(g,0x3f,sizeof(g));memset(f,0x3f,sizeof(f));
	
    for(int i=1;i<=n;++i)g[i][i][w[i]][w[i]]=0;

	for(int len=1;len<=n;++len)
		for(int l=1,r=len;r<=n;++l,++r)
			for(int mn=1;mn<=tot;++mn)
				for(int mx=mn;mx<=tot;++mx){
					int &G=g[l][r][mn][mx];
					for(int k=l;k<r;++k)	
                        G=min(g[l][k][mn][mx]+f[k+1][r],G);

					int &gg=g[l][r+1][min(mn,w[r+1])][max(mx,w[r+1])];
					gg=min(gg,G);f[l][r]=min(f[l][r],G+a+b*(d[mx]-d[mn])*(d[mx]-d[mn]));
				}
	printf("%d\n",f[1][n]);
}