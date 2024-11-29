#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10, INF = 1e9;
int n, len, pos, m, dis[N];
bool vis[N], fail[N];
struct Queue
{
    int l, r, num[N];
    void push(int x) { num[++r] = x; }
    void pop() { l++; }
    int front() { return num[l]; }
    bool empty() { return l > r; }
} q;

bool check() { 
    return 1;
    return (double)((double)clock() / (double)CLOCKS_PER_SEC) <= 0.995; 
}

void SPFA()
{

    dis[pos] = 0;
    q.push(pos);
    vis[pos] = true;
    while (!q.empty() && check())
    {
        int x = q.front();
        q.pop();
        int fro = max(1, x + len - n), to = min(x, len);
        for (int i = fro, id = x - 2 * i + len + 1; i <= to; i++, id = x - 2 * i+len + 1)
            if (id >= 1 && id <= n)
                if (fail[id] && dis[id] - dis[x] + 1)
                    dis[id] = dis[x] + 1, q.push(id), vis[id] = true;
    }
}

signed main()
{

    cin >> n >> len >> m >> pos;
    for (int i = 1, x; i <= m; i++)
    {
        cin >> x;
        fail[x] = 1;
    }
    memset(dis, 0x3f, sizeof(dis));
    SPFA();
    for (int i = 1; i <= n; i++)
        cout << (dis[i] >= INF ? -1 : dis[i]) << " ";
}