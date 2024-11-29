#include <bits/stdc++.h>
using namespace std;
int x, y;
#define double long double

int main() {
//	freopen("island.in", "r", stdin);
//	freopen("island.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> x >> y;
	double ans = 0;
	for (int i = 1; i <= x; ++i) {
		ans += (double)1.0 / (i * 2 - 1);
	}
	for (int i = 1; i <= y; ++i) {
		ans += (double)1.0 / (i + x * 2);
	}
	cout << fixed << setprecision(15) << ans << '\n';
	return 0;
}