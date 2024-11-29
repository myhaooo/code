#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e3 + 5;
const ll mod = 998244353;

ll qpow(ll a, ll p, ll mod) {
    ll ans = 1;
    while (p) {
        if (p & 1) {
            ans = ans * a % mod;
        }
        a = a * a % mod;
        p >>= 1;
    }
    return ans;
}

ll n, m;
ll a[maxn];
ll f[maxn][maxn], ans[maxn], p;

int main() {
    freopen("bottle.in", "r", stdin);
    freopen("bottle.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        m = max(a[i], m);
    }
    p = qpow(n - 1, mod - 2, mod);
    f[1][a[1]] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            ans[i] = (ans[i] + f[i][j] * j % mod) % mod;
            for (int k = i + 1; k <= n; k++) {
                ll w = min(a[k], (ll)j);
                f[k][w] = (f[k][w] + f[i][j] * p % mod) % mod;
                ans[i] = (ans[i] - w * f[i][j] % mod * p % mod) % mod;
            }
            if (!j)
                continue;
            for (int k = 1; k < i; k++) {
                ll w = min(a[k], (ll)j);
                ans[i] = (ans[i] - w * f[i][j] % mod * p % mod) % mod;
                ans[k] = (ans[k] + w * f[i][j] % mod * p % mod) % mod;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (ans[i] + mod) % mod << endl;
    }
}
