#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1000005;

int fa[MAXN], deg[MAXN];
long long ans;
int a[MAXN], b[MAXN], n, m, huan;
inline int find(int u){
	if(u == fa[u]) return u;
	return fa[u] = find(fa[u]);
}

inline void merge(int u, int v){
	int ufa = find(u), vfa = find(v);
	if(ufa != vfa) fa[ufa] = vfa;
}
signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
    	//fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif

    cin>>n>>m;
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= m; i++){
		cin>>a[i]>>b[i];
		merge(a[i], b[i]);
		if(a[i] == b[i]) huan++;
		else{
			deg[a[i]]++;
			deg[b[i]]++;
		}
	}
	int begin = find(a[1]);
	for(int i = 2; i <= m; i++)
		if(find(a[i]) != begin)
			return cout<<0, 0;
	ans += (huan - 1) * huan / 2 ;
    ans += huan * (m - huan);
	for(int i = 1; i <= n; i++)
		ans +=deg[i] * (deg[i] - 1) / 2;
	cout<<ans<<"\n";
	return 0;
}