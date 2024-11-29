#include <bits/stdc++.h>
using namespace std;
int n, q;
const int MAXN=1e5+5;
vector<int> G[MAXN];
int dis1[MAXN], dis2[MAXN];
int pre[MAXN];
void dfs(int u, int dis[], int fa) {
    pre[u] = fa;
    for (auto v : G[u]) {
        if (v == fa)
            continue;
        dis[v] = dis[u] + 1;
        dfs(v, dis, u);
    }
}
int main() {
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    cin >> n >> q;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dis1[1] = 0;
    dfs(1, dis1, 1);
    int u = 0, len = 0;
    for (int i = 1; i <= n; i++) {
        if (dis1[i] > len) {
            u = i;
            len = dis1[i];
        }
    }
    dis2[u] = 0;
    dfs(u, dis2, u);
    len = 0;
    int v = 0;
    for (int i = 1; i <= n; i++) {
        if (dis2[i] > len) {
            v = i;
            len = dis2[i];
        }
    }
    if (len % 2 == 1) {
        while (q--) {
            int u;
            cin >> u;
            cout << "Alice" << endl;
        }
    }
    if (len % 2 == 0) {
        int ct = v;
        for (int i = 1; i <= len / 2; i++) ct = pre[ct];
        //cout << ct << endl;
        while (q--) {
            int x;
            cin >> x;
            if (n == 1)
                cout << "Bob" << endl;
            if (x != ct)
                cout << "Alice" << endl;
            else
                cout << "Bob" << endl;
        }
    }
    return 0;
}

