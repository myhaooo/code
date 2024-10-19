#include<bits/stdc++.h>
using namespace std;
#define inf 0x3f3f3f3f
int a;
const int mod=1e9+7;
int b,c,d;
map<int,int>kk,bb;
int K(int x)
{
	if(x==1)
	{
		return 1;
	}
	if(kk[x])
	{
		return kk[x];
	}
	kk[x]=((K(x>>1)<<1)+(K(((x+1)>>1))<<1)+1)%mod;
	return kk[x];
}
int B(int x)
{
	if(x==1)
	{
		return 0;
	}
	if(bb[x])
	{
		return bb[x];
	}
	bb[x]=(B(x>>1)+B((x+1)>>1)+K(x>>1))%mod;
	return bb[x];
}
int got(int x,int y)
{
	return (K(x)*y+B(x))%mod;
}
int found(int x,int lt,int rt,int left,int right)
{
	if(lt<=left&&right<=rt)
	{
		return got(right-left+1,x);
	}
	int mid=(left+right)>>1,rn=0;
	if(lt<=mid)
	{
		rn+=found((x<<1)%mod,lt,rt,left,mid);
		rn%=mod;
	}
	if(rt>mid)
	{
		rn+=found((x<<1|1)%mod,lt,rt,mid+1,right);
		rn%=mod;
	}
	return rn;
}
int main()
{
	scanf("%d",&a);
	while(a--)
	{
		scanf("%lld%lld%lld",&b,&c,&d);
		printf("%lld\n",found(1,c,d,1,b));
	}
	return 0;
}
