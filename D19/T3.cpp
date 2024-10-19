#include<cstdio>
#include<iostream>
using namespace std;
#define int long long
#define sum (dp[i][l]*dp[i][r])%mod
int dp[301][602],n,k,mod;
signed main(){
    scanf("%lld%lld",&n,&mod);
    dp[1][0]=dp[1][1]=1;
    for(int i=1;i<n;++i) for(int l=0;l<=min(n-i+2,i<=9?(1ll<<i)-1:n-i+2);++l) for(int r=0;r<=min(n-i+2-l,i<=9?(1ll<<i)-1:n-i+2);++r){
        (dp[i+1][l+r]+=sum)%=mod;//直接转移
        (dp[i+1][l+r+1]+=sum)%=mod;//只多了一个根自己是路径
        (dp[i+1][l+r]+=(sum<<1)*(l+r)%mod)%=mod;//只把一条边伸长到根节点，双向
        (dp[i+1][l+r-1]+=l*r%mod*(sum<<1)%mod)%=mod;//左右通过根节点相连
        (dp[i+1][l+r-1]+=sum*(l*(l-1)%mod+r*(r-1)%mod)%mod)%=mod;//同侧通过根节点相连
    }
    printf("%lld\n",dp[n][1]%mod);
}

