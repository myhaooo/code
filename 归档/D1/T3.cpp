#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int p=1e9+7;
int n,pr[1000006],tot,cnt[1000006];
ll fac[1000006];
bool vis[1000006];
void get_prime(int x)
{
	for(int i=2;i<=x;i++)
	{
		if(!vis[i])
		{
			pr[++tot]=i;
		}
		for(int j=1;i*pr[j]<=x;j++)
		{
			vis[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
}
void get_rt(int x)
{
	int tmp=1;
//	printf("%d ",x);
	if(!vis[x]&&x*2>n)
	{
		cnt[1]++;
	//	printf("1\n");
		return;
	}
	for(int i=1;pr[i]*pr[i]<=x;i++)
	{
		if(!vis[x]) break;
		if(x%pr[i]==0)
		{
			tmp*=pr[i];
			while(x%pr[i]==0) x/=pr[i];
		}
	}
	tmp*=x;
	cnt[tmp]++;
//	printf("%d\n",tmp);
}
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
int b[35],a[35];
ll ans;

int cnt1[1000006];
int main()
{
	get_prime(1e6);
	scanf("%d",&n);
	fac[0]=1;
	for(int i=1;i<=n;i++)
	{
		fac[i]=fac[i-1]*i%p;
	}
	cnt[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			int tmp=n/i;
			cnt1[tmp]++;
		}
	}
	ans=1;
	for(int i=1;i<=n;i++)
	{
		ans=ans*fac[cnt[i]]%p;
	}
	for(int i=2;i<=n;i++)
	{
		ans=ans*fac[cnt1[i]]%p;
	}
	printf("%lld",ans);
	return 0;
}
