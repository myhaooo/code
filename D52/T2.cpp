#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 200;
ll n, m, a[N], ans, s[N];
ll mx, mw;
int top, l[N];
ll st[N];

int main() {
    freopen("bitop.in", "r", stdin);
    freopen("bitop.out", "w", stdout);
    cin>>n>>m;
    for (int i = 1; i <= n; ++i) cin>>a[i], mx = max(a[i], mx);
    for (int i = 59; i >= 0; --i)
        if (mx & (1 << i))
            mw = 1 << i;
    ans = a[1];
    for (int i = 1; i <= m + 1; ++i) ans &= a[i];
    for (int i = m + 2; i <= n; ++i) ans |= a[i - 1];
    for (int i = n; i; --i) s[i] = s[i + 1] | a[i];
    int len = n;
    ll mn = 1ll << 59;
    for (int i = 59; i >= 0; --i) {
        ll x = 1ll << i, la = 0;
        if (ans & x) {
            for (int j = 1; j <= len; ++j)
                if (a[j] & x)
                    l[j] = la, la = j;
            len = la;
            mn = min(mn, x);
            if (s[len + 1] == ans)
                break;
            else {
                for (int j = 1; j <= n; ++j) a[j] -= s[len + 1] & a[j];
                ans -= s[len + 1];
                for (int j = n; j; --j) s[j] = s[j + 1] | a[j];
            }
        }
    }  // cout<<endl;
    ll wh = len;
    for (int i = l[len], tmp = 0; i; i = l[i]) {
        ++tmp;
        // cout<<i<<endl;
        if (tmp == m) {
            for (int i = len; i != wh; i = l[i]) st[++top] = i - 1, --m;
            cout << --wh << ' ';
            for (int i = top; i; --i) cout << st[i] << ' ';
            return 0;
        }
        if (i - 2 >= m - tmp)
            wh = i;
        else
            break;
    }
    for (int i = len; i != wh; i = l[i]) st[++top] = i - 1, --m;
    --wh;
    while (m--) st[++top] = --wh;
    for (int i = top; i; --i) cout << st[i] << ' ';
    return 0;
}

