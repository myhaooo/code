#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int N = 1e6 + 5;
int n, a[N], s[N], dp[N], ans = LONG_LONG_MAX, del = LONG_LONG_MAX;
signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin>>n; for(int i=1; i<=n; ++i) cin>>a[i], s[i] = s[i-1] + abs(a[i] - a[i-1]);
    memset(dp, 0x7f, sizeof(int) * (n+1)); dp[0] = 0;
    if(n >= 1e5) del = 1e4;
    if(n >= 1e6) del = 1e3;
    for(int i=1; i<=n; ++i){
        for(int j=max(0ll, i-del); j<i; ++j){
            dp[i] = min(dp[i], dp[j] + s[i-1] - s[j] + abs(a[i] - (j-1<0?0:a[j-1])));
        }
    }
    for(int i=1; i<=n; ++i) ans = min(ans, dp[i] + s[n] - s[i]);
    return cout<<ans, 0;
}
