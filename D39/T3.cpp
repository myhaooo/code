#include<bits/stdc++.h>
using namespace std;
#define int long long
deque<int>q;
const int maxn=1e7+5;
const int mod=998244353;
char c[maxn];
int t,n,pos[maxn],cnt,all,dis[maxn],cf[maxn],sum[maxn],ans,num,ori;
bool ans1[maxn];
int qpow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
signed main(){
    freopen("chuan.in","r",stdin);
	freopen("chuan.out","w",stdout);
	cin>>t;
	scanf("%s",c+1);
	n=strlen(c+1);
	for(int i=1;i<=n;i++){
		if(c[i]=='1')num++;
		else ori+=num;
	}
	ori%=mod;
	for(int i=1;i<=n;i++){
		if(c[i]=='1')pos[++cnt]=i;
	}
	for(int i=1;i<=t;i++){
		q.push_back(i);
	}
	for(int k=1;k<=cnt;k++){
		all++;
		if(q.back()+all>t&&q.size())q.pop_back();
		q.push_front(1-all);
		
		for(int j=1;j<=pos[k]-pos[k-1]-1&&q.size();j++){
			cf[q.front()+all]++;
			cf[min(cnt-k+q.front()+all+1,t+1)]--;
			q.pop_front();
		}
		
		dis[k]=t-q.size();
		ans1[pos[k]-dis[k]]=1;
	}

	for(int i=0;i<=t;i++){
		if(i)sum[i]=(sum[i-1]+cf[i])%mod;
		ori+=sum[i];
		ori%=mod;
		ans^=(qpow(233,i)*ori%mod);
	}
	for(int i=1;i<=n;i++)cout<<ans1[i];
	cout<<endl<<ans;
	return 0;
}
