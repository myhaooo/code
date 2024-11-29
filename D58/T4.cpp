#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int N = 50000, INF = 1e9;
const ULL base = 20070923;
int K, n, m, f[70][50005], ans[35];
char a[50005], b[50005];
ULL ha[50005], hb[50005], pw[50005];
inline ULL vala(int l, int r) { return (ha[r] - ha[l - 1] * pw[r - l + 1]); }
inline ULL valb(int l, int r) { return (hb[r] - hb[l - 1] * pw[r - l + 1]); }
inline int LCP(int st1, int st2) {
    if (st1 < 0 || st2 < 0 || st1 > n || st2 > m || a[st1] != b[st2])
        return 0;
    int l = 0, r = min(m - st2, n - st1);
    while (l <= r) {
        int mid = l + r >> 1;
        if (vala(st1, st1 + mid) == valb(st2, st2 + mid))
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l;
}
void max(int &a, int b) { a = (a > b ? a : b); }
int main() {
    freopen("edit.in", "r", stdin);
    freopen("edit.out", "w", stdout);
    scanf("%d", &K);
    scanf("%s", a + 1), n = strlen(a + 1);
    scanf("%s", b + 1), m = strlen(b + 1);
    pw[0] = 1;
    for (int i = 1; i <= N; i++) pw[i] = pw[i - 1] * base;
    for (int i = 1; i <= n; i++) ha[i] = ha[i - 1] * base + a[i];
    for (int i = 1; i <= m; i++) hb[i] = hb[i - 1] * base + b[i];
    
    for (int st = 1; st <= m; st++) {
        for (int i = 0; i <= K; i++)
            for (int j = -K; j <= K; j++) f[i][j + K] = -INF;
        f[0][K] = 0;	
        for (int i = 0; i <= K; i++)
            for (int j = -K; j <= K; j++)
                if (f[i][j + K] != -INF) {
                    f[i][j + K] = f[i][j + K] + LCP(f[i][j + K] + 1, f[i][j + K] + j + st);
                    if (i != K) {
                        if (j != -K)
                            max(f[i + 1][j + K - 1], f[i][j + K] + 1);
                        if (f[i][j + K] != n)
                            max(f[i + 1][j + K], f[i][j + K] + 1);
                        if (j != K)
                            max(f[i + 1][j + K + 1], f[i][j + K]);
                    }
                }
        for (int j = -K; j <= K; j++)
            for (int i = 0; i <= K; i++)
                if (f[i][j + K] >= n) {
                    ans[i]++;
                    break;
                }
    }
    for (int i = 0; i <= K; i++) printf("%d\n", ans[i]);
    return 0;
}

