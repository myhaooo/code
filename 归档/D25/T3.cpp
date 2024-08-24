#include<bits/stdc++.h>
using namespace std;
#define MAXN 1110
#define mod 998244353
#define ll long long
bool be;
int n,i,j,k,d[MAXN];
ll m,a[MAXN][MAXN],c[MAXN][MAXN],f[MAXN];
bool ed;

ll power(ll a, ll b) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}

int main(){
	cin>>n>>m;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			cin>>(a[i][j]);
	for (i=1;i<=n;i++)
		if (a[i][i])
		{cout<<"0\n";return 0;}
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((a[i][j]!=a[j][i])||(a[i][j]>m))
			{cout<<"0\n";return 0;}
	for (k=1;k<=n;k++)
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				if (a[i][k]+a[k][j]<a[i][j])
				{cout<<"0\n";return 0;}
	
	for (i=1;i<=n;i++){
		c[i][0]=c[i][i]=1;
		f[i]=power(m+1,i*(i-1)/2);
		for (j=1;j<i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
			f[i]=(f[i]-f[j]*c[i-1][j-1]%mod*power(m,j*(i-j))%mod*power(m+1,(i-j)*(i-j-1)/2))%mod;
		}
	}
	
	long long ans=1;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (!a[i][j])
			{d[i]=0;d[j]++;break;}
	for (i=1;i<=n;i++)
		if (d[i]) ans=ans*f[d[i]]%mod;
	
	for (i=1;i<=n;i++)
		for (j=i+1;j<=n;j++)
			if ((d[i])&&(d[j])){
				for (k=1;k<=n;k++)
					if ((a[i][k]!=0)&&(a[k][j]!=0)&&(a[i][k]+a[k][j]==a[i][j])) break;
				if (k<=n) ans=ans*power(m-a[i][j]+1,d[i]*d[j])%mod;
				else ans=ans*(power(m-a[i][j]+1,d[i]*d[j])-power(m-a[i][j],d[i]*d[j]))%mod;
			}
	cout<<(ans+mod)%mod;
	return 0;
}