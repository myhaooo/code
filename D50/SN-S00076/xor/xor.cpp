#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
#define int unsigned int
int n,a[MAXN];
void solve1(){
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=j+1;k<=n;k++){
				if((a[i]^a[j])<(a[j]^a[k])){
					ans++;
				}
			}
		}
	}
	cout<<ans,exit(0);
	
}
signed main(){
	#ifndef LOCAL
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);
    #endif
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	solve1();
	
} 
