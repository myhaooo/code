#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Maxn = 2e5 + 5;
const int Inf = 2e9;
int n, m, a[Maxn], s[Maxn], t[Maxn], c[Maxn], r[Maxn];
bool check(int x) {
    for(int i = 1; i <= m; i++) {
        int pos = s[i], tot = 0;
        while(1) {
            int nxt = upper_bound(a + 1, a + n + 1, a[pos] + x / c[i]) - a - 1;
            if(nxt == pos) return 0;
            pos = nxt;
            if(pos >= t[i]) break;
            tot++;
        }
        if(tot > r[i]) return 0;
    }
    return 1;
}

int ans = 0;


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int maxn = 0;
    for(int i = 1; i <= m; i++) {
        cin >> s[i] >> t[i] >> c[i] >> r[i];
        maxn = max(maxn, (a[t[i]] - a[s[i]]) * c[i]);
    }
    int l=0,r=maxn,mid;
    while(l <= r) {
        mid = (l + r) >> 1;
        if(check(mid)) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
    return 0;
}
