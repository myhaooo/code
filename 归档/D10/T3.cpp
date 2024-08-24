#include <bits/stdc++.h>
#define int long long
#define double long double
#define clear(a) memset(a,0,sizeof(a));
using namespace std;
int T,n,m;
double dp[500],a[500],b[500],g[500],ls,ans;
double qpow(double a, int b) {
  double res = 1;
  while (b > 0) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}
signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif
    #define 下面是代码 上面是模版------------------
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i]>>b[i];
		}
        clear(dp);
        clear(g);
		dp[0]=1;
		for(int i=1;i<=n;i++){
			for(int j=m-1;j>=0;j--){
				ls=dp[j]*qpow(1-a[i],m-j);
				g[i]+=dp[j]-ls;
				dp[j+1]+=dp[j]-ls;
				dp[j]=ls;
			}
		}
		ans=0;
		for(int i=1;i<=n;i++){
            //cout<<fixed<<setprecision(40)<<g[i]<<" \n";
			ans=ans+g[i]*b[i];
		}
		cout<<fixed<<setprecision(40)<<ans<<"\n";
	}
	return 0;
}
