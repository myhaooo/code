#include <bits/stdc++.h>
#define int long long
using namespace std;
int T;
signed main(){
	#ifdef LOCAL
	freopen("in.in","r",stdin);
	//freopen("out.out","w",stdout);
	#endif
	cin>>T;
	while(T--){
		int a1[2]={0,0}, n=0;
		long long ans=0;
		string s="";
		cin >> s;
	    n = s.length();
	    for(int i=0;i<n;i++){
	        a1[s[i] - '0']++;
	        if(s[i] == '0') ans += a1[1];
	    }
	    cout << (ans % 3 ? "A" : "B")<<"\n";
	}
}
