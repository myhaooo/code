#include<bits/stdc++.h>
using namespace std;

const int maxn=1005;
int c[maxn][maxn];
int n,m;
long long f[maxn][maxn][2][2],mod;
void pre(){
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
//			cout<<c[i][j]<<" ";
		}
	}
	return ;
}
signed main(){
	freopen("per.in", "r", stdin);
	freopen("per.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin>>n>>m>>mod;
	pre();
//	cout<<c[5][2]<<endl;
	for(int i=0;i<=m;i++)f[0][i][0][0]=f[0][i][1][1]=f[0][i][0][1]=f[0][i][1][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=1;k<=i;k++){
				f[i][j][0][0]=(f[i][j][0][0]+f[k-1][j][0][1]*f[i-k][j][1][0]%mod*c[i-1][k-1]%mod)%mod;
				f[i][j][0][1]=(f[i][j][0][1]+f[k-1][j][0][1]*f[i-k][j-1][1][1]%mod*c[i-1][k-1]%mod)%mod;
				f[i][j][1][0]=(f[i][j][1][0]+f[k-1][j-1][1][1]*f[i-k][j][1][0]%mod*c[i-1][k-1]%mod)%mod;
				f[i][j][1][1]=(f[i][j][1][1]+
				(f[k-1][j][1][1]*f[i-k][j][1][1]-
				(f[k-1][j][1][1]-f[k-1][j-1][1][1])*(f[i-k][j][1][1]-f[i-k][j-1][1][1]))
				%mod*c[i-1][k-1])%mod;
				f[i][j][1][1]=f[i][j][1][1]%mod+mod;
//				cout<<f[i][j][1][1]<<endl;
			}
		}
	}
	cout<<((f[n][m][0][0]-f[n][m-1][0][0])%mod+mod)%mod;
	return 0;
}

