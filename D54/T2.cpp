#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
int n,P,now,maxn,ans[2],K,s[MAXN],t[MAXN];
signed main()
{
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	cin>>n>>K;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	while(K--){
		cin>>P;
		ans[0]=ans[1]=0;
		maxn=now=0;
		for(int i=1;i<P;i++)
		{
			t[s[i]]++;
			maxn=max(maxn,s[i]);
		}
		for(int i=P;i<=n;i++)
		{
			if(s[i]>=maxn)	ans[now]+=s[i];
			else
			{
				t[s[i]]++;
				t[maxn]--;
				ans[now]+=maxn;
				while(!t[maxn])	maxn--;
			}
			now=(!now);
		}
		for(int i=maxn;i>=1;i--)
			while(t[i])
			{
				ans[now]+=i;
				t[i]--;
				now=(!now);
			}
	cout<<(ans[0]-ans[1])<<"\n";
	}
	return 0;
}
