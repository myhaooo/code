#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5 + 10;
int t, n, k, a[maxn];
bitset<maxn> f[maxn], all, tmp;
inline int C(int n, int m) {
    if ((n & m) == m)
        return 1;
    return 0;
}
signed main() {
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    scanf("%lld", &t);
    while (t--) {
        scanf("%lld%lld", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        for (int i = 1; i <= k; i++) f[i].reset();
        all.reset();
        for (int i = 1; i <= n; i++) {
            int c = a[i];
            tmp = all ^ f[c];
            f[c] = tmp << 1;
            f[c][1] = 1;
            all = tmp ^ f[c];
        }
        int res = 0;
        for (int i = 1; i <= n; i++) res = (res + C(n - 1, i - 1) * all[i]) % 2;
        printf("%lld", res);
    }
    return 0;
}

