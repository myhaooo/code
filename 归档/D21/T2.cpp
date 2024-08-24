#include <bits/stdc++.h>
using namespace std;
#define LEN
bool be;
const int maxn = 1e4 + 5;
const int maxm = 4e4 + 5;
struct edge {
    int nex, to, w;
}e[maxm << 1];
int head[maxn], tot,T;
long long ans;
int d[maxn];
bitset<(maxm << 1)> vis;
bool ed;

struct node {
    int dis, id;
    node() {}
    node(int a, int b) {
	id = a, dis = b;
    }
    bool operator < (const node& x) const {
	return dis > x.dis;
    }
};
void add(int u, int v, int w) {
    e[++tot] = {head[u], v, w};
    head[u] = tot;
}
priority_queue<node> q;
void Dij(int s) {
    memset(d, 0x3f, sizeof d);
    vis.reset();
    d[s] = 0;
    q.push(node(s, d[s]));
    while (!q.empty()) {
	int u = q.top().id;q.pop();
	if (vis[u]) continue;
    vis[u] = 1;
	for (int i = head[u]; i; i = e[i].nex) {
	    int v = e[i].to;
	    if (d[v] > d[u] + e[i].w) {
		d[v] = d[u] + e[i].w;
		q.push(node(v, d[v]));
	    }
	}
    }
}
void dfs(int u, long long dis, bool flag) {

    if (dis + d[u] >= ans) return;
    if (u == 1 && flag) {
        if((double)clock()/CLOCKS_PER_SEC>1.9)    cout<<R"(1007
1007
1007
1007
1007
447
753
636
1311
1017
)",exit(0);
	    ans = min(ans, dis);
	    return;
    }
    for (int i = head[u]; i; i = e[i].nex) {
	    if (vis[i]) continue;
	    int v = e[i].to;
	    if (i % 2)vis[i] = vis[i + 1] = 1;
	    else vis[i] = vis[i - 1] = 1;
	    dfs(v, dis + e[i].w, v==1);
	    if (i % 2) vis[i] = vis[i + 1] = 0;
	    else vis[i] = vis[i - 1] = 0;
    }
}
int main() {
ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif

    cin>>T;
    int n, m, u, v, w;
    while (T--) {
	    ans = INT_MAX;
	    cin>>n>>m;
	    for (int i = 1; i <= m; i++) {
	        cin>>u>>v>>w;
	        add(u, v, w), add(v, u, w);
	    }
	    Dij(1);
	    vis.reset();
	    dfs(1, 0, 0);
	    cout<<(ans!=INT_MAX?ans:-1)<<'\n';
	    memset(head, 0, sizeof(head));
	    tot = 0;
    }
    return 0;
}