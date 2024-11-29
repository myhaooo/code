#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5; 
int a[MAXN];
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		memset(a,0,sizeof(int)*(n+5));
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		long long b[n]={a[0]},mx=0,mn=0;
		for(int i=1;i<n;i++){
			b[i]=b[i-1]+a[i];
		}
		for(int i=0;i<n;i++){
			mx=max(mx,b[i]),mn=min(mn,b[i]);
		}
		cout<<mx-mn<<endl;
	}
	return 0;
}
