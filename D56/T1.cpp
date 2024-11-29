#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5+5;
bitset<MAXN>vis; 
int n, k;
vector<tuple<int, int, int>> colors;
int bfs(int start,int &val) {
    queue<int> q;
    q.push(start);
    vis[start] = true;
    int size = 0;
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        size++;
        auto [r1, g1, b1] = colors[u];
        
        for (int v = 0; v < n; ++v) {
            if (!vis[v]) {
                auto [r2, g2, b2] = colors[v];
                int diff = max({abs(r1 - r2), abs(g1 - g2), abs(b1 - b2)});
                if (diff <= val) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    
    return size;
};
bool check(int val) {
    vis.reset();
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            if (bfs(i,val) >= k) return true;
        }
    }

    return false;
}

int main() {
    freopen("rgb.in", "r", stdin);
    freopen("rgb.out", "w", stdout);
    cin >> n >> k;
    colors.resize(n);
    
    for (int i = 0; i < n; ++i) {
        int r, g, b;
        cin >> r >> g >> b;
        colors[i] = make_tuple(r, g, b);
    }

    int l = 0, r = 256, answer = 255;
    
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            answer = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    cout << answer << endl;
    return 0;
}

