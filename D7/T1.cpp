#include <bits/stdc++.h>
#define int __int128
using namespace std;

inline int read()
{
	int w{1},x{};
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return w * x;
 } 
 inline void write(int x)
 {
 	if(x<0)x=-x,putchar('-');
 	if(x>9) write(x/10);
	putchar(x%10+'0');
 }
 inline void writeln(int x)
 {
 	write(x);putchar(10);
 }
const int MOD1 = 1e9+5;
const int MOD2 = 1e9+7;
int qp(int a,int b,int mod)
{
	int res{1};
	while(b)
	{
		if(b&1) (res *= a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return res;
}
int getans(int a,int b)
{
	int res1 = qp(b,MOD1,MOD2);
	(res1 *= a) %= MOD2;
	return res1;
}
const int N = 1e5+5;
int a[N];
//mod <= 300;
int sum[N];
int b[N];
int c[N];
int n,m,mod;

signed main()
{
	#ifdef LOCAL
	freopen("in.in","r",stdin);
	#endif
	n = read(),m = read(),mod = read();
	for(int i{1};i<=n;i++) a[i] = read(),sum[a[i]]++;
	for(int i{0};i<mod;i++) b[i] = sum[i];
	for(int T{2};T<=m;T++)
	{
		for(int i{0};i<mod;i++) // b
			for(int j{1};j<mod;j++) // sum
				c[(i*j)%mod] += b[i] * sum[j];
		
		for(int i{0};i<mod;i++) b[i]=c[i]%MOD2,c[i]=0;
		
	}
	
	int sum1{},sum2{qp(n,m,MOD2)};
	for(int i{};i<mod;i++)sum1+=b[i]*i%MOD2;
	int gcd = __gcd(sum1,sum2);
	sum1/=gcd,sum2/=gcd;
	writeln(getans(sum1,sum2));
	return 0;
}