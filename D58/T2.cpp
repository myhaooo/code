#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
const int P = 998244353;
int qpow(int x, int y) {
    int ans = 1;
    while (y) {
        if (y & 1)
            ans = 1ll * ans * x % P;
        x = 1ll * x * x % P;
        y >>= 1;
    }
    return ans;
}
int n, deg[N], ans;
map<pair<int, int>, bool> mp;
int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    cin >> n;
    ans = 1ll * (n - 1) * qpow(2, P - 2) % P;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin>>x>>y;
        deg[x]++, deg[y]++;
        mp[{ x, y }] = mp[{ y, x }] = 1;
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin>>x>>y;
        int s = n - 1 - deg[x] - deg[y] + mp[{ x, y }];
        ans = (ans + 1ll * s * qpow(16, P - 2) % P) % P;
    }
    cout<<ans<<'\n';
    return 0;
}

