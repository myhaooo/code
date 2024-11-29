#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = (int)5e5 + 5;
int r[maxn], w[maxn], g[maxn];
int m,n,q,t;;
signed main() {
    cin>>n>>m;
    mt19937 myrand(time(0));
    for (int u = 1; u <= n; ++u)
        w[u] = myrand();
    int tar = accumulate(w + 1, w + n + 1, 0LL);
    int now = 0;
    while (m--) {
        int u,v;
        cin>>u>>v;
        r[v] += w[u];
        g[v] = r[v];
        now += w[u];
    }
    cin>>q;
    while (q--) {
        cin>>t;
        if (t == 1) {
            int u,v;
        cin>>u>>v;
            r[v] -= w[u];
            now -= w[u];
        } else if (t == 2) {
            int u,v;
        cin>>v;
            now -= r[v];
            r[v] = 0;
        } else if (t == 3) {
           int u,v;
        cin>>u>>v;
            r[v] += w[u];
            now += w[u];
        } else if (t == 4) {
            int u,v;
        cin>>v;
            now += g[v] - r[v];
            r[v] = g[v];
        }

        puts(now == tar ? "YES" : "NO");
    }

    return 0;
}
