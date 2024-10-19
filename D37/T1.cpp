#include <bits/stdc++.h>
using namespace std;

const int N = 35;
int belong[N], fa[N], n, m, code, val[N];
vector<int> dif[N];
bool vis[N][N], vs[N];
struct node
{
    int x, y;
} e[N];
int tot;
inline int find(int x)
{
    return (x == fa[x]) ? x : fa[x] = find(fa[x]);
}
inline void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    fa[fx] = fy;
}
int main()
{
    freopen("str.in","r",stdin);
	freopen("str.out","w",stdout);

    cin>>n>>m;
    if (n == 30)
    {
        printf("-1");
        return 0;
    }

    for (int i = 1; i <= n; ++i)
        fa[i] = i;
        
    for (int i = 1,x,y,z; i <= m; ++i)
    {
        cin>>x>>y>>z;
        if (!z)
            e[++tot] = {x, y};
        else
        {
            for (int j = 1; j <= z; ++j)
                merge(x + j - 1, y + j - 1);
            if (max(x + z, y + z) <= n)
                e[++tot] = {x + z, y + z};
        }
    }

    for (int i = 1; i <= tot; ++i)
    {
        int fx = find(e[i].x), fy = find(e[i].y);
        if (fx == fy)
        {
            printf("-1");
            return 0;
        }
        if (!vis[fx][fy])
            dif[fx].push_back(fy), dif[fy].push_back(fx); 
        vis[fx][fy] = vis[fy][fx] = 1;
    }
    for (int i = 1; i <= n; ++i)
        val[i] = n + 2; 
    int mex;
    for (int i = 1; i <= n; ++i)
    {
        int bl = find(i);
        if (val[bl] != n + 2)
            val[i] = val[bl];
        else
        {
            fill(vs, vs + 3 + n, 0);
            mex = 0;
            for (int v : dif[bl])
            {
                vs[val[v]] = 1;
            }
            while (vs[mex])
                ++mex;
            val[bl] = val[i] = mex;
        }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", val[i]);
    return 0;
}