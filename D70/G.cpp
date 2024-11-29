 #include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200005
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int T,n,rt,cnt,a[N],f[N],t[N<<9][2],ans;
inline void insert(int x)
{
	int p=rt;
	for(int i=30;~i;i--)
	{
		int k=(x>>i)&1;
		if(!t[p][k]) t[p][k]=++cnt;
		p=t[p][k];
	}
}
inline int query(int x)
{
	int p=rt,res=0;
	for(int i=30;~i;i--)
	{
		int k=(x>>i)&1;
		if(t[p][k^1]) res^=(1<<i),p=t[p][k^1];
		else p=t[p][k];
	}
	return res;
}
void solve(int l,int r)
{
	if(l==r) return;
	int mid=l+r>>1,p=0;
	solve(l,mid),solve(mid+1,r);
	rt=++cnt,f[l-1]=0;
	for(int i=l;i<=r;i++) f[i]=f[i-1]^a[i];
	for(int i=mid+1,j=mid+1;i<=r;i++)
	{
		p=max(p,a[i]);
		while(j>l&&a[j-1]<=p) j--,insert(f[j-1]);
		ans=max(ans,query(f[i]^p));
	}
	rt=++cnt,p=f[r+1]=0;
	for(int i=r;i>=l;i--) f[i]=f[i+1]^a[i];
	for(int i=mid,j=mid;i>=l;i--)
	{
		p=max(p,a[i]);
		while(j<r&&a[j+1]<p) j++,insert(f[j+1]);
		ans=max(ans,query(f[i]^p));
	}
}
int main()
{
	T=read();
	while(T--)
	{
		cnt=ans=0,n=read();
		for(int i=1;i<=(n<<9);i++) t[i][0]=t[i][1]=0;
		for(int i=1;i<=n;i++) a[i]=read();
		solve(1,n);
		printf("%d\n",ans);
	}
	return 0;
}
