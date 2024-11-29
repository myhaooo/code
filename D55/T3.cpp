#include<bits/stdc++.h>
#define int long long
#define MAXN 50005
#define MAXM 205
using namespace std;
int T,n,A,B;
int ans;
int fac[MAXN],inv[MAXN],cat[MAXM][MAXN];
const int mod=1e9+7;
inline int qpow(int base,int power){
	int res=1;
	while(power){
		if(power&1)res=res*base%mod;
		base=base*base%mod;
		power>>=1;
	}
	return res%mod;
}
inline void INIT(){
	fac[0]=inv[0]=1,cat[0][0]=1;;
	for(int i=1;i<MAXN;i++)fac[i]=fac[i-1]*i%mod,cat[1][i]=fac[i-1];
	inv[MAXN-1]=qpow(fac[MAXN-1],mod-2);
	for(int i=MAXN-2;i>=1;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=2;i<MAXN;i++){
		for(int j=2;j<=min(i,1ll*MAXM-1);j++)
			cat[j][i]=(cat[j-1][i-1]+(i-1)*cat[j][i-1]%mod)%mod;
	}
}
inline int C(int x,int y){
	if(y>x)return 0;
	if(!y)return 1;
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline void work(){
	cin>>n>>A>>B;
	
//	if(A+B>n+1){
//		printf("0\n");
//		return ;
//	}
	cout<<(C(A+B-2,A-1)*cat[A+B-2][n-1]%mod)<<"\n";
}
signed main(){
	freopen("building.in","r",stdin);
	freopen("building.out","w",stdout);
	INIT();
	cin>>T;
	while(T--)work();
	return 0;
}
