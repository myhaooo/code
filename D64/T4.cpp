#include <algorithm>
#include <iostream>
#include <vector>
#define RF(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

using namespace std;
using LL = long long;
using Pii = pair<int, int>;
using Pll = pair<LL, LL>;

int _n, n;

int main() {
    RF("symphony");
    ios::sync_with_stdio(0), cin.tie(0);
    auto cmp = [](int i, int j) {
        if (j <= _n) {
            cout << "CMPSWP R" << i << " R" << j << ' ';
        }
    };
    cin >> _n, n = (1 << __lg(_n - 1) + 1);
    cout << __lg(n) * (__lg(n) + 1) / 2 << '\n';
    for (int i = 1; i < n; i *= 2) {
        for (int j = 1; j <= n; j += i * 2) {
            for (int k = 0; k < i; ++k) {
                cmp(j + k, j + i * 2 - 1 - k);
            }
        }
        cout << '\n';
        for (int j = i / 2; j >= 1; j /= 2) {
            for (int k = 1; k <= n; k += j * 2) {
                for (int p = 0; p < j; ++p) {
                    cmp(k + p, k + j + p);
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
