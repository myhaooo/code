#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
const int INF=1e9;
int a[MAXN],b[MAXN],minn[MAXN];
bool used[MAXN];
int main()
{
	int T;
	cin>>T;
	int n;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;++i) used[i]=0;
		for(int i=1;i<=n;++i) cin>>a[i],used[a[i]]=1,b[a[i]]=i;
		minn[n+1]=INF;
		for(int i=n;i>=1;--i) minn[i]=min(minn[i+1],(a[i]>0)?a[i]:INF);
		priority_queue< int,vector<int>,greater<int> >q;
		for(int i=1;i<=n;++i) if(!used[i]) q.push(i);
		int pos=n;
		for(int i=1;i<n;++i)
		{
			if(!a[i])
			{
				if(minn[i]>q.top()) a[i]=q.top(),q.pop();
				else
				{
					a[i]=minn[i],pos=b[a[i]];
					break;
				}
				continue;
			}
			if(a[i+1])
			{
				if(a[i]>a[i+1])
				{
					pos=i,q.push(a[i]);
					break;
				}
			}
			else
			{
				if(a[i]>q.top())
				{
					pos=i,q.push(a[i]);
					break;
				}
			}
		}
		for(int i=1;i<=n;++i)
		{
			if(a[i] || i==pos) continue;
			a[i]=q.top(),q.pop();
		}
		for(int i=1;i<=n;++i) if(i!=pos) printf("%d ",a[i]);
		putchar('\n');
	}
	return 0;
}
