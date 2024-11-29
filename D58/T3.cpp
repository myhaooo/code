#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1e6 + 5;
int n, q, a[N];
unordered_map<int, int> mp;
int main(){
	freopen("fun.in", "r", stdin); freopen("fun.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin>>n>>q; 
	for(int i=1; i<=n; ++i) cin>>a[i], mp[a[i]] = i;
	int A, B; while(q--){
		cin>>A>>B; bool ok = 1;
		if(n <= B){
			for(int i=1; i<n; ++i) 
				if(((a[i]^A)<=B && (a[i+1]^A)>=B) || ((a[i]^A)>=B && (a[i+1]^A)<=B)){
					cout<<i<<'\n'; ok = 0; break; }
		} 
		else {
			for(int i=B; i>=0; --i){
				int id = mp[i^A];
				if(!id) continue;
				if(id < n && (a[id+1] ^ A) >= B){
					cout<<id<<'\n'; ok = 0; break;
				}
				if(id > 1 && (a[id-1] ^ A) >= B){
					cout<<(id-1)<<'\n'; ok = 0; break;
				}
			}
		}
		if(ok) cout<<"-1\n";
	} return 0;
}

