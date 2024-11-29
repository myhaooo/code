#include <bits/stdc++.h>
using namespace std;
int n, m;
string str;
unsigned long long s[10005][2];
signed main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    while (m--) {
        cin >> str;
        for (int i = 1; i <= n; i++) {
            s[i][0] <<= 1;
            s[i][1] <<= 1;
            if (str[i - 1] == '2' || str[i - 1] == '3') {
                s[i][0] |= 1;
            }
            if (str[i - 1] == '1' || str[i - 1] == '3') {
                s[i][1] |= 1;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (__builtin_popcountll(s[i][0] & s[j][1]) & 1) {
                ans++;
            }
        }
    }
    cout << ans;
    return 0;
}

