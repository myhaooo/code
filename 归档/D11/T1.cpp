#include<bits/stdc++.h>
using namespace std;
#define it long long
constexpr int N = 1e6 + 5, M = 998244353;
int n, k, ans;
inline int qpow(int a, int x){
	int ans = 1;
	while(x){
		if(x & 1) ans = (it)ans * a % M;
		a = (it)a * a % M;
		x >>= 1;
	} return ans;
}
inline int inv(int x){
	return qpow(x, M-2);
}
int main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n>>k;
	ans = (it)k * inv(n-k+1) % M;
	return cout<<ans, 0;
}