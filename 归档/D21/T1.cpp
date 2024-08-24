#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353,MAXN=2005;

int d,fac[MAXN],inv[MAXN],fm[MAXN];
int ans,n,m,sum[MAXN][MAXN];//前缀和
int dp[MAXN][MAXN];//天数i，给出j块饼干

int qpow(int a,int b) {
    int num=1;
    while(b){
        if(b&1)num=num*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return num;
}
inline int getC(int x,int y){
	if(y>x)return 0;
	if(!y)return 1;
	return fac[x]*inv[x-y]%mod*inv[y]%mod;
}
 
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
    	//fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif

    fac[1]=1;
    for(int i=2;i<=2001;i++)
        fac[i]=(fac[i-1]*i)%mod;
    inv[2001]=qpow(fac[2001],mod-2);
    for(int i=2000;i>=1;i--)
        inv[i]=(inv[i+1]*(i+1))%mod;

    
    while(1) {
        cin>>n>>d>>m;
        if(n==0||d==0||m==0)exit(0);
        ans=0;
        memset(dp,0,sizeof dp);
        memset(fm,0,sizeof fm);
        fm[1]=d%mod;
        for(int i=2;i<=n;i++)
            fm[i]=(fm[i-1]*((d-i+1)%mod))%mod;
        dp[0][0]=1;
        for(int i=0;i<=n;i++)
            sum[0][i]=1;
        for(int i=1;i<=min(n,d);i++) {
            for(int j=1;j<=n;j++) {
                if(j-m+1>0)
                    dp[i][j]=((sum[i-1][j-1]-sum[i-1][j-m])%mod+mod)%mod;
                else
                    dp[i][j]=sum[i-1][j-1]%mod;
                sum[i][j]=(sum[i][j-1]+dp[i][j])%mod;
            }
            ans=(ans+((dp[i][n]%mod*inv[i]%mod)*fm[i]%mod)+mod)%mod;
        }
        cout<<ans<<'\n';
    }
    return 0;
}