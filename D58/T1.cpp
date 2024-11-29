#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e4 + 5;
int n, p[N], val[N], ans;
signed main(){
	freopen("book.in", "r", stdin); freopen("book.out", "w", stdout);
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n; for(int i=1; i<=n; ++i) cin>>p[i];
	for(int i=1; i<=n; ++i){
		int mid = 0;
		for(int j=i; j<=n; j+=2){
			++val[p[j]];
			if(j == i){
				mid = p[j];
				ans += i * j * mid;
			} else {
				++val[p[j-1]];
				if(p[j-1] < mid && p[j] < mid){
					--mid;
					while(!val[mid]) --mid;
				} else if(p[j-1] > mid && p[j] > mid){
					++mid; 
					while(!val[mid]) ++mid;
				}
				ans += i * j * mid;
			}
		}
		for(int j=i; j<=n; ++j) val[p[j]] = 0;
	} cout<<ans; return 0;
}

