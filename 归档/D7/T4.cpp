#include<bits/stdc++.h>
using namespace std;

const int mod=998244353;
int n,k;
__int128 f[52][52][2610];
int ans=0;
signed main(){
	cin>>n>>k;
	f[1][0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=n;j++)
			for(int w=0;w<=k;w++){
				f[i][j][w+i]=(f[i][j][w+i]+f[i-1][j][w]*2)%mod;
				f[i][j+1][w]=(f[i][j+1][w]+f[i-1][j][w]*2)%mod;
				f[i][j][w+i]=(f[i][j][w+i]+f[i-1][j][w]*j*2)%mod;
				f[i][j+1][w]=(f[i][j+1][w]+f[i-1][j][w]*j)%mod;
				if(j)   f[i][j-1][w+2*i]=(f[i][j-1][w+2*i]+f[i-1][j][w]*j)%mod;
			}
	for(int i=0;i<=k;i++)
		ans=(ans+f[n][0][i])%mod;
	cout<<ans<<endl;
	return 0;
}