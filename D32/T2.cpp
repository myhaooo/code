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
˵��Ǯ������������ڣ����������鹦������
��ָߣ�������ǿ����ʵ��Ǯ����ѧ�ʲ�����������Ժ�
���ֲ��;�Ŀ๦��Ǯ�����ѧͬ�������������������Уʱ����һ�ܶ�
���ľ��䣬һ����ŷ��������������֮��������һ�ա�ÿ��ͼ��ݽ��黹��
���ػ��������޲ᣬ�ұ��ҳۡ���Щ�˿��ܲ�֪�����������廪��Ŀ���ǡ���ɨ��
��ͼ��ݡ���������ѧ�ĵ��ǣ���Խ�Ǵ����ˣ�ԽҪ�����±����򡣡�
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
