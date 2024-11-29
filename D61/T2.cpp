#include<bits/stdc++.h>
const int N = 1e6+5;
#define ll long long 
using namespace std;
struct st {
	ll a,b;
}goods[N], tickets[N];
bool cmp(st a, st b) {
	if(a.a != b.a) return a.a > b.a;
	return a.b > b.b;
}
ll n,m;
ll ans;
priority_queue<ll, vector<ll>, greater<ll> > que;
int main() {
	cin>>n>>m;
	for(int i = 1; i <= n; ++ i) {
		cin>>goods[i].a>>goods[i].b;
		ans += goods[i].b;
	}
	sort(goods + 1, goods + n + 1, cmp);
	for(int i = 1; i <= m; ++ i) {
		cin>>tickets[i].a>>tickets[i].b;
	}
	sort(tickets + 1, tickets + m + 1, cmp);
	for(int i = 1, j = 1; i <= m; ++ i) {
		while(j <= n && goods[j].a >= tickets[i].a) {
			que.push(goods[j].a - goods[j].b);
			++j;
		}
		if(!que.empty() && que.top() < tickets[i].b) {
			ans += que.top() - tickets[i].b;
			que.pop();
			que.push(tickets[i].b);
		}
	}
	cout<<ans<<"\n";
	return 0;
}
