#include<bits/stdc++.h>
#define int long long
#define ls x<<1
#define rs x<<1|1
using namespace std;
const int N=1e6+10;
int n,m,ans,las[N],s[N],val[N];
struct Segment_Tree
{
	int dat,laz;
}tre[N<<2];
vector<int> v[N];
void push_down(int x)
{
	if(!tre[x].laz)	return ;
	tre[ls].laz+=tre[x].laz;
	tre[rs].laz+=tre[x].laz;
	tre[ls].dat+=tre[x].laz;
	tre[rs].dat+=tre[x].laz;
	tre[x].laz=0;
}
void push_up(int x)
{
	tre[x].dat=max(tre[ls].dat,tre[rs].dat);
}
void update(int x,int l,int r,int L,int R,int num)
{
	if(L<=l&&r<=R)
	{
		tre[x].dat+=num;
		tre[x].laz+=num;
		return ;
	}
	push_down(x);
	int mid=(l+r)>>1;
	if(L<=mid)	update(ls,l,mid,L,R,num);
	if(R>mid)	update(rs,mid+1,r,L,R,num);
	push_up(x);
}
signed main()
{
	freopen("flower.in","r",stdin);
	freopen("flower.out","w",stdout);
	cin>>n>>m; 
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		v[s[i]].push_back(i);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<v[i].size();j++)
			las[v[i][j]]=v[i][j-1];
	for(int i=1;i<=m;i++)
		cin>>val[i];
	for(int i=1;i<=n;i++)
	{
		int num=s[i];
		if(las[i])	update(1,1,n,max(1ll,las[las[i]]),las[i],-val[num]);
		update(1,1,n,las[i]+1,i,val[num]);
		ans=max(ans,tre[1].dat);
	}
	cout<<ans<<"\n";
	return 0;
}
