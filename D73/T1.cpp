#include <bits/stdc++.h>
using namespace std;
bool check(const vector<int>& a, int x) {
    int prev = a[0] ^ x;
    for (int i = 1; i < a.size(); ++i) {
        int curr = a[i] ^ x;
        if (prev > curr) return false;
        prev = curr;
    }
    return true;
}

int query(const vector<int>& a) {
    int minX = -1;
    for (int x = 0; x <= (1 << 9); ++x) {
        if (check(a, x)) {
            minX = x;
            break;
        }
    }
    return minX;
}

int main() {
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int m;
    cin >> m;
    vector<pair<int, int>> operations(m);
    for (int i = 0; i < m; ++i) {
        cin >> operations[i].first >> operations[i].second;
    }

    cout << query(a) << endl;

    for (const auto& op : operations) {
        int p = op.first - 1; 
        int v = op.second;
        a[p] = v;
        cout << query(a) << endl;
    }

    return 0;
}

