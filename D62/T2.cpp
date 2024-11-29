#include <bits/stdc++.h>
using namespace std;
const int N = 5;
const long long mod = 998244353;
int n, siz[N + 5];
long long f[N + 5][N + 5];
vector<int> G[N + 5];
void dfs(int u, int fa) {
    for (int i = 1; i <= n; i++) f[u][i] = 1;
    for (int v : G[u]) {
        if (v == fa)
            continue;
        dfs(v, u);
        long long tmp = 0;
        for (int i = 1; i <= n; i++) {
            tmp = (tmp + f[v][i + 1]) % mod;
            f[u][i] = f[u][i] * tmp % mod;
        }
    }
}
int main() {
    freopen("reflection.in", "r", stdin);
    freopen("reflection.out", "w", stdout);
    cin>>n; 
    for (int i = 1, x, y; i < n; i++) {
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(n, 0);
    cout<<f[n][1]<<endl;
    return 0;
}
 
