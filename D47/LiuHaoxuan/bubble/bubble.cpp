#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int n, k, a[MAXN];
vector<int> v[MAXN];
int main() {
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++) 
		cin >> a[i], v[i % k].push_back(a[i]);
    for (int i = 0; i < k; i++) 
		sort(v[i].begin(), v[i].end());
    for (int i = 0; i < n; i++) 
		cout << v[i % k][i / k] << ' ';
    cout << '\n';
    cout.flush();
    return 0;
}

