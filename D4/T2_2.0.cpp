#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 2,M = 102;
int a[N],sum[N],dp[N][M],pos[2][M],n,k,p;
//dp[i][j]:前 i 个数分成 j 组的最小和
int main() {
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    cin.tie(0),cout.tie(0);
    #else
    #include "../local.h"
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
    cin>>n>>k>>p;

    memset(dp,0x3f,sizeof(dp));

    for (int i = 1;i <= n; ++ i) {
        cin>>a[i];
        sum[i] = (sum[i - 1] + a[i]) % p;
        dp[i][1] = sum[i];

    }

    for (int i = 1;i <= n; ++i) {
        for (int j = 2 ; j <= k; ++j) {
            dp[i][j] = min(dp[i][j],dp[pos[i & 1 ^ 1][j - 1]][j - 1] + ((sum[i] - sum[pos[i & 1 ^ 1][j - 1]]) % p + p) % p);
        }
        //pos[i & 1 ^ 1][j - 1]表示在前i个元素中选择j-1个元素的最优解的位置。
        for (int j = 0;j <= k; ++ j) {
            pos[i & 1][j] = pos[i & 1 ^ 1][j];
            if (dp[i][j] < dp[pos[i & 1][j]][j]) {
                pos[i & 1][j] = i;
            }
        }
    }
    cout<<dp[n][k];
    
    return 0;
}