#include<bits/stdc++.h>
using namespace std;
int n=100;
signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
    	//fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","w",stdout);
        #include "../local.h"
    #endif


    mt19937 myrand(5);
    cout<<n<<"\n";
    for(int i=1;i<=n;i++){
        cout<<myrand()%(int)1e4<<"\n";

    }
}