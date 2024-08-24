#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5,P=1e9+7;
int n,m,k;
ll fac[N],inv[N];

ll qpow(ll a,int b,int mod=P){
	ll res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}

ll C(int n,int m){
	if(n<0||m<0||n<m)return 0;
	return fac[n]*inv[m]%P*inv[n-m]%P;
}

int main(){
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>k>>m;
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%P;
	inv[n]=qpow(fac[n],P-2);
	for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%P;
    
	cout<<((2*C(m+n-k-1,m)-(n-k))%P+P)%P;
	return 0;
}