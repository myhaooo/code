#include<bits/stdc++.h>
int Solve();
using namespace std;
using ll=long long;
const int MOD = 998244353;
const int N = 3e5+35;
int n;
int a[N];
int st1[N],top1=0; // max
int st2[N],top2=0; // min
ll f[N],mxg[N],mng[N];
signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	return Solve();
}
int Solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	f[0]=1;
	for(int i=1;i<=n;i++) {
		while(top1&&a[st1[top1]]<=a[i]) --top1;
		while(top2&&a[st2[top2]]>=a[i]) --top2;
		if(top1) mxg[i]=(mxg[st1[top1]]+(f[i-1]-f[st1[top1]-1]+MOD)%MOD*a[i]%MOD)%MOD;
		else mxg[i]=f[i-1]*a[i]%MOD;
		if(top2) mng[i]=(mng[st2[top2]]+(f[i-1]-f[st2[top2]-1]+MOD)%MOD*a[i]%MOD)%MOD;
		else mng[i]=f[i-1]*a[i]%MOD;
		f[i]=(f[i-1]+mxg[i]-mng[i]+MOD)%MOD;
		st1[++top1]=st2[++top2]=i;
	}
	printf("%lld\n",(f[n]-f[n-1]+MOD)%MOD);
	return 0;
}