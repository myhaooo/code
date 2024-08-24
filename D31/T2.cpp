#include<bits/stdc++.h>
using namespace std;
const int N=2005,mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int mul(int a,int b){return 1ll*a*b%mod;}
int n,m,tot,ans;
char s[N][N];
int s1[N],s2[N];
int g[N],f1[N],f2[N];
int p1[N],p2[N];
int sum[N][N];
inline int S(int x1,int y1,int x2,int y2){
	return sum[x2][y2]-sum[x1][y2]-sum[x2][y1]+sum[x1][y1];
}
int cnt1[N],cnt2[N];
void solve(int k1){
	int k2=tot*2/k1,c1=0,c2=0;
	for(int i=1;i<=n;i++)if(s1[i]!=s1[i-1]&&s1[i]%k1==0)p1[++c1]=i;
	for(int i=1;i<=m;i++)if(s2[i]!=s2[i-1]&&s2[i]%k2==0)p2[++c2]=i;
	if(c1<<1 !=k2||c2<<1!=k1)return;
	for(int i=1;i<=c1;i++)
		for(int j=1;j<=c2;j++)
			if(S(p1[i-1],p2[j-1],p1[i],p2[j])!=2)return;
	for(int i=1;i<=c1;i++)cnt1[i]=0;
	for(int i=1;i<=c2;i++)cnt2[i]=0;
	for(int i=1;i<=n;i++)if(s1[i]%k1==0)cnt1[s1[i]/k1]++;
	for(int i=1;i<=m;i++)if(s2[i]%k2==0)cnt2[s2[i]/k2]++;
	int res=1;
	for(int i=1;i<c1;i++)res=mul(res,cnt1[i]);
	for(int i=1;i<c2;i++)res=mul(res,cnt2[i]);
	ans=add(ans,res);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
			if(s[i][j]=='Y')s1[i]++,s2[j]++,sum[i][j]++;
		}
	}
	for(int i=1;i<=n;i++)s1[i]+=s1[i-1];
	for(int i=1;i<=m;i++)s2[i]+=s2[i-1];
	tot=s1[n];
	if(tot&1)return cout<<0,0;
	for(int i=2;i<=n*m;i+=2)if(tot%i==0)solve(i);
	cout<<ans<<endl;
	return 0;
}