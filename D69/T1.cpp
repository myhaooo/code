#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e6 + 10;
const ll modd = 998244353;
int n, k, nxt[maxn];
ll fac[maxn], siz[maxn], dep[maxn], ans;
string s;
vector<int> G[maxn];

ll qpow(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1)
            res = res * x % modd;
        x = x * x % modd;
        y >>= 1;
    }
    return res;
}

ll C(int x, int y) { return fac[x] * qpow(fac[y], modd - 2) % modd * qpow(fac[x - y], modd - 2) % modd; }

void dfs(int now, int fa) {
    siz[now] = 1;
    for (int i = 0; i < G[now].size(); i++) {
        int v = G[now][i];
        if (v != fa) {
            dep[v] = dep[now] + 1;
            dfs(v, now);
            siz[now] += siz[v];
        }
    }
    if (siz[now] >= k)
        ans = (ans + ((dep[now] << 1ll) - 1ll) * C(siz[now], k) % modd) % modd;
}

int main() {
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> k >> s;
    n = s.size();
    s = ' ' + s;
    fac[0] = 1;
    for (ll i = 1; i <= n + 5; i++) fac[i] = fac[i - 1] * i % modd;
    int j = 0;
    G[1].push_back(0);
    G[0].push_back(1);
    for (int i = 2; i <= n; i++) {
        while (j && s[j + 1] != s[i]) j = nxt[j];
        if (s[j + 1] == s[i])
            j++;
        nxt[i] = j;
        G[i].push_back(j);
        G[j].push_back(i);
    }
    dep[0] = 1;
    dfs(0, 0);
    cout << ans << '\n';
    return 0;
}
