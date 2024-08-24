#include <bits/stdc++.h>          
using namespace std;              
bool ed;                          
int d,B,n;                        
constexpr int m=5,N=5005;         
string s;          
int dp[N][N][2];   
bitset<N> combo; 
bool be;           
                   
signed main(){     
    ios::sync_with_stdio(false);  
    #ifndef LOCAL                 
        #define                                   NDEBUG            
        cin.tie(0),cout.tie(0);   
    #else                         
	    fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);    
        freopen("in.in","r",stdin);    
        freopen("out.out","w",stdout); 
        #include "../local.h"          
    #endif                             
	cin>>d>>B;                         
    cin>>s;                            
	n=s.length();                      
	memset(dp,-0x3f,sizeof(dp));       
	dp[0][0][0]=dp[0][0][1]=0;         
	int ls=0;                          
	for(int i=1;i<=n;i++){             
		if(s[i-1]=='0') ls=0;          
		else{                          
			ls++;                      
			if(ls>=d)  combo[i]=true;  
		}                              
	}                                  
	for(int i=1;i<=n;i++){             
		int minn=min(i,B);             
		for(int j=0;j<=minn;j++){      
			if(s[i-1]=='0'){           
				dp[i][j][0]=max({dp[i][j][0],dp[i-1][j][0],dp[i-1][j][1]});                 
			}                     
			else if(s[i-1]=='1'){ 
				if(j>=1) dp[i][j][       
				if(j>=d&&i>=d&&combo[i]) dp[i][j][1]=max({dp[i][j][1],dp[i-d][j-d][0]+1,dp[i-d][j-d][1]+1});        
			}                            
			else /*if(s[i-1]=='?')*/ {   
				dp[i][j][0]=max({dp[i][j][0],dp[i-1][j][0],dp[i-1][j][1]});                                         
				if(j>=1) dp[i][j][1]=max({dp[i][j][1],dp[i-1][j-1][0],dp[i-1][j-1][1]});                            
				if(j>=d&&i>=d&&combo[i]) dp[i][j][1]=max({dp[i][j][1],dp[i-d][j-d][0]+1,dp[i-d][j-d][1]+1});        
			}   
		}       
	}           
	int maxn=max(dp[n][B][0],dp[n][B][1]);            
	maxn=min(maxn,n-B);
	int ans=B*2-n+maxn+1;
    if(ans<=0){cout<<1;return 0;}                     
	if(dp[n][B][0]<dp[n][B][1]&&ans%m==0)ans=ans/m;   
	else ans=ans/m+1;     
	cout<<ans<<"\n";   
	return 0;          
}
