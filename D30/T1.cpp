#include<bits/stdc++.h>
using namespace std;
#define N 510
#define int long long
int n,mod,c[N][N],_2[N*N],f[N][N],p[N][N];//f[i][j]:前若干层有i个点且最外层有j个点时的方案数
inline int qpow(int a,int b){
    int ans=1;
    while (b)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
inline void init()
{
	c[0][1]=c[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		c[i][0]=c[i][i]=c[0][i]=1;
		for(int j=1;j<i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
	_2[0]=1;
	for(int i=1;i<=n*(n-1)/2;i++)_2[i]=_2[i-1]*2%mod;
	for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            p[i][j]=qpow(_2[i]-1,j)%mod;//((2^i)-1)^j
	
} 
signed main ()
{
	cin>>n>>mod;
	init();
	f[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			for(int k=1;k<=i-j;k++)
            f[i][j]=(f[i][j]+f[i-j][k]*c[n-i+j-1][j]%mod*_2[j*(j-1)/2]%mod*p[k][j]%mod+mod)%mod;
		}
	}
	cout<<f[n][1];
	return 0;
}