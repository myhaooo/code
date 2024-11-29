#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,  c[4], ans[5],m, rep[50][50];
void dfs(ll x, ll y, ll cc) {
    if (x == n && y == c[x] + 1) {
        ans[cc]++;
        return;
    }
    if (y == c[x] + 1) {
        y = 1;
        x++;
    }
    if (cc > m) {
        return;
    }
    if (y == 1) {
        rep[x][y] = c[x];
        dfs(x, y + 1, cc + c[x]);
    } else {
        if (x == 1) {
            for (int i = 1; i <= rep[x][y - 1]; i++) {
                if (cc + i <= m) {
                    rep[x][y] = i;
                    dfs(x, y + 1, cc + i);
                }
            }
        } else {
            ll op = min(rep[x - 1][y], rep[x][y - 1]);
            for (int i = 1; i <= op; i++) {
                if (cc + i <= m) {
                    rep[x][y] = i;
                    dfs(x, y + 1, cc + i);
                }
            }
        }
    }
}
int main() {
    freopen("mountain.in", "r", stdin);
    freopen("mountain.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    dfs(1, 1, 0);
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << " ";
    }
}


 
