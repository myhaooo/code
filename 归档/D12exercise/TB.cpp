#include<bits/stdc++.h>
using namespace std;
bool be;
const int MAXN=1e5+5;
struct node{int v, w;};
vector<node> G1[MAXN],G2[MAXN];
int T, N, M, K, P;
bool fail;
int f[MAXN][51];//f[u][k]表示从1号节点走到u号节点，路径长度为d[u]+k的方案总数。
int d[MAXN];//d[u]表示从1号节点走到u号节点的最短路长度
bitset<MAXN> vis;
bool ins[MAXN][51];
bool ed;
void Dij(){
    vis.reset();
    memset(d,0x3f,sizeof d);
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0,1));
    d[1]=0;
    while(q.size()){
        int u=q.top().second;
        q.pop();
        if(vis[u])continue;
        vis[u]=1;
        for(auto it=G1[u].begin();it!=G1[u].end();it++){
            int v=it->v,w=it->w;
            if(d[u]+w<d[v]){
                d[v]=d[u]+w;
                q.push(make_pair(-d[v],v));
            }
        }
    }
}
inline int dp(int u, int k) {
    if (k < 0) return 0;
    if (ins[u][k]){
        fail = 1;
        return 0;
    }
    if (f[u][k]) return f[u][k];
    ins[u][k] = 1;
    int ans = 0;
    for (auto it = G2[u].begin(); it != G2[u].end(); it++) {
        int p = it->v, w = it->w;
        ans = (ans + dp(p, d[u] - d[p] + k - w))%P;
        if (fail == 1) return 0;
    }
    ins[u][k] = 0;
    return f[u][k] = ans;
}
int main() {
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
    	fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif
    cin>>T;
    while (T--) {
        memset(ins,0,sizeof ins);
        for (register int i = 1; i <= N; ++i) {
            G1[i].clear(), G2[i].clear();
        }
        cin>>N>>M>>K>>P;
        for (register int i = 1; i <= M; ++i) {
            int u, v, w;
            cin>>u>>v>>w;
            G1[u].push_back((node){v, w});
            G2[v].push_back((node){u, w});
        }
        Dij();
        dp(1, 0);
        f[1][0] = 1;
        int ans = 0;
        for (register int i = 0; i <= K; ++i) {
            ans = (ans + dp(N, i))%P;
        }
        if(fail == 1) puts("-1");
        else printf("%d\n", ans);
        fail = 0;
        memset(f, 0, sizeof(f));
        for (register int i = 1; i <= N; ++i) {
            G1[i].clear(), G2[i].clear();
        }
    }
}