#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 998244353, N = 100005;
int n;
int a[N], sum, ans;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    freopen("fft.in", "r", stdin);
    freopen("fft.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        ans = (ans + sum * a[i] % Mod) % Mod;
        sum = (sum + a[i]) % Mod;
    }
    for (int i = 3,t ; i <= n; i++) {
        t = i * (i - 1) / 2 % Mod;
        ans = ans * t % Mod;
    }
    cout << ans;
    return 0;
}

