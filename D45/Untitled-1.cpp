#include<bits/stdc++.h>
using namespace std;
main(){
    //ios::sync_with_stdio(false);
    #ifndef LOCAL
    #define NDEBUG
    	cin.tie(0), cout.tie(0);
    #define file(a)                               \
    	FILE *FI = freopen(#a ".in", "r", stdin); \
    	FI = freopen(#a ".out", "w", stdout)
    	//file();
    #else
    #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
    #endif
    	freopen("in.in", "w", stdout);
    	// #include "../local.h"
    #endif

    int n=1e6;
    cout<<n<<endl;
    mt19937_64 myrand(time(0));
    for(int i=1;i<=n;i++){
        cout<<myrand()%LLONG_MAX<<" ";
    }
}