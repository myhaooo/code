#include <bits/stdc++.h>

using namespace std;

const int N = 2e4 + 2;
bitset<N> mp[N]; 
vector<int> num[N];
int n, m, a[N];
int main() {
    cin>>n;
    for (int i = 1; i <= n; i++) {
        cin>>a[i];
        num[a[i]].push_back(i);
    }
    int last = 0;
    for (int i = 1; i <= n; i++) {
        if (num[i].empty()) continue;
        for (int j : num[i]) {
            mp[i][j] = 1;
            for (int k = j - 1; k >= 1 && a[j] > a[k]; k--) {
                mp[i][k] = 1;
                mp[i] |= mp[a[k]];
                if (a[k] == last) break;
            }
            for (int k = j + 1; k <= n && a[j] > a[k]; k++) {
                mp[i][k] = 1;
                mp[i] |= mp[a[k]];
                if (a[k] == last) break;
            }
        }
        last = i;
    }
    cin>>m;
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (mp[a[x]][y]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}
