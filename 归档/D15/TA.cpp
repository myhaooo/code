
#include<bits/stdc++.h>
using namespace std;
#define clear(a) memset(a, 0, sizeof(a))
#define ll long long
#define ull unsigned long long
bool be;
const int MAXN=1e6+5;
int n,m,a[MAXN];
ull sum,ans;
bool ed;
signed main(){
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
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    ans=ceil((double)sum/m);
    for(int i=1;i<=n;i++){
        ans=max(ans,1ull*a[i]);
    }
    cout<<ans<<'\n';
}