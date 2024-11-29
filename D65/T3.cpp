#include <bits/stdc++.h>
using namespace std;

const long long mod=998244353;
struct node{
	long long x,y,z;
}p[10007];
bool cmp(node a,node b){
	if(a.x!=b.x) return a.x<b.x;
	if(a.y!=b.y) return a.y<b.y;
	return a.z<b.z;
}
long long a,b,c;
long long n;
int C[65][65];
long long f[65][65][65];
long long g[10007];
int cc[5000007];
int pc(long long x){
	int cnt=0;
	while(x){
		x=x^(x&-x);
		cnt=cnt+1;
	}
	return cnt;
}
signed main(){
	cin>>a>>b>>c>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i].x>>p[i].y>>p[i].z;
	}

	p[++n]=(node){a,b,c};
	sort(p+1,p+n+1,cmp);
	for(int i=0;i<64;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	f[0][0][0]=1;

	for(int i=0;i<64;i++){
		for(int j=0;j<64;j++){
			for(int k=0;k<64;k++){
				for(int x=1;x<=i;x++) f[i][j][k]=(f[i][j][k]+f[i-x][j][k]*C[i][x])%mod;
				for(int x=1;x<=j;x++) f[i][j][k]=(f[i][j][k]+f[i][j-x][k]*C[j][x])%mod;
				for(int x=1;x<=k;x++) f[i][j][k]=(f[i][j][k]+f[i][j][k-x]*C[k][x])%mod;
			}
		}
	}

	for(int i=1;i<=n;i++){
		g[i]=f[pc(p[i].x)][pc(p[i].y)][pc(p[i].z)];
		for(int j=1;j<i;j++){
            if((p[j].x&p[i].x)!=p[j].x||(p[j].y&p[i].y)!=p[j].y||(p[j].z&p[i].z)!=p[j].z) continue;
            g[i]=(g[i]+mod-g[j]*f[pc(p[j].x^p[i].x)][pc(p[j].y^p[i].y)][pc(p[j].z^p[i].z)]%mod)%mod;
		}
	}
	printf("%lld\n",g[n]);
	return 0;
}