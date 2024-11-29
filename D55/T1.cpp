#include<bits/stdc++.h>
using namespace std;
#define inv(x) ksm(x,mod-2,mod)
#define int long long
const int N=1e6+5,mod=998244353;
int x[N],pre[N];
inline int ksm(int a,int b,int mod){
	a%=mod; int res=1;
	while(b){
		if(b&1) res=(res*a)%mod;
		a=(a*a)%mod,b>>=1;
	}
	return res%mod;
}
	int m,n,ans=1;
signed main(){

	freopen("ds.in","r",stdin);
	freopen("ds.out","w",stdout);
	cin>>n; for(int i=1;i<=n;i++) cin>>x[i],pre[i]=pre[i-1]+x[i];
	for(int i=1;i<n;i++){
		while(x[i]) 
			ans=(ans*n%mod*x[i]%mod*inv(x[i]+pre[n]-pre[i])%mod),x[i]--;
	}
	ans=ans*ksm(n,x[n],mod)%mod; 
	cout<<ans;
}

