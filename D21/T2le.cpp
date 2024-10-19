#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1e4 + 5, M = 4e4 + 5;
#define p pair<int, int>
int T, n, m, h[N], cnt, dis[N], ans = INT_MAX, dfn[N], low[N], tot, st[N], sc, num[N], sh[N], scnt;
vector<int> sG[N];
bitset<N> vis;
bitset<M> flag;
template <typename T> inline void rd(T &x){
    x = 0; char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^48);
        ch = getchar();
    }
}
template <typename T2> inline void wt(T2 x){
    if(x<0) putchar('-'), x = -x;
    if(x/10 > 0) wt(x / 10);
    putchar(x%10 + '0');
}
struct edge{ int v, nxt, val, id; }e[M<<1], se[M<<1];
inline void add(int u, int v, int val, int id){
	e[++cnt] = edge{v, h[u], val, id}; h[u] = cnt;
}
inline void sadd(int u, int v, int val, int id){
	se[++scnt] = edge{v, sh[u], val, id}; sh[u] = scnt;
}
inline void tarjan(int u, int f){
	dfn[u] = low[u] = ++tot;
	st[++st[0]] = u;
	for(int i=h[u]; i; i=e[i].nxt){
		int v = e[i].v;
		if(!dfn[v]){
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
		} else low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]){
		++sc; int v;
		do{
			v = st[st[0]--];
			sG[sc].push_back(v);
			num[v] = sc;
		} while(v != u);
	}
}
inline void dijkstra(){
	priority_queue<p, vector<p>, greater<p> > q;
	memset(dis, 0x7f, sizeof dis);
	dis[1] = 0; q.push((p){0, 1});
	while(!q.empty()){
		p t = q.top(); q.pop();
		int u = t.second;
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i=sh[u]; i; i=se[i].nxt){
			int v = se[i].v;
			if(dis[v] > dis[u] + se[i].val){
				dis[v] = dis[u] + se[i].val;
				q.push((p){dis[v], v});
			}
		}
	}
}
inline void DP(int u, int x){
	if(x + dis[u] > ans) return;
	for(int i=sh[u]; i; i=se[i].nxt){
		int v = se[i].v;
		if(flag[se[i].id]) continue;
		int y = x + se[i].val;
		if(v == 1){
			ans = min(ans, x + se[i].val);
			continue;
		}
		flag[se[i].id] = 1;
		DP(v, y);
		flag[se[i].id] = 0;
	}
}
int main(){
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



	// freopen("t2.in", "r", stdin);
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	rd(T); while(T--){
		rd(n), rd(m);
		for(int i=1, x, y, z; i<=m; ++i){
			rd(x), rd(y), rd(z);
			add(x, y, z, i), add(y, x, z, i);
		}
		for(int i=1; i<=n; ++i) if(!dfn[i]) tarjan(i, 0);
		for(int u : sG[num[1]]){// printf("u = %d\n", u);
			for(int i=h[u]; i; i=e[i].nxt){
				int v = e[i].v;
				if(num[v] != num[1]) continue;
				else sadd(u, v, e[i].val, e[i].id);
			}
		}
		dijkstra();
		DP(1, 0);
		if(ans == INT_MAX) wt(-1), putchar('\n');
		else wt(ans), putchar('\n');
		// memset(e, 0, sizeof e);
		memset(h, 0, sizeof(h));
		// memset(se, 0, sizeof se);
		memset(sh, 0, sizeof(sh));
		memset(dfn, 0, sizeof(int) * (n+1));
		memset(low, 0, sizeof(int) * (n+1));
		cnt = scnt = 0; vis.reset(); flag.reset();
		ans = INT_MAX;
	} return 0;
}