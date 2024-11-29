#include<bits/stdc++.h>
using namespace std;
#define int __int128
const long long mod=1e9+7;
signed n,q;
int S[200005];
int t[60][200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	long long m;
	cin>>n>>m>>q;
	long long l=-m;
	for(int i=0;i<n;i++)
	{
		char c;
		cin>>c;
		if(c=='1')S[i]=i,l=i;
		else S[i]=l;
	}
	if(l!=-m)for(int i=0;i<n&&S[i]==-m;i++)S[i]=l-n;
	for(int j=0;j<n;j++)
	{
		int k=(j+m)%n;
		t[0][j]=max(j+m-k+S[k],1ll*(j+1));
	}
	for(int i=1;i<60;i++)
	{
		for(int j=0;j<n;j++)
		{
			int k=t[i-1][j]%n;
			t[i][j]=t[i-1][k]-k+t[i-1][j];
		}
	}
	while(q--)
	{
		long long s1,k;
		cin>>s1>>k;
		int s=s1-1;
		for(int i=0;k;k>>=1,i++)
		{
			if(k&1)
			{
				int tt=s%n;
				s=t[i][tt]+s-tt;
			}
		}
		cout<<(long long)((s+1)%mod)<<endl;
	}
}
