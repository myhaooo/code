#include<bits/stdc++.h>
#define int long long 
#define val(x,y) ((x*x-2*x*y+y*y-x+y)/2)
using namespace std;
const int MAXN=1e5+5;
int n,a[MAXN],pos[MAXN],dp[MAXN];
signed main(){
	ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        freopen("skip.in","r",stdin);
        freopen("skip.out","w",stdout);
        cin.tie(0),cout.tie(0);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n"
        , abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
		//freopen("out.out","w",stdout);
        //#include "../local.h"
    #endif

	
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		dp[i]=LLONG_MIN;
		for(int j=0;j<i;j++){
			if(j!=0 && a[i]<a[j])continue;
			dp[i]=max(dp[i],dp[j]-val(i,j)+a[i]);
		}
		if((double)clock()/CLOCKS_PER_SEC>=1.48)break;
	}
	
	int ans=LLONG_MIN;
	for(int i=1;i<=n;i++){
		ans=max(ans,dp[i]-val(i,n));
	}
	cout<<ans;
}
