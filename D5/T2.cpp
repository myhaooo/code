#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

const int N = 3e5 + 10;
const int inf = 0x3f3f3f3f;
int n, m;
std::vector < int > f[N];
int F[N], G[N];
int l, r, mid, cnt;

void dfs (int x, int fa) {
    F[x] = 0, G[x] = inf;
    for (int i = 0; i < int (f[x].size()); i++) {
        int to = f[x][i];
        if (to == fa) continue;
        dfs (to, x);
        F[x] = std::max(F[to] + 1, F[x]);
        G[x] = std::min(G[to] + 1, G[x]);
    }
    if (G[x] + F[x] <= mid) F[x] = -inf;
    if (F[x] == mid) {
        ++cnt; F[x] = -inf; G[x] = 0;
    }
}

bool check () {
    cnt = 0;
    dfs (1, 0);
    if (F[1] >= 0) cnt++;
    return cnt <= m;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        f[u].push_back(v);
        f[v].push_back(u);
    }
    l = 0, r = n;
    while (l < r) {
        mid = (l + r) / 2;
        if (check()) r = mid;
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}