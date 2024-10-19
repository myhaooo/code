#include<bits/stdc++.h>
using  ll = long long;
using namespace std;
#define int long long 
const int N = 4e5 + 7, mod = 998244353;
int ans, n, m;
int fac[N], inv[N], ifac[N];
void init(int x) {
    fac[0] = ifac[0] = inv[1] = 1;
    for(int i = 2; i <= x; i++) inv[i] = (ll) inv[mod % i] * (mod - mod / i) % mod;
    for(int i = 1; i <= x; i++) fac[i] = (ll) fac[i - 1] * i % mod, ifac[i] = (ll) ifac[i - 1] * inv[i] % mod;
}
int C(int x, int y) {
    return x < y || y < 0 ? 0 : (ll) fac[x] * ifac[y] % mod * ifac[x - y] % mod;
}
int main() {
    cin >> n >> m, init(max(n, m) * 4);
    for(int i = 1; i <= m - 1; i++) {
        int now = 0;
        for(int j = n - 1; j >=1; j--) {
            (now += (ll) C(j + m - i - 1, m - i - 1) * C(n - j + m - i - 1, m - i) % mod) %= mod;
            (ans += (ll) C(j + i - 1, i) * C(n - j + i - 1, i - 1) % mod * now % mod) %= mod;
        }
    }
    for(int j = 1; j <= n; j++) {
        int now = 0;
        for(int i = 1; i <= m-1; i++) {
            (now += (ll) C(n - j + i - 2, i - 2) * C(n - j + m - i, m - i + 1) % mod) %= mod;
            (ans += (ll) C(j + i - 1, i) * C(j + m - i - 1, m - i - 1) % mod * now % mod) %= mod;
        }
    }

    ans = (ll) ans * 2 % mod;
    cout << ans << "\n";
    return 0;
}