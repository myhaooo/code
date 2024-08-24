#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int N = 5e5 + 5;
string s;  int n, ans[N];
signed main(){
	ios::sync_with_stdio(false);
	#ifndef LOCAL
	cin.tie(0),cout.tie(0);
    #endif
    #ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
	cin>>n>>s;
	for(int i=1, j=1, sum=0; i<=n; ++i){
		while(j <= n && s[j-1] == '>') ++j;
		if(j > n) break;
		sum += 2 * (j - i) + 1;
		ans[i] += sum; ++j;
	}
	for(int i=n, j=n, sum=0; i>=1; --i){
		while(j >= 1 && s[j-1] == '<') --j;
		if(j < 1) break;
		sum += 2 * (i - j) + 1;
		ans[i] += sum; --j;
	}
	for(int i=1; i<=n; ++i) cout<<ans[i]<<' ';
	return 0;
}