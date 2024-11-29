#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxm = 10005, maxn = 55;
int b[maxm], dp[maxm];
int n, m;
vector<int> ans;
signed main() {
	#ifndef LOCAL
    freopen("subset.in", "r", stdin);
    freopen("subset.out", "w", stdout);
    #endif
    cin >> n >> m;
    for (int i = 0; i <= m; i++) {
        cin >> b[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= m; i++) {
        int cishu = b[i] - dp[i];
        for (int j = 1; j <= cishu; j++) {
            ans.push_back(i);
            for (int k = m - i; k >= 0; k--) {
                dp[i + k] += dp[k];
            }
        }
    }
    for(auto it:ans){
    	cout<<it<<" "; 
	}
}


