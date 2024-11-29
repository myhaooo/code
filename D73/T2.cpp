#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, M = 40;
int n, m, v, a[N], b[N], c[N], d[N];
ll k, cnt, r;

int p[N], to[N], nxt[M][N];

int main() {
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    cnt = k / m, r = cnt % m;
    v = m % n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> c[i] >> d[i];
    iota(p, p + n, 0);
    for (int i = 1; i <= m; i++) swap(p[(c[i % m] + i) % n], p[(d[i % m] + i) % n]);
    for (int i = 0; i < n; i++) to[p[i]] = i;
    for (int i = 0; i < n; i++) nxt[0][i] = to[i];
    for (int j = 1; j < M; j++)
        for (int i = 0; i < n; i++) {
            int pre = nxt[j - 1][i];
            nxt[j][i] = nxt[j - 1][(pre - v + n) % n];
        }
    if (cnt) {
        for (int i = 0; i < n; i++) {
            int u = i;
            u = to[u];
            for (int j = M - 1; j >= 0; j--)
                if ((cnt - 1) >> j & 1) {
                    u = nxt[j][(u - v + n) % n];
                }
            u = (u + 1ll * v * (cnt - 1)) % n;
            b[u] = a[i];
        }
    }
    ll now = cnt * m + 1;
    while (now <= k) {
        swap(b[(c[now % m] + now) % n], b[(d[now % m] + now) % n]);
        now++;
    }
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    return 0;
}
