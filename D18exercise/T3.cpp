#include<bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int N=3e5+10;
const int mod=998244353;
ll ans;
stack<int> s1,s2;
int n,m,T,a[N],f[N],g[N],h[N];
signed main(){
	cin>>n;
	for(register int i=1;i<=n;++i) cin>>a[i];
	f[0]=1;
	for(register int i=1;i<=n;++i){
		while(!s1.empty()&&a[s1.top()]<a[i]) s1.pop();
		while(!s2.empty()&&a[s2.top()]>a[i]) s2.pop();
		if(!s1.empty()) g[i]=(g[s1.top()]+(f[i-1]-f[s1.top()-1]+mod)%mod*a[i]%mod)%mod;
		else g[i]=f[i-1]*a[i]%mod;
		if(!s2.empty()) h[i]=(h[s2.top()]+(f[i-1]-f[s2.top()-1]+mod)%mod*a[i]%mod)%mod;
		else h[i]=f[i-1]*a[i]%mod;
		f[i]=(f[i-1]+g[i]-h[i]+mod)%mod;
		s1.push(i),s2.push(i);
	}
	cout<<(f[n]-f[n-1]+mod)%mod;
	return 0;
}