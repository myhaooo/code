#include <bits/stdc++.h>
#define N 5005
#define D 1000000
using namespace std;
vector<int> a[D*2 + 5], b[D*2 + 5];
int n, m, num[D*4];
int main() {
    freopen("mirror.in", "r", stdin);
    freopen("mirror.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        x += D, y += D;
        a[x].push_back(y);
    }
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        x += D, y += D;
        b[x].push_back(y);
    }
    int ans = 0;
    for (int i = 0; i <= D * 2; i++) {
        for (auto pa : a[i])
            for (auto pb : b[i]) {
                ans = max(ans, ++num[pa + pb]);
            }
    }
    cout << ans << '\n';
    return 0;
}

