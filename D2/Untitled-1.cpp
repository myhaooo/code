#include<iostream>
#include<cstdio>
using namespace std;
int n,k;
long long dp[10][15000][80]; 
long long state[777777] , king[77777] ;//state[]是当前状态，king[]是当前行的国王数；
long long ans , sum;

inline void inte()
{
	int tot = (1<<n) - 1;
	for(int i = 0 ; i <= tot ; i++)
		if(!((i<<1)&i))		
		{
			state[++ans] = i;
			int t = i;
			while(t)			
			{
				king[ans] += t%2;
				t>>=1;				
			}
		}
 } 

int main()
{
	cin>>n>>k;					
	inte();						
	for(int i = 1; i <= ans ; i++)	
		if(king[i] <= k)					
			dp[1][i][king[i]] = 1;
	
	for(int i = 2 ; i <= n ; i++)				
		for(int j = 1; j <= ans ; j++)				
			for(int p = 1; p <= ans ; p++)					
			{												
				if(state[j] & state[p])	continue;				 
				if(state[j] & (state[p]<<1))	continue;		 
                
				if((state[j]<<1) & state[p])	continue;		 
				for(int s = 1 ; s <= k ; s++)
				{												
					if(king[j] + s > k)	continue;			
					dp[i][j][king[j]+s] += dp[i-1][p][s];	 	
				}
			}
	
	for(int i = 1; i <= n ; i++)						 
		for(int j = 1 ; j <= ans ; j++)					
			sum += dp[i][j][k];							 
	
	cout<<sum;
	return 0;	
	
}