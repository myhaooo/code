#include<bits/stdc++.h>
#define MAXN 1000005
#define int long long
using namespace std;
int T,n,a,b,x,y,z;
int dp[MAXN];
struct node{
	int id;
	double c;
}p[5];
inline bool cmp(node x,node y){
	return x.c<y.c;
}
const int inf=1e18;
int ans,refl[5],cnt;
inline void Reset(){
	ans=inf;
	cnt=0;
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		Reset();
		scanf("%lld%lld%lld%lld%lld%lld",&n,&a,&b,&x,&y,&z);
		y=min(y,a*x);
		z=min(z,b*x);
		if(y*b>z*a)swap(y,z),swap(a,b);
		if(n/a>=a-1){
			for(int i=0;i<=a-1;i++){
				cnt=n-i*b;
				if(cnt>=0)ans=min(ans,i*z+cnt/a*y+cnt%a*x);
			}
		}
		else for(int i=0;i<=n/a;i++)cnt=n-i*a,ans=min(ans,i*y+cnt/b*z+cnt%b*x);
		printf("%lld\n",ans);	
	}
	return 0;
}