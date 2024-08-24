
#include<bits/stdc++.h>
using namespace std;
#define val(x)  (siz[x]-w[x]-dep[x])
const int MAXN=2e5+5;
vector<int> edge[MAXN];
int n,w[MAXN],dep[MAXN],siz[MAXN],p[MAXN],ans;

bool cmp(int a,int b){
    return val(a)>val(b);
}

void dfs(int u){
    int fa=p[u];
    siz[u]=1;dep[u]=dep[fa]+1;
    for(auto v:edge[u]) dfs(v),siz[u]+=siz[v];
}

int main()
{
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        // double CODE_USE_MEM=abs(&be - &ed) / 1048576.0;
    	// fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n",CODE_USE_MEM);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    
    cin>>n;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=2;i<=n;i++){
        cin>>p[i];
        edge[p[i]].push_back(i);
    }
    dfs(1);
    for(int i=1;i<=n;i++) p[i]=i;
    sort(p+1,p+n+1,cmp);
    for(int i=1;i<=n;i+=2) ans+=val(p[i]);
    cout<<ans;
    return 0;
}