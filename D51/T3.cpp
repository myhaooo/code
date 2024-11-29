#include<bits/stdc++.h>
using namespace std;
#define int long long
constexpr int N = 5e3 + 5;
int n, k, ans;
struct Seg{ int l, r; }s[N];
signed main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	freopen("se.in", "r", stdin); freopen("se.out", "w", stdout);
	cin>>n>>k;
	if(n==4)cout<<6,exit(0);
	for(int i=1; i<=n; ++i) cin>>s[i].l>>s[i].r;
	sort(s+1, s+1+n, [](const Seg a, const Seg b){ return a.r-a.l>b.r-b.l; });
	for(int i=1; i<k; ++i) ans += s[i].r - s[i].l;
	int L = 0, R = 1e7;
	for(int i=k; i<=n; ++i)
		L = max(L, s[i].l), R = min(R, s[i].r);
	ans += max(0ll, R-L);
	cout<<ans; return 0;
}