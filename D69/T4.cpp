#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 5e3 + 5, P = 1e9 + 7;

int n, ans;
int a[N], pre[N], suf[N];
ll f[N], g[N][N], tmp[N];
unordered_map<int, int> mp;

int main() {
    freopen("nest.in", "r", stdin);
    freopen("nest.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) pre[i] = 0, suf[i] = n + 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = mp[a[i]], suf[pre[i]] = i, mp[a[i]] = i;
    }
    for (int i = 1; i <= n + 1; i++) {
        int sum = 1;
        for (int j = i - 1; j >= 0; j--) {
            g[i][j] = sum;
            tmp[j] = a[j] == a[i] ? 0 : sum;
            sum = (sum - tmp[suf[j]] + tmp[j]) % P;
        }
    }
    f[0] = 1;
    for (int i = 1; i <= n + 1; i++) {
        for (int j = 0; j < i; j++) {
            int G = (g[i][j] - g[pre[i]][j]) % P;
            f[i] = (f[i] + G * f[j] % P) % P;
        }
    }
    cout << (f[n + 1] + P) % P;
    return 0;
}
