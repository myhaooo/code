#include <bits/stdc++.h>
using ll = long long;

const int maxn = 256;
int n, m;
int c[maxn][maxn][maxn];

bool check(int mid) {
    for (int i = mid - 1; i < 256; ++i)
        for (int j = mid - 1; j < 256; ++j)
            for (int k = mid - 1; k < 256; ++k)
                if (c[i][j][k] - (i >= mid ? c[i - mid][j][k] : 0) - (j >= mid ? c[i][j - mid][k] : 0) -
                        (k >= mid ? c[i][j][k - mid] : 0) +
                        (i >= mid && j >= mid ? c[i - mid][j - mid][k] : 0) +
                        (i >= mid && k >= mid ? c[i - mid][j][k - mid] : 0) +
                        (j >= mid && k >= mid ? c[i][j - mid][k - mid] : 0) -
                        (i >= mid && j >= mid && k >= mid ? c[i - mid][j - mid][k - mid] : 0) >=
                    m)
                    return true;
    return false;
}

int main() {
    std::freopen("rgb.in", "r", stdin);
    std::freopen("rgb.out", "w", stdout);
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    while (n--) {
        int r, g, b;
        cin >> r >> g >> b;
        ++c[r][g][b];
    }
    for (int i = 1; i < 256; ++i)
        for (int j = 0; j < 256; ++j)
            for (int k = 0; k < 256; ++k) c[i][j][k] += c[i - 1][j][k];
    for (int i = 0; i < 256; ++i)
        for (int j = 1; j < 256; ++j)
            for (int k = 0; k < 256; ++k) c[i][j][k] += c[i][j - 1][k];
    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < 256; ++j)
            for (int k = 1; k < 256; ++k) c[i][j][k] += c[i][j][k - 1];

    int l = 0, r = 255, mid, ans = 255;
    while (l <= r) {
        mid = l + r >> 1;
        if (check(mid + 1))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    cout << ans << '\n';

    cout.flush();
    return 0;
}