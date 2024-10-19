#include<iostream>
#include<cstdio>
#include<cstring>
#define N 1005
using namespace std;
int n,m,f[2][N],a[N],b[N],nxt[3][3]={{1,0,0},{1,2,0},{1,0,3}},dp[2][32769][3],ans[N],now,sta[32769][3];
char ch[N];
const int mod=1e9+7;
void init()//24300
{
	for(int s=0;s<(1<<m);s++)
	{
		for(int k=0;k<m;k++)f[0][k+1]=f[0][k]+((s>>k)&1);
		for(int j=0;j<=2;j++)
		{
			for(int k=1;k<=m;k++)
			{
				f[1][k]=max(f[1][k-1],f[0][k]);
				if(b[k]==j)f[1][k]=max(f[1][k],f[0][k-1]+1);
			}
			int t=0;
			for(int i=1;i<=m;i++)if(f[1][i]>f[1][i-1])t|=(1<<(i-1));
			sta[s][j]=t;
		}
	}	
}
int main()
{
	cin>>n>>m;
	cin>>(ch+1);
	for(int i=1;i<=m;i++)
	{
		if(ch[i]=='N')b[i]=0;
		if(ch[i]=='O')b[i]=1;
		if(ch[i]=='I')b[i]=2;
	}
	init();
	dp[0][0][0]=1;
	for(int i=1;i<=n;i++)
	{
		memset(dp[now^1],0,sizeof(dp[now^1]));
		for(int s=0;s<(1<<m);s++)
		{
			for(int j=0;j<=2;j++)
			{
				for(int k=0;k<=2;k++)
				{
					if(j==2&&k==2)continue;
					int ff=nxt[j][k];
					dp[now^1][sta[s][k]][ff]+=dp[now][s][j];
					dp[now^1][sta[s][k]][ff]%=mod;
				}
			} 
		}
		now^=1;
	}
	for(int s=0;s<(1<<m);s++)
	{
		for(int j=0;j<=2;j++)
		{
			int ff=0,ll=s;
			while(ll){if(ll%2==1)ff++;ll/=2;}
			ans[ff]+=dp[now][s][j];
			ans[ff]%=mod;
		}
	}
	for(int i=0;i<=m;i++)cout<<ans[i]<<endl;
	return 0; 
}