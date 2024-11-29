#include <bits/stdc++.h>
#define int long long
#define N 500500
using namespace std;
int n, h[N], a[N], p[N], ans[N];
struct tree {
    int minv[4 * N];
    void build(int i, int l, int r) {
        if (l == r) {
            minv[i] = h[l];
            return;
        }
        int mid = l + r >> 1;
        build(i << 1, l, mid);
        build(i << 1 | 1, mid + 1, r);
        minv[i] = min(minv[i * 2], minv[i * 2 + 1]);
    }
    void change(int i, int x, int k, int l, int r) {
        if (l == r) {
            minv[i] = k;
            return;
        }
        int mid = l + r >> 1;
        if (mid >= x)
            change(i << 1, x, k, l, mid);
        else
            change(i << 1 | 1, x, k, mid + 1, r);
        minv[i] = min(minv[i * 2], minv[i * 2 + 1]);
    }
    int fir(int i, int x, int l, int r) {
        if (minv[i] >= x)
            return -1;
        if (l == r)
            return l;
        int mid = l + r >> 1;
        if (minv[i << 1] >= x)
            return fir(i << 1 | 1, x, mid + 1, r);
        return fir(i << 1, x, l, mid);
    }
    int lst(int i, int x, int l, int r) {
        if (minv[i] >= x)
            return -1;
        if (l == r)
            return l;
        int mid = l + r >> 1;
        if (minv[i << 1 | 1] >= x)
            return lst(i << 1, x, l, mid);
        return lst(i << 1 | 1, x, mid + 1, r);
    }
} t1, t2;
signed main() {
    freopen("uphill.in", "r", stdin);
    freopen("uphill.out", "w", stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    t1.build(1, 1, n);
    int cnt = 0;
    memset(ans, -1, sizeof(ans));
    for (int i = n; i; i--) {
        int tmp = t1.lst(1, a[i], 1, n);
        p[i] = tmp;
        if (tmp != -1) {
            cnt++;
            ans[tmp] = i;
            t1.change(1, tmp, 1ll << 50, 1, n);
        }
    }
    t2.build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int tmp = -1;
        if (p[i] == -1) {
            tmp = t2.fir(1, 1ll << 50, 1, n);
            if (ans[tmp] != -1)
                p[ans[tmp]] = -1;
            p[i] = tmp;
            ans[tmp] = i;
        } else {
            t1.change(1, p[i], h[p[i]], 1, n);
            ans[p[i]] = -1;
            tmp = t1.fir(1, a[i], 1, n);
            p[i] = tmp;
            ans[p[i]] = i;
        }
        t1.change(1, tmp, 1ll << 50, 1, n);
        t2.change(1, tmp, 1ll << 50, 1, n);
    }
    for (int i = 1; i <= n; i++) cout << a[ans[i]] << ' ';
    return 0;
}

