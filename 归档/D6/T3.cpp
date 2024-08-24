#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e5+5;
int n,m;
struct Node{
    int to,next;
}edge[N<<1];
int head[N],tot;
inline void add(int u,int v){
    edge[++tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot;
}

bool vis[N];
int DEP[N << 1][20], dep[N], in[N], logg[N << 1], cnt;
void dfs(int x,int fa){
    dep[x]=dep[fa]+1;
    in[x]=++cnt;
    DEP[in[x]][0]=dep[x];
    for(int i=head[x];i;i=edge[i].next){
        int v=edge[i].to;
        if(v==fa)continue;
        dfs(v,x);
        DEP[++cnt][0]=dep[x];
    }
}

int lca(int u,int v){
    u=in[u],v=in[v];
    if(u>v)swap(u,v);
    int k=logg[v-u+1];
    return min(DEP[u][k],DEP[v-(1<<k)+1][k]);
}
int DIS(int u,int v){
    if(u==-1||v==-1)return -1;
    return dep[u]+dep[v]-2*lca(v,u);
}
#define lson root<<1
#define rson root<<1|1
struct tree{
    int u,v;
}t[N<<2];


inline void pushup(int root) {
	if (t[lson].u == -1 && t[lson].v == -1) {
		t[root] = t[rson];
		return ;
	}
	if (t[rson].u == -1 && t[rson].v == -1) {
		t[root] = t[lson];
		return ;
	}
	if (DIS(t[lson].u, t[lson].v) > DIS(t[rson].u, t[rson].v)) t[root] = t[lson];
	else t[root] = t[rson];
	if (DIS(t[lson].u, t[rson].u) > DIS(t[root].u, t[root].v)) t[root].u = t[lson].u, t[root].v = t[rson].u;
	if (DIS(t[lson].u, t[rson].v) > DIS(t[root].u, t[root].v)) t[root].u = t[lson].u, t[root].v = t[rson].v;
	if (DIS(t[lson].v, t[rson].u) > DIS(t[root].u, t[root].v)) t[root].u = t[lson].v, t[root].v = t[rson].u;
	if (DIS(t[lson].v, t[rson].v) > DIS(t[root].u, t[root].v)) t[root].u = t[lson].v, t[root].v = t[rson].v;
}
inline tree add(tree a, tree b) {
	//cout << "add:\n";
	//cout << "a: " << a.u << " " << a.v << " b: " << b.u << " " << b.v << "\n";
	if (a.u == -1 && a.v == -1) return b;
	if (b.u == -1 && b.v == -1) return a;
	tree c;
	if (DIS(a.u, a.v) > DIS(b.u, b.v)) c = a;
	else c = b;
	//cout << "c: " << c.u << " " << c.v << "\n";
	if (DIS(a.u, b.u) > DIS(c.u, c.v)) c.u = a.u, c.v = b.u;
	if (DIS(a.u, b.v) > DIS(c.u, c.v)) c.u = a.u, c.v = b.v;
	if (DIS(a.v, b.u) > DIS(c.u, c.v)) c.u = a.v, c.v = b.u;
	if (DIS(a.v, b.v) > DIS(c.u, c.v)) c.u = a.v, c.v = b.v;
	return c;
}
inline void build(int root, int l, int r) {
	if (l == r) {                               
		t[root].u = t[root].v = -1;                  
		return ;
	}
	int mid = l + r >> 1;   
	build(lson, l, mid);
	build(rson, mid + 1, r);
	pushup(root);
}        
inline void modify(int root, int l, int r, int x) {
	if (x < l || x > r) return ;
	if (l == r) {
		if (t[root].u == -1 && t[root].v == -1) t[root].u = t[root].v = x;
		else t[root].u = t[root].v = -1;
		return ;
	}
	int mid = l + r >> 1;
	modify(lson, l, mid, x);
	modify(rson, mid + 1, r, x);
	pushup(root);
}
inline tree query(int root, int l, int r, int ql, int qr) {
	//cout << "begin: " << root << " " << l << " " << r << " " << ql << " " << qr << "\n";
	if (ql > r || qr < l || l > r || ql > qr) return {-1, -1};
	if (ql <= l && r <= qr) {
		return t[root];
	}
	int mid = l + r >> 1;
	tree ans = {-1, -1};
	ans = add(ans, query(lson, l, mid, ql, qr));
	ans = add(ans, query(rson, mid + 1, r, ql, qr));
	return ans;
}


int main() {
	cin.tie(0);
	cout.tie(0)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1, u, v; i <= n - 1; i++) {
		cin >> u >> v;
		add(u, v);
		add(v, u);
	}
	dfs(1, 0);
	for (int i = 2; i <= cnt; i++) logg[i] = logg[i >> 1] + 1;
	for (int j = 1; j <= logg[cnt]; j++) {
		for (int i = 1; i + (1 << j) - 1 <= cnt; i++) {
			DEP[i][j] = min(DEP[i][j - 1], DEP[i + (1 << (j - 1))][j - 1]);
		}
	}

	build(1, 1, n);
	while (m--) {
		int opt, u, l, r;
		cin >> opt;
		if (opt == 1) {
			cin >> u;
			modify(1, 1, n, u);
		} else {
			cin >> l >> r;
			tree top;
			top = query(1, 1, n, l, r);
			cout << DIS(top.u, top.v) << "\n";
		}
	}
	return 0;
}