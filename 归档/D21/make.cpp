#include <bits/stdc++.h>
using namespace std;
int T=10,n=10000,m=20000;
signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","w",stdout);
        #include "../local.h"
    #endif




    mt19937 myrand(time(0));
    cout<<T<<'\n';
    while(T--){
        cout<<n<<' '<<m-2<<'\n';
        for(int i=2;i<=10000;i++){
            cout<<1<<' '<<i<<" "<<myrand()%(int)1e3<<'\n';
        }
        for(int i=3;i<=10000;i++){
            cout<<i-1<<' '<<i<<' '<<myrand()%(int)1e3<<'\n';
        }
        cout<<10000<<' '<<2<<' '<<myrand()%(int)1e3<<'\n';
    }
}