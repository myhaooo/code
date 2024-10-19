#include<bits/stdc++.h>
using namespace std;
constexpr int N = 1e6 + 500;
int n, a[N], b[N], cnt, ans[N], tot;
bitset<N> vis, f; stack<bitset<N>> st;
inline void solve(int k, int id){
    if(k == 0 || id == 0) return;
    bitset<N> pre = st.top(); st.pop();
    if(pre[k]){
        ans[++tot] = a[id];
        solve(((k - b[id]) % n + n) % n, id - 1);
    }
    else solve(k, id - 1);
}
int main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        #ifdef LEN
        fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        //#include "../local.h"
    #endif

    cin>>n;
    for(int i=1; i<=n; ++i){
        cin>>(a[i]);
        if(!(a[i] % n)){
            cout<<(1)<<'\n'<<(i);
            return 0;
        }
        if(!vis[a[i] % n]){
            vis[a[i] % n] = 1;
            b[++cnt] = a[i] % n;
        }
    }
    f[0] = 1;
    for(int i=1; i<=cnt; ++i){
        f |= f << b[i];
        f |= f >> (n - b[i]);
        if(f[n]){
            ans[++tot] = a[i];
            solve(n - b[i], i - 1);
            if(tot==0)return 2;
            cout<<(tot)<<endl;
            for(int j=1; j<=tot; ++j) cout<<(ans[j])<<endl;
            return 0;
        }
        st.push(f);
    }
    exit(0);
}