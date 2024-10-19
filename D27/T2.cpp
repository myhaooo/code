#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

const int MAXN=1e3+5;
const long long INF=1e18;
int sum[MAXN],maxl[MAXN],maxr[MAXN];
long long dp[MAXN];
int main()
{
	int T;
	cin>>T;
	int n,k;
	while(T--)
	{
		scanf("%d %d",&n,&k);
		for(int i=1;i<=n;++i) scanf("%d",&sum[i]),sum[i]+=sum[i-1];
		int tmp=0;
		for(int i=1;i<=n;++i)
		{
			maxl[i]=sum[i]-tmp;
			tmp=min(tmp,sum[i]);
		}
		tmp=sum[n];
		for(int i=n;i>=1;--i)
		{
			maxr[i]=tmp-sum[i-1];
			tmp=max(tmp,sum[i]);
		}
		memset(dp,-0x3f,sizeof(dp));
		dp[1]=0;
		long long ans=0;
		for(int j=1;j<=min(k,5000);++j)
		{
			if(j&1)
			{
				long long maxn=-INF;
				for(int i=1;i<=n;++i)
				{
					maxn=max(maxn,dp[i]-sum[i-1]);
					dp[i]=maxn+sum[i]>=0?maxn+sum[i]:-INF;
					ans=max(ans,dp[i]+max(0ll,1ll*(k-j)*maxl[i]));
				}
			}
			else
			{
				long long maxn=-INF;
				for(int i=n;i>=1;--i)
				{
					maxn=max(maxn,dp[i]+sum[i]);
					dp[i]=maxn-sum[i-1]>=0?maxn-sum[i-1]:-INF;
					ans=max(ans,dp[i]+max(0ll,1ll*(k-j)*maxr[i]));
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}