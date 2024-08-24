#include <bits/stdc++.h>
using namespace std;
const int maxn = 1048576 + 10;
int a[50], flag[60];
int x[40], y[40];
int main() {
    freopen("back.in", "r", stdin);
    freopen("back.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
	    scanf("%d %d", &x[i], &y[i]);
	}
	int ans = INT_MAX, anscnt = 0;
	for (int s = (1 << n) - 1; s >= 0; --s) {
	    memset(a, 0, sizeof a);
	    memset(flag, 0, sizeof flag);

	    int cnt = 0;
	    for (int i = 1; i <= n; ++i) {
		if (s & (1 << (i - 1))) {
		    a[i] = y[i];
		    cnt++;
		}
		else a[i] = x[i];
	    }
	    for (int i = 1; i <= n; ++i) {
		if (flag[a[i]]) break;
		flag[a[i]] = 1;
		if (i == n) {
		    if (ans > cnt) ans = cnt, anscnt = 1;
		    else if (ans == cnt) anscnt++;
		}
	    }
	}
	if (ans == INT_MAX) {
	    printf("-1 -1\n");
	    continue;
	}
	printf("%d %d\n", ans, anscnt);
    }
    return 0;
}