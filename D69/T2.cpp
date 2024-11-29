#include <bits/stdc++.h>
#define ll long long
#define fir first
#define sec second
using namespace std;
typedef pair<int, int> pii;
const int maxn = 5e4 + 5;
int N, K, n;
pii ans[2000005];
ll a[maxn];
int main() {
    freopen("nim.in", "r", stdin);
    freopen("nim.out", "w", stdout);
    cin>>N>>K;
    for (int i = 1; i <= N; i++) cin>>a[i];
    ll s = 0;
    for (int i = 1; i <= N; i++) s ^= a[i];
    for (int i = 1; i <= N; i++) {
        ll t = (s ^ a[i]) - a[i], now = 0;
        t = (~t) + 1;
        for (int j = 0; j <= 30; j++)
            if ((t >> j) & 1) {
                now += 1LL << j;
                if (now > K || now > a[i])
                    continue;
                ans[++n] = { i, now };
            }
    }
    if (!n)
        printf("0");
    else {
        printf("1\n");
        for (int i = 1; i <= n; i++) printf("%d %d\n", ans[i].fir, ans[i].sec);
    }
    return 0;
}