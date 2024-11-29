#include <iostream>
#include <vector>
#define x first
#define y second
using namespace std;
using PII = pair<int, int>;
const int dir[][2] = {1, 0, 0, 1, -1, 0, 0, -1};
const int INF = 1e9;
 
vector<vector<int>> g;
vector<vector<int>> dis[170];
int n, m, k, Q;
PII q[50], que[200010]; 
void bfs(int x, int y, vector<vector<int>>& dis) {
    int hh = 0, tt = -1;
    que[++tt] = {x, y};
    dis[x][y] = 0;
    while (hh <= tt) {
        auto [x, y] = que[hh++];
        for (auto d : dir) {
            int tx = x + d[0], ty = y + d[1];
            if (tx < 1 || tx > n || ty < 1 || ty > m || g[tx][ty] == 1) continue;
            if (dis[tx][ty] != 1e9) continue;
            que[++tt] = {tx, ty};
            dis[tx][ty] = dis[x][y] + 1;
        }
    }
}
 
int main() {
		freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
    cin >> n >> m >> k >> Q;
    g = vector<vector<int>>(n + 5, vector<int>(m + 5));
    int cnt = 0;
    for (int i = 1; i <= k; i++) {
        cin >> q[i].x >> q[i].y;
        g[q[i].x][q[i].y] = 1;
    }
    
    
    for (int i = 1; i <= k; i++) {
        for (auto d : dir) {
            int tx = q[i].x + d[0], ty = q[i].y + d[1];
            if (tx < 1 || tx > n || ty < 1 || ty > m || g[tx][ty] == 1) continue;
            dis[++cnt] = vector<vector<int>>(n + 5, vector<int>(m + 5, INF));
            bfs(tx, ty, dis[cnt]);
        }
    }
    
    while (Q--) {
        int x0, y0, x1, y1;
        bool flag = false;
        cin >> x0 >> y0 >> x1 >> y1;
        int a = min(x0, x1), b = max(x0, x1);
        int c = min(y0, y1), d = max(y0, y1);
 
        for (int i = 1; i <= k; i++) {
            auto& [x, y] = q[i];
            if (x >= a && x <= b && y >= c && y <= d) flag = true;
        }
        
        if (!flag) cout << abs(x0 - x1) + abs(y0 - y1) << '\n';
        else {
            int res = INF;
            for (int i = 1; i <= cnt; i++)
                res = min(res, dis[i][x0][y0] + dis[i][x1][y1]);
            if (res == INF) res = -1;
            cout << res << '\n';
        }
    }
    return 0;
}
