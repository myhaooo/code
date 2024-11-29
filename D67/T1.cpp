#include <bits/stdc++.h>
#define int long long
#define MAXN 500005
using namespace std;
int n, m, k;
int a[MAXN], c[MAXN];
bool check(int x) {
    int res = 0;
//    int id = upper_bound(a + 1, a + 1 + n, x) - a;
//    if (id > n / 2 + 1) {
//        return true;
//    }
    int pos = n / 2 + 1;
    for (int i = 1; i <= pos; i++) {
        int t = a[i] / (x + 1) + 1;
        res += c[t];
    }
    return res <= k;
}
int cc[MAXN];
signed main() {
    freopen("opt.in", "r", stdin);
    freopen("opt.out", "w", stdout);
    int i, j;
    cin>>n>>m>>k;
    int mx = 0;
    for (i = 1; i <= n; i++) {
        cin>>a[i] ;
        mx = max(a[i], mx);
    }
    for (i = 1; i <= m; i++) {
        cin>>c[i];
    }
    c[1] = 0;
    for (i = 1; i <= m; i++) {
        cc[i] = c[i];
    }
    for (i = 1; i <= m; i++) {
        for (j = i * 2; j <= m; j += i) {
            c[j] = min(c[j], c[i] + cc[j / i]);
        }
    }
    for (i = n - 1; i >= 1; i--) {
        c[i] = min(c[i], c[i + 1]);
    }
    sort(a + 1, a + 1 + n);
    int l = -1, r = mx;
    while (l < r) {
        int mid = (l + r) / 2;
        if (!check(mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << l;
    return 0;
}

