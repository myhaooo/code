#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n, a[N];
int main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    cin>>n;
    for (int j = 1; j <= n; j++) {
        for (int i = 0; i <= n; i += j) {
            int l = i, r = i + (j - 1) / 2 + 1;
            a[l]++, a[r]--;
        }
    }
    for (int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
        cout<<a[i]<<" ";
    }
}
