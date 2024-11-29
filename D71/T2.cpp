#include <bits/stdc++.h>
#define ll long long
#define int long long 
using namespace std;

const int N = 1e5+5, mod = 1e9+7;
int t, n, m, cnt;
int a[N], maxn[N], f[N];

struct node {
    int numerator, denominator;//·Ö×Ó£¬·ÖÄ¸ 
    bool operator<(node other) const {
        return denominator * other.numerator < numerator * other.denominator;
    }
} b[N];


ll qpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

#define inv(x) (qpow(x,mod-2))

vector<int> vec[N];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) {
            maxn[x] = max(maxn[x], y);
        } else if (opt == 2) {
            vec[x].push_back(y);
        } else {
            if (y != 1) {
                cnt++;
                b[cnt].denominator = 1;
                b[cnt].numerator = y;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] < maxn[i]) {
            vec[i].push_back(maxn[i] - a[i]);
        }
        sort(vec[i].rbegin(), vec[i].rend());
        int ls = a[i];
        for (int x : vec[i]) {
            cnt++;
            b[cnt].denominator = a[i];
            a[i] += x;
            b[cnt].numerator = a[i];
        }
        a[i] = ls;
    }
    sort(b + 1, b + 1 + cnt);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[0] *= a[i];
        f[0] %= mod;
    }
    cout << f[0] << " ";
    for (int i = 1; i <= cnt; i++) {
        f[i] = f[i - 1];
        f[i] *= b[i].numerator;
        f[i] %= mod;
        f[i] *= inv(b[i].denominator);
        f[i] %= mod;
        cout << f[i] << " ";
    }
    for (int i = cnt + 1; i <= m; i++) {
        f[i] = f[cnt];
        cout << f[i] << " ";
    }
    return 0;
}

