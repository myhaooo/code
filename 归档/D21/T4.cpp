#include<bits/stdc++.h>
using namespace std; 
const int MAXN = 15;
const int MAXNN = 2055;
int n,nn,m,ans;
int dp[MAXNN][MAXNN],war[MAXNN][MAXN],farmer[MAXNN][MAXN];

void dfs(int x,int s,int d)//s为祖先状态 1打仗 0后勤，d为子树大小
{
    for(int i = 0;i <= d;++ i)
        dp[x][i] = 0;
    if(d == 1)
    {
        for(int i = 0;i < n-1;++ i)
            if(s >> i & 1)
                dp[x][1] += war[x][i+1];
            else
                dp[x][0] += farmer[x][i+1];
        return ;
    }
    for(int cas = 0;cas < 2;++ cas)
    {
        dfs(x<<1,s<<1|cas,d>>1);
        dfs(x<<1|1,s<<1|cas,d>>1);
        for(int i = 0;i <= min(d,m);++ i)
            for(int j = 0;j <= min(d,m);++ j)
                dp[x][i+j] = max(dp[x][i+j],dp[x<<1][i]+dp[x<<1|1][j]);
    }
}

int main()
{

    cin>>n>>m;
    nn = 1 << (n-1);
    for(int i = nn;i < nn+nn;++ i)
        for(int j = 1;j < n;++ j)
            cin>>war[i][j];
    for(int i = nn;i < nn+nn;++ i)
        for(int j = 1;j < n;++ j)
            cin>>farmer[i][j] ;
    dfs(1,0,(1<<n)-1);
    for(int i = 0;i <= m;++ i)
        ans = max(dp[1][i],ans);
    cout<<ans<<'\n';
    return 0;
}