#include <iostream>
#include <vector>
#include <algorithm>
const int MOD = 998244353;
using namespace std;
int main() {
	freopen("sa.in","r",stdin);
    freopen("sa.out","w",stdout);
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    for (int i = 0; i < m; ++i) {
        int op, u, v;
        cin >> op >> u >> v;
        --u, --v;  

        if (op == 0) {
            vector<int> temp(a.begin() + u, a.begin() + v + 1);
            a.erase(a.begin() + u, a.begin() + v + 1);
            a.insert(a.begin(), temp.begin(), temp.end());
        } else if (op == 1) {
            reverse(a.begin() + u, a.begin() + v + 1);
        }
    }

    vector<int> ranks(n);
    for (int i = 0; i < n; ++i) {
        ranks[a[i] - 1] = i;
    }

    long long result = 1;
    for (int i = 1; i < n; ++i) {
        if (ranks[i] < ranks[i - 1]) {
            result = (result * 2) % MOD; 
        }
    }

    cout << result << endl;

    return 0;
}

