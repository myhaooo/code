#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 1000005;
const int mod = 998244353;
int f[maxn],g[maxn],sum,n,m;

int qpow(int x,int b)
{
	int res = 1;
	while(b)
	{
		if(b&1) res=res*x%mod;
		x=x*x%mod,b>>=1;
	}
	return res;
}

signed main()
{
	cin>>n>>m;
	if(m==1) sum=1;
	else for(int i=1; i<=m; i++)
	{
		int tmp = (i+1)/2+(i+2)/2;
		if(m%2==0) sum+=tmp*(m/2)+(m/2)*(m/2-1);
		else sum+=tmp*(m/2)+(m/2)*(m/2-1)+(i+m)/2;
	}
	sum %= mod;
	f[2]=g[1]=sum;
	for(int i=2; i<=n-2; i++)
		g[i] = (qpow(m,i-1)*sum%mod+m*g[i-1])%mod;
	for(int i=3; i<=n; i++)
		f[i] = (m*f[i-1]%mod+m*g[i-2]%mod+qpow(m,i-2)*sum%mod)%mod;
	cout<<f[n];
	return 0;
}
