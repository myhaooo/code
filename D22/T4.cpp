#include <bits/stdc++.h>
using namespace std;
using ll = long long

const int N=25,Q=1e5+5,P=998244353;

int n,q,h,t,m;
int s[Q][N];
ll f[Q][N][N];// f i,j,k 表示从第 i 行的 j 到第 m 行的 k（或第 m 行的 k 到第 i 行的 j）的方案数
ll g[Q][N][N];// g i,j,k 表示从第 i 行的 j 到第 m−1 行的 k（或第 m+1 行的 k 到第 i 行的 j）的方案数
char ch[N];
string opt;

void Update(int now,int p1,int p2,ll dp[][N][N]){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)dp[now][i][j]=0;
	}
	for(int i=1;i<=n;i++){
		if(s[now][i])continue;
		for(int j=1;j<=n;j++){
			if(i-1>=1)dp[now][i][j]=(dp[now][i][j]+dp[p2][i-1][j])%P;
			if(i-2>=1)dp[now][i][j]=(dp[now][i][j]+dp[p1][i-2][j])%P;
			if(i+1<=n)dp[now][i][j]=(dp[now][i][j]+dp[p2][i+1][j])%P;
			if(i+2<=n)dp[now][i][j]=(dp[now][i][j]+dp[p1][i+2][j])%P;
		}
	}
	return ;
}

void Rebuild(){
	m=t;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)f[t][i][j]=0;
	}
	for(int i=1;i<=n;i++)f[t][i][i]=1-s[t][i];
	for(int i=t-1;i>=h;i--)Update(i,i+1,i+2>m?0:i+2,f);
	if(h==t)return ;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)g[t-1][i][j]=0;
	}
	for(int i=1;i<=n;i++)g[t-1][i][i]=1-s[t-1][i];
	for(int i=t-2;i>=h;i--)Update(i,i+1,i+2>=m?0:i+2,g);
	return ;
}

void Insert(){
	scanf("%s",ch+1);
	++t;
	for(int i=1;i<=n;i++)s[t][i]=(ch[i]=='#');
	if(h<=t&&h>m){
		Rebuild();
		return ;
	}
	Update(t,t-1,t-2<m?0:t-2,f);
	if(t!=m+1){
		Update(t,t-1,t-2<=m?0:t-2,g);
		return ;
	}
	for(int i=1;i<=n;i++)g[t][i][i]=1-s[t][i];
	return ;
}

void Delete(){
	++h;
	if(h<=t&&h>m)Rebuild();
	return ;
}

void Query(){
	ll ans=0;
	int x,y;
	cin>>x>>y;
	if(s[h][x]||s[t][y]){
		cout<<"0\n";
		return ;
	}
	for(int i=1;i<=n;i++)ans=(ans+f[h][x][i]*f[t][y][i]%P)%P;
	if(t<=m||h>=m){
		cout<<ans<<'\n';
		return ;
	}
	for(int i=1;i<=n;i++){
		if(i-1>=1)ans=(ans+g[h][x][i]*g[t][y][i-1]%P)%P;
		if(i+1<=n)ans=(ans+g[h][x][i]*g[t][y][i+1]%P)%P;
	}
	cout<<ans<<'\n';
	return ;
} 

int main(){
	cin>>n>>q;
	h=1,t=0;
	for(int i=1;i<=q;i++){
		cin>>opt;
		switch(opt[0]){
			case 'A':{
				Insert();
				break;
			}case 'D':{
				Delete();
				break;
			}case 'Q':{
				Query();
				break;
			}
		}
	}
	return 0;
}