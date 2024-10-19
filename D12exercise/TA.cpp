#include<bits/stdc++.h>
using namespace std;
#define clear(a) memset(a, 0, sizeof(a))
#define ll long long

const int maxn = (1 << 22) + 100;
const int mod = 998244353;
int cnt[maxn], f[30];
int son[30];
ll ans[maxn];

signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif
    int n, m, x, y;
    cin>>n>>m;
    for (int i = 1; i <= m; i++) {
        cin>>x>>y;
        son[x] = son[x] | (1 << (y - 1));
    }
    int all = (1 << n);
    for (int i = 1; i < all; ++i) cnt[i] = cnt[(i >> 1)] + (i & 1); 
    f[0] = 1;
    for (int i = 1; i <= n; i++)
        f[i] = f[i - 1] << 1;  //2^i
    ans[0] = 1;
    for (int s = 0; s < all; s++) {
        if (ans[s] > 0) {
            for (int i = 1; i <= n; i++) {
                if ((s & (1 << (i - 1))) == 0)
                    ans[(s | (1 << (i - 1)))] =
                            (ans[(s | (1 << (i - 1)))] + ans[s] % mod * f[cnt[(s & son[i])]] % mod) % mod;
            }
        }
    }
    //cout<<ans[all - 1]<<'\n';
    return 0;
}



 
