#include<bits/stdc++.h>
using namespace std;
#define ll __int128
#define mod 10000009
using namespace std;
ll kfib[90],x,y;
long long ans,T,k;
void exgcd(ll a,ll b)
{
	if(!b){x = 1,y = 0;return;}
	exgcd(b,a%b);
	ll t = x;x = y;
	y = t-a/b*x;
}
ll ksc(ll a,ll b,ll c)
{
	ll kk = 1,fin = 0;
	if(a<0)a = -a,kk = -kk;
	if(b<0)b = -b,kk = -kk;
	while(b)
	{
		if(b&1)fin = (fin+a)%c;
		a = (a+a)%c,b>>=1;
	}return fin*kk;
}
int main()
{
	freopen("fibsword.in","r",stdin);
	freopen("fibsword.out","w",stdout);
	fib[1] = 1;
	for(int i = 2;i<90;i++)fib[i] = fib[i-2]+fib[i-1];
	cin>>T;
	while(T--)
	{
		cin>>k,ans = 0;
		for(int i = 1;i<90;i++)
		{
			ll a = fib[i],b = fib[i+1];
			if(a+b>k)break;
			exgcd(a,b);
			x = (ksc(x,k%b,b)+b)%b;
			if(!x)x+=b;
			y = (k-a*x)/b;
			if(y>0)ans = (ans+(y-1)/a+1)%mod;
		}
		cout<<ans%mod<<endl;
	}
	return 0;
}


