#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6+5, inf = INT_MAX;
int n, m;
ll s[N], p[N];
int main() {
   freopen("st.in", "r", stdin);
   freopen("st.out", "w", stdout);
    srand(time(0));
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
		p[m] = s[0] = 0ll;
        for (int i = 1; i < m; i++) p[m] -= p[i] = rand();
        for (int i = 1, x; i <= n; i++) scanf("%d", &x), s[i] = s[i - 1] + p[x];
        sort(s, s + 1 + n);
        ll ans = 0;
        for (int i = 1, c = 1; i <= n; i++) s[i] ^ s[i - 1] ? c = 0 : 0, ans += c++;
        printf("%lld\n", ans);
    }
    return 0;
}


