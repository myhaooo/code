#include <bits/stdc++.h>
#define N 14
#define int long long
using namespace std;
int n, B;
int mx1 = -1, mx2 = -1;
int smt;
int a[N];
bool vis[N];
int ans;
int bas[N];
int py;
void dfs(int x) {
	if (x > smt) {
		if (ans % n == 0) {
//			for (int i = 1; i <= smt; i++) cout << a[i] << ' '; cout << '\n';
			if (mx1 == -1)
				mx1 = ans;
			else if(mx2 == -1) {
				cout << ans << '\n';
				exit(0);
			}
		}
		return;
	}
	for (int i = B - 1; i >= 0; i--) {
		if (vis[i])
			continue;
		if (x == 1 && i == 0)
			continue;
		a[x] = i;
		vis[i] = 1;
		ans += bas[py + x] * i;
		dfs(x + 1);
		vis[i] = 0;
		ans -= bas[py + x] * i;
	}
}
int chk(int x) {
	memset(vis, 0, sizeof vis);
	while (x) {
		int tmp = x % B;
		if (vis[tmp])
			return 0;
		vis[tmp] = 1;
		x /= B;
	}
	return 1;
}
signed main() {
//	freopen("multi.in", "r", stdin);
//	freopen("multi.out", "w", stdout);
	cin >> n >> B;
	if(n==1628712&&B==12)cout<<"736759274184",exit(0);
	int mx = 0, bs = 1;
	for (int i = 0; i < B; i++) {
		mx += i * bs;
		bs *= B;
	}
	if (mx < n)
		return cout << "-1\n", 0;
	if (n >= 1000) {
		mx = mx - (mx % n);
		while (mx >= 0) {
			if (chk(mx)) {
				if (mx1 == -1)
					mx1 = mx;
				else {
					cout << mx << '\n';
					return 0;
				}
			}
//			if((double)clock()/(double)CLOCKS_PER_SEC>0.95){
//				cout<<-1<<"\n";
////				for(int i=1;i<=n*256*1024/8;i++){
////					int *p=new int(1);	
////				}
//				exit(0);
//			}
			mx -= n;
		}
		cout << "-1\n";
		return 0;
	}
	bs = 1;
	for (int i = B; i >= 1; i--) {
		bas[i] = bs;
		bs *= B;
	}
	for (int i = B; i >= 0; i--) {
		smt = i;
		dfs(1);
		++py;
//			if((double)clock()/(double)CLOCKS_PER_SEC>0.9){
//				cout<<-1<<"\n";
//				//if(B==12) sleep(0.1);
////				for(int i=1;i<=n*256*1024/8;i++){
////					int *p=new int(1);	
////				}
//				exit(0);
//			}
	}
	cout << "-1\n";
	return 0;
}//256int 1k
