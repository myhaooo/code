#include <bits/stdc++.h>
#define int long long
using namespace std;
int T, n, k, tot, ch[1001001][30], del[1001001], dp[5050], dis[5050], len[5050], minv[5050];
string s[5050];
void add(int i) {
    int p = 1;
    for (int j = 0; j < len[i]; j++) {
        int son = s[i][j] - 97;
        if (!ch[p][son]) {
            tot++;
            ch[p][son] = tot;
            del[tot] = 1ll << 50;
            for (int k = 0; k < 26; k++) ch[tot][k] = 0;
        }
        p = ch[p][son];
        del[p] = min(del[p], (len[i] - j - 1) / k + 1 + dis[(len[i] - j - 1) % k]);
    }
}
signed main() {
    freopen("keyboard.in", "r", stdin);
    freopen("keyboard.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        tot = 1;
        memset(dp, 63, sizeof(dp));
        memset(minv, 63, sizeof(minv));
        memset(dis, 63, sizeof(dis));
        for (int i = 0; i < 26; i++) ch[1][i] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
            len[i] = s[i].size();
            minv[len[i] % k] = min(minv[len[i] % k], len[i]);
        }
        cin >> s[n + 1];
        len[n + 1] = s[n + 1].size();
        dis[0] = 0;
        for (int i = 1; i <= n; i++) {
            if (len[i] > minv[len[i] % k])
                continue;
            minv[len[i] % k] = 0;
            int num = __gcd(len[i], k);
            for (int j = 0; j < num; j++) {
                int u = j;
                while (1) {
                    int v = (u + len[i]) % k, w = len[i] / k + 1;
                    if (u + len[i] % k >= k)
                        w++;
                    dis[v] = min(dis[v], dis[u] + w);
                    u = v;
                    if (u == j)
                        break;
                }
            }
        }
        reverse(dis, dis + k + 1);
        for (int i = 0; i <= k; i++) dis[i]++;
        dis[0] = 0;
        for (int i = 1; i <= n; i++) add(i);
        dp[len[n + 1]] = 0;
        for (int i = len[n + 1] - 1; i >= 0; i--) {
            int pos = 1;
            for (int j = i; j < len[n + 1]; j++) {
                int son = s[n + 1][j] - 97;
                pos = ch[pos][son];
                if (!pos)
                    break;
                dp[i] = min(dp[i], dp[j + 1] + del[pos]);
            }
        }
        if (dp[0] < 1ll << 50)
            cout << dp[0] << '\n';
        else
            cout << "-1\n";
    }
    return 0;
}
