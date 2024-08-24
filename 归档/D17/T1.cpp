#include<bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 5;
int n, p[N], q[N], a[N], b[N], rt;
vector<int> st;
struct SegmentTree{
	int cnt, ls[N<<1], rs[N<<1], mx[N<<1];
	inline void modify(int &id, int l, int r, int x, int k){
		if(!id) id = ++cnt; int mid = (l + r) >> 1;
		if(l == r) return (void)(mx[id] = k);
		if(x <= mid) modify(ls[id], l, mid, x, k);
		else modify(rs[id], mid+1, r, x, k);
		mx[id] = max(mx[ls[id]], mx[rs[id]]);
	}
	inline int query(int &id, int l, int r, int x, int y){
		if(x > y) return 0;
		if(!id) return 0; int mid = (l + r) >> 1, ans = 0;
		if(x <= l && r <= y) return mx[id];
		if(x <= mid) ans = max(ans, query(ls[id], l, mid, x, y));
		if(y >  mid) ans = max(ans, query(rs[id], mid+1, r, x, y));
		return ans;
	}
} ST;
int main(){
//	freopen("T1.in", "r", stdin);
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin>>n;
	for(int i=1; i<=n; ++i) cin>>p[i], a[p[i]] = i;
	for(int i=1; i<=n; ++i) cin>>q[i], b[q[i]] = i;
	for(int i=n; i>=1; --i) {
		for(int j=p[i]; j<=n; j += p[i]) st.push_back(b[j]);
		sort(st.begin(), st.end());
		for(auto it : st){
			int add = ST.query(rt, 1, n, it+1, n) + 1;
			ST.modify(rt, 1, n, it, add);
		}
		st.clear();
	} return cout<<ST.mx[rt], 0;
}