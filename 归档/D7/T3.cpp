#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 1005
#define int long long
using namespace std;
const int mod=1e9+7;
int n,typ;
int f[MAXN],g[MAXN];
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
	f[0]=g[0]=1;
	for(int i=1;i<MAXN;i++){
		f[i]=f[i-1]*i%mod;
		g[i]=g[i-1]*qpow(i,mod-2)%mod;
	}
} 
inline int getC(int x,int y){
	if(y>x)return 0;
	return f[x]*g[y]%mod*g[x-y]%mod;
}
inline int inv(int x){
	return qpow(x,mod-2)%mod;
}
inline int Cat(int x){
	return getC(2*x,x)*inv(x+1)%mod;
}
int ans;
int dp[MAXM];
signed main(){
	INIT();
	scanf("%lld%lld",&n,&typ);
	if(typ==0){
		for(int i=0;i<=n;i+=2){
			ans=(ans+getC(n,i)*getC(i,i/2)%mod*getC(n-i,(n-i)/2)%mod)%mod;
		}	
		printf("%lld",ans%mod);
	}
	if(typ==1){
		printf("%lld",Cat(n/2));
	}
	if(typ==2){
		dp[0]=1;
		for(int i=1;i<=n/2;i++){
			for(int j=1;j<=i;j++)dp[i]=(dp[i]+dp[i-j]*Cat(j-1)%mod*4%mod)%mod;
		}
		printf("%lld",dp[n/2]);
	}
	if(typ==3){
		for(int i=0;i<=n;i+=2){
			ans=(ans+getC(n,i)*Cat(i/2)%mod*Cat((n-i)/2)%mod)%mod;
		}
		printf("%lld",ans);
	}
	return 0;
}