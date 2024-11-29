#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Tree __
	int l,r;
	int mn; //区间最小值 
	int AG; //区间最小值出现次数 
	int DYG; //区间次小值出现次数 
	int lazy;
___t[1200010];
int n,a[300010],p[300010],ans;
void update(int p) __
	t[p].mn=min(t[p<<1].mn,t[p<<1|1].mn);
	t[p].AG=t[p<<1].AG*(t[p<<1].mn==t[p].mn)+t[p<<1|1].AG*(t[p<<1|1].mn==t[p].mn);
	t[p].DYG=(t[p<<1].mn==t[p].mn)*t[p<<1].DYG+(t[p<<1].mn==t[p].mn+1)*t[p<<1].AG+(t[p<<1|1].mn==t[p].mn)*t[p<<1|1].DYG+(t[p<<1|1].mn==t[p].mn+1)*t[p<<1|1].AG;
___
void spread(int p) __
	t[p<<1].mn+=t[p].lazy;
	t[p<<1|1].mn+=t[p].lazy;
	t[p<<1].lazy+=t[p].lazy;
	t[p<<1|1].lazy+=t[p].lazy;
	t[p].lazy=0;
___
void build(int p,int l,int r) __
	t[p].l=l,t[p].r=r;
	if(l==r) __
		t[p].AG=1;
		return ;
	___
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	update(p);
___
void add(int p,int l,int r,int val) __
	if(t[p].l>r||t[p].r<l) return ;
	if(t[p].l>=l&&t[p].r<=r) __
		t[p].mn+=val;
		t[p].lazy+=val;
		return ;
	___
	spread(p);
	add(p<<1,l,r,val);
	add(p<<1|1,l,r,val);
	update(p);
___
int ask(int p,int l,int r) __
	if(t[p].l>r||t[p].r<l) return 0;
	if(t[p].l>=l&&t[p].r<=r) return t[p].AG*(t[p].mn<=2)+t[p].DYG*(t[p].mn<=1);
	spread(p);
	return ask(p<<1,l,r)+ask(p<<1|1,l,r);
___
signed main()
__
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),p[a[i]]=i;
	build(1,1,n);
	for(int i=1;i<=n;i++) __
		add(1,1,i,1);
		if(a[p[i]-1]<i&&a[p[i]-1]) add(1,1,a[p[i]-1],-1);
		if(a[p[i]+1]<i&&a[p[i]+1]) add(1,1,a[p[i]+1],-1);
		ans+=ask(1,1,i-1);
	___
	printf("%lld",ans);
	return 0;
___
