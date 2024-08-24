/*
莫听穿林打叶声，何妨吟啸且徐行。竹杖芒鞋轻胜马，谁怕？一蓑烟雨任平生。
料峭春风吹酒醒，微冷，山头斜照却相迎。回首向来萧瑟处，归去，也无风雨也无晴。
*/
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 10;
const int MOD = 998244353;

int n, k;
int dp[MAXN][MAXN];

int main(){
    cout<<1;
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    #define clear(a) memset(a, 0, sizeof(a))
    #else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #include "../local.h"
    #endif
    cin>>n>>k;
    dp[0][0] = 1;
    for(int i=1; i<=n; i++){
        for(int j=i; j>=1; j--){
            dp[i][j] = dp[i-1][j-1];
            if(i>=2*j) 
            dp[i][j] += dp[i][j*2];
            dp[i][j] %= MOD;
        }
    }
    cout<<dp[n][k]<<endl;
    return 0;
}
