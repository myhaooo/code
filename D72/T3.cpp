#include <bits/stdc++.h>
#define ll long long
#define N 1100000
using namespace std;
int n, c, d;
ll a[N], b[N];
vector<ll> solve(int l, int r) {
    if (l == r) {
        return { a[l], b[l] };
    }
    int mid = (l + r) >> 1;
    auto vl = solve(l, mid), vr = solve(mid + 1, r);
    vector<ll> ans(r - l + 2, LLONG_MIN);
    auto cal = [&](int i, int j) {
        return vl[i] + vr[j] + (ll)(vl.size() - 1 - i) * j * c + (ll)(vr.size() - 1 - j) * i * d;
    };
    ans[0] = cal(0, 0);
    for (int i = 0, j = 0; i + 1 < vl.size() || j + 1 < vr.size();) {
        if (i + 1 < vl.size() && (j + 1 == vr.size() || cal(i + 1, j) > cal(i, j + 1)))
            i++;
        else
            j++;
        ans[i + j] = cal(i, j);
    }
    return ans;
}
int main() {
    freopen("creek.in", "r", stdin);
    freopen("creek.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> c >> d;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    auto ans = solve(1, n);
    cout << *max_element(ans.begin(), ans.end()) << '\n';
    return 0;
}
