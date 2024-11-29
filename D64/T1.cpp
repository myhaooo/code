#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, x, y, answer;
__int128 ans;
ll div(ll nn, ll xx, ll yy) {
    while (yy--) nn /= xx;
    return nn;
}
__int128 solve(int m) {
    __int128 res = y * m;
    ll l = 1, r = n + 1, mid, re = n + 1;
    while (l <= r) {
        mid = (l + r) / 2;
        if (div(n, mid, m) == 0)
            re = mid, r = mid - 1;
        else
            l = mid + 1;
    }
    __int128 mn = (__int128)(re - 1) * m * x;
    if (re != 1) {
        for (int i = 1; i <= m; i++)
            if (div(div(n, re, m - i), re - 1, i) == 0)
                mn = (__int128)(re * m - m - i) * x;
    }
    res += mn;
    return res;
}
int main() {
    freopen("dice.in", "r", stdin);
    freopen("dice.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> x >> y;
    swap(x, y);
    ans = solve(1);
    for (int i = 2; i <= 60; i++) ans = min(ans, solve(i));
    answer = ans;
    cout << answer;
    return 0;
}
