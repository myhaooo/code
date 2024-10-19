#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
int n, m, ans, T;//a是保存排序后的数组，b是merge后的数组，rec是保存原序列 
ll t, rec[N], a[N], b[N];
void merge(int l, int mid, int r) {
	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++) {
		if (j > r || i <= mid && a[i] <= a[j])
			b[k] = a[i++];
		else
			b[k] = a[j++];
	}
}
bool check(int l, int mid, int r) {
	//[l, mid - 1]是前一段 
	for (int k = mid; k <= r; k++) a[k] = rec[k];
	sort(a + mid, a + r + 1);
	merge(l, mid - 1, r);
	ll sum = 0;
	for (int k = 1; k <= ((r - l + 1) >> 1) && k <= m; k++) 
		sum += pow(b[r - k + 1] - b[l + k - 1],2);
	if (sum <= t) {
		for (int k = l; k <= r; k++) a[k] = b[k];
		return 1;
	}
	else
		return 0;
}
void solve() {
	int p = 1, l = 1, r = 1;
	a[l] = rec[l];
	while (r <= n) {
		if (!p) {
			ans++;
			l = ++r;
			a[l] = rec[l];
			p = 1;
		}
		else if (r + p <= n && check(l, r + 1, r + p)) {
			r = r + p;
			p <<= 1;
		}
		else
			p >>= 1;
	}
}
int main() {
	cin>>T;
	while (T--) {
		cin>>n>>m>>t;
		for (int i = 1; i <= n; i++) cin>>rec[i];
		ans = 0;
		solve();
		cout<<ans<<'\n';
	}
	return 0;
} 