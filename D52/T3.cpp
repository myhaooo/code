#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MOD = 998244353;
int n, q, type;
int lastans = 0;
vector<vector<int>> tree;
vector<int> depth, parent;
void dfs(int node, int par, int dep) {
    parent[node] = par;
    depth[node] = dep;
    for (int neighbor : tree[node]) {
        if (neighbor != par) {
            dfs(neighbor, node, dep + 1);
        }
    }
}

int get_distance(int u, int v) {
    int dist = 0;
    while (u != v) {
        if (depth[u] > depth[v]) swap(u, v);
        v = parent[v];
        dist++;
    }
    return dist;
}

int main() {
    cin >> n >> q >> type;
    tree.resize(n + 1);
    depth.resize(n + 1);
    parent.resize(n + 1);
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(1, 0, 0);

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        if (type == 1) {
            u ^= lastans;
            v ^= lastans;
        }

       
        int ans = get_distance(u, v);
        lastans = ans % MOD;
        cout << lastans << endl;
    }
    return 0;
}

