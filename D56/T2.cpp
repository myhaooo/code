#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int maxn = 1005;
int n, a[maxn], b[maxn];
vector<pair<int, int>> ops;
void solve() {
    ops.clear();
    cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) {
        int pos = -1;
        for (int j = i; j <= n; ++j) {
            if (a[j] < b[i]) {
                pos = -1;
                break;
            } else if (a[j] == b[i]) {
                pos = j;
                break;
            }
        }
        if (pos == -1) {
            cout << "-1\n";
            return;
        }
        if (i != pos) {
            for (int j = pos; j > i; --j) {
                ops.emplace_back(j - 1, j);
                swap(a[j - 1], a[j]);
            }
        }
    }
    cout << 0 << '\n' << ops.size() << '\n';
    for (auto [l,r] : ops) cout << l << ' ' << r << '\n';
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(false);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
