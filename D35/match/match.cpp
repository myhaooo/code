#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f3f3f
const int N=5e3+5;
int a[N];
int dp[2][N][2];
signed main()
{
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=0;i<=n;i++){
    	dp[1][i][0]=inf;
    	dp[1][i][1]=inf;
	}
    dp[1][0][0]=0;
    for(int i=2;i<=n;++i)
    {
        dp[i&1][0][0]=dp[(i-1)&1][0][0];
        for(int j=1;j<=m;++j)
        {
            dp[i&1][j][0]=min(dp[(i-1)&1][j][0],dp[(i-1)&1][j][1]);
            dp[i&1][j][1]=dp[(i-1)&1][j-1][0]+(a[i]-a[i-1]);
        }
    }
    cout<<min(dp[n&1][m][0],dp[n&1][m][1]);
    return 0;
}
