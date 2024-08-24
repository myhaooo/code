#include<bits/stdc++.h>
using namespace std;
#define clear(a) memset(a, 0, sizeof(a))
#define ll long long
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
    #define 下面是代码 上面是模版------------------
    mt19937 myrand(time(0));
    for(int i=0;i<100000;i++){
        int n=myrand()%49995;
        cout<<2<<" "<<n<<" "<<n+50000<<" "<<myrand()%(int)1e3<<endl;
    }


}