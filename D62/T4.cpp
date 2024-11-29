#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
const long long mod = 1e9 + 7;
int n, a[N + 5];
long long ans = 0, jc[N + 5], ny[N + 5], s[N + 5];
vector<int> T[N + 5], G[N + 5];
long long mi(long long t, long long v) {
    if (!v)
        return 1;
    long long re = mi(t, v / 2);
    re = re * re % mod;
    if (v & 1)
        re = re * t % mod;
    return re;
}
long long C(int x, int y) { return jc[x] * ny[y] % mod * ny[x - y] % mod; }
void init() {
    jc[0] = 1;
    for (int i = 1; i <= N; i++) jc[i] = jc[i - 1] * i % mod;
    ny[N] = mi(jc[N], mod - 2);
    for (int i = N - 1; i >= 0; i--) ny[i] = ny[i + 1] * (i + 1) % mod;
    s[0] = C(n - 1, 0);
    for (int i = 1; i < n; i++) s[i] = (s[i - 1] + C(n - 1, i)) % mod;
    for (int i = 2; i <= N; i++) {
        if (T[i].size())
            continue;
        for (int j = i; j <= N; j += i) {
            T[j].push_back(i);
        }
    }
}
void ptd(int x) {
    while (x > 1) {
        int p = T[x][0], ct = 0;
        while (x % p == 0) {
            x /= p;
            ++ct;
        }
        G[p].push_back(ct);
    }
}
int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        ptd(a[i]);
    }
    for (int i = 2; i <= N; i++) {
        if (T[i][0] != i || !G[i].size())
            continue;
        sort(G[i].begin(), G[i].end());
        int bs = n - (int)G[i].size() + 1;
        for (int j = 0; j < G[i].size(); j++) {
            int id = j + bs;
            long long tmp = 0;
            if (id - 2 >= 0)
                tmp = (tmp + s[id - 2]) % mod;
            if (n - id - 1 >= 0)
                tmp = (tmp - s[n - id - 1] + mod) % mod;
            ans = (ans + G[i][j] * tmp) % mod;
        }
    }
    printf("%lld", ans);
    return 0;
}

