#include <bits/stdc++.h>
using namespace std;
const int N = 300005, mod = 998244353;
int t, n, m, ans;
int a[N];
int p, x, y;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    cin >> n;
    ans = 1;
    for (int i = 1; i <= n; i++) {
        cin >> p >> x >> y;
        ans *= (y + 1);
        ans %= mod;
    }
    cout << ans;
    return 0;
}
