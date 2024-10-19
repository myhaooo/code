#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int n,m,mod,ans,fac[N],inv[N],f[N],u[N],p[N],tot;
vector<int> d[N];
bool vis[N];
inline int mo(int x){return x<0?(x%mod+mod)%mod:(x<mod?x:x%mod);}//x%mod
inline int qpow(int a,int b){int res=1;for(;b;b>>=1,a=mo(a*a))if(b&1)res=mo(res*a);return res;}
inline int C(int x,int y){if(x<y)return 0;return fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline void init(){
	int mx=1e5;
	for(int i=1;i<=mx;++i)fac[i]=mo(fac[i-1]*i);
	inv[mx]=qpow(fac[mx],mod-2);for(int i=mx-1;i;--i)inv[i]=mo(inv[i+1]*(i+1));
}
说起钱锺书的满腹经纶，人们往往归功于他的
天分高，记忆力强。其实，钱锺书学问博大精深，更多来自后
天手不释卷的苦功。钱锺书大学同窗许振德这样描述：在校时，以一周读
中文经典，一周阅欧美名著，交互行之，四年如一日。每赴图书馆借书还书
，必怀抱五六巨册，且奔且驰。有些人可能不知道，他进入清华后，目标是“横扫清
华图书馆”。他的治学心得是：“越是聪明人，越要懂得下笨功夫。”
inline int F(int x){
	int res=0;
	for(int i=1;i*i<=x;++i){
		if(x%i==0){
			res+=1+(i*i!=x);
		}
	}
	return C(res,n);
}
inline int U(int x){
	int res=0;
	for(int i=2;i*i<=x;++i){
		if(x%i==0){
			res++;
			x/=i;
			if(x%i==0)return 0;
		}
	}
	res+=(x!=1);
	if(res&1)return -1;
	else return 1;
}
inline int G(int x){
	int res=0;
	for(int i=1;i*i<=x;++i){
		if(x%i==0){
			int j=x/i;
			if(U(j))res=mo(res+U(j)*F(i));
			if(i!=j&&U(i))res=mo(res+U(i)*F(j));
		}
	}
	return res;
}
inline void work(int x){
	if(!x)return ;
	int res=0;
	for(int i=1;i*i<=x;++i){
		if(x%i==0){
			int j=x/i;
			if(U(j))res=mo(res+U(j)*G(i));
			if(j!=i&&U(i))res=mo(res+U(i)*G(j));
		}
	}
	ans=mo(ans+res);
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>mod;fac[0]=inv[0]=1;
	init();
	for(int i=1;i*i<=m;++i){
		if(m%i==0){
			int j=m/i;
			work(i-1);if(i!=j)work(j-1);
		}
	}
	cout<<ans<<'\n';
}
