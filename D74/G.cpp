#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10,M=1e7+10;
int T,n,a[N],tire[M][2],f[M][2][2],dp[N],tot;
//f[x][0/1][0/1]表示x及其之前的都相等,x下一位开始,i为0/1,a[i]为0/1的dp最大值. 
inline int query(int id,int val)
{
	int p=1,ans=0;
	for(int i=30;i>=0;--i)
	{
		int c2=(val&(1<<i))?0:1,c1=(id&(1<<i))?1:0;
		ans=max(ans,f[p][c2][c1]); 
		int ch=((id^val)&(1<<i))?1:0;
		if(!tire[p][ch]) break;
		p=tire[p][ch];
	}
	return ans;
}
inline void insert(int id,int val)
{
	int p=1;
	for(int i=30;i>=0;--i)
	{
		int c2=(val&(1<<i))?1:0,c1=(id&(1<<i))?1:0;
		f[p][c1][c2]=max(f[p][c1][c2],dp[id]);
		int ch=((id^val)&(1<<i))?1:0;
		if(!tire[p][ch]) tire[p][ch]=++tot;
		p=tire[p][ch];
	} 
}
inline void solve()
{
	cin>>n;
	for(int i=0;i<n;++i) cin>>a[i];
	tot=1;
	int ans=0;
	for(int i=0;i<n;++i)
	{
		int temp=query(i,a[i]);
		dp[i]=temp+1;
		insert(i,a[i]);
		ans=max(ans,dp[i]);
	}
	cout<<ans<<endl;
	for(int i=1;i<=tot;++i)
		for(int j=0;j<2;++j)
		{
			tire[i][j]=0;
			for(int k=0;k<2;++k) f[i][j][k]=0;
		}		 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--) solve();
	return 0;
}
