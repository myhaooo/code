#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1.2e6 + 5, inf = 0x3f3f3f3f;
int n, m, a[N], cnt;
struct Node {
    int cnt, sum, ans;
} t[N << 1], tmp[N];
bool operator<(Node x, Node y) { return x.cnt * y.sum > x.sum * y.cnt; }
int now_cnt, ans;
signed main() {
//    freopen("dog.in", "r", stdin);
//    freopen("dog.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%lld", &x);
        for (int j = 1; j <= x; j++) scanf("%lld", a + j);
        int cur = 0;
        for (int j = 1; j <= x; j++) {
            tmp[++cur] = { 1, a[j], a[j] };
            while (cur >= 2 && tmp[cur] < tmp[cur - 1]) {
            	cout<<cur<<endl;
                tmp[cur - 1].ans += tmp[cur].ans + tmp[cur].cnt * tmp[cur - 1].sum;
                tmp[cur - 1].cnt += tmp[cur].cnt;
                tmp[cur - 1].sum += tmp[cur].sum;
                cur--;
            }
        }
        for (int j = 1; j <= cur; j++) t[++cnt] = tmp[j];
    }
    sort(t + 1, t + 1 + cnt);
    for (int i = cnt; i >= 1; i--) {
        ans += t[i].sum * now_cnt;
        ans += t[i].ans;
        now_cnt += t[i].cnt;
    }
    ans = now_cnt * m - ans;
    printf("%lld\n", ans);
    return 0;
}

