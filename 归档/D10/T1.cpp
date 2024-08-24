#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int a,b,c,d;
int z;
signed main(){
	cin>>a>>b>>c>>d;
	for(int i=1;i<=999;i++){
		for(int j=1;j+i<=999;j++){
			if(__gcd(i,j)==1){
				int l,r;
				r=min(b/i,d/j);
				l=max((a+i-1)/i,(c+j-1)/j);
				if(l<=r){
					z=(z+(i+j)*(r-l+1)%mod)%mod;
				}
			}
		}
	}
	cout<<z;
}