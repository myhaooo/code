#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e3+5,P=998244353;
int n,k;
int l[N],r[N];
ll qpow(ll a,int b){
	ll res=1;
	while(b){
		if(b&1)res=res*a%P;
		a=a*a%P,b>>=1;
	}return res;
}

int main(){
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>l[i]>>r[i];
	ll sum=0;
	for(int i=1;i<=n;i++)sum=(sum+l[i]+r[i])%P;
	sum=(sum-1)*qpow(2,P-2)%P;
	cout<<qpow((sum+P)%P,k);
	return 0;
}
