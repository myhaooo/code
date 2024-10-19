#include <cstdio>
struct E{
    int to, nxt;
} e[400050];
int n, c, x, y, o = 1, a[200050], w[200050], dep[200050], head[200050];
void add(int u, int to)
{
    e[++c] = {to, head[u]};
    head[u] = c;
}
void dfs1(int u, int k)
{
    if (dep[u] > dep[x])
        x = u;
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v= e[i].to) != k)
            dep[v] = dep[u] + 1, dfs1(v, u);
}
void dfs2(int u, int k)
{
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != k)
            dfs2(v, u), w[u] |= w[v];
}
void dfs3(int u, int k)
{
    a[u] = o;
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != k && !w[v])
            ++o, dfs3(v, u), ++o;
    for (int i = head[u], v; i; i = e[i].nxt)
        if ((v = e[i].to) != k && w[v])
            ++o, dfs3(v, u);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i)
        scanf("%d%d", &u, &v), add(u, v), add(v, u);
    dfs1(dep[1] = 1, 0);
    dep[y = x] = 1;
    dfs1(y, x = 0);
    w[y] = 1;
    dfs2(x, 0);
    dfs3(x, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d ", a[i]);
    return 0;
}