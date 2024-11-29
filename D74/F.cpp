#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=4010;
template<class T>inline bool ckmin(T &x,const T &y)__return x>y?x=y,1:0;___
template<class T>inline bool ckmax(T &x,const T &y)__return x<y?x=y,1:0;___
int a[maxn],m,n;
vector<ll>solve(int l,int r)__
	vector<ll>ret(r-l+2,LLONG_MIN);
	ret[0]=0;
	if(l>r)return ret;
	int pos=min_element(a+l,a+r+1)-a;
	vector<ll>ansL=solve(l,pos-1),ansR=solve(pos+1,r);
	for(int i=0;i<ansL.size();++i)
		for(int j=0;j<ansR.size();++j)__
			ckmax(ret[i+j],ansL[i]+ansR[j]-2ll*i*j*a[pos]);
			ckmax(ret[i+j+1],ansL[i]+ansR[j]-(2ll*(i+1)*(j+1)-1)*a[pos]+1ll*m*a[pos]);
		___
	return ret;
___
signed main()__
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)scanf("%d",a+i);
	printf("%lld",solve(1,n)[m]);
	return 0;
___
