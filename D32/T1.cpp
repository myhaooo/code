#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int T;
int pri[N],bi[N],cnt;
bool vis[N];

void ask_prime(int n){
    for(int i=2;i<=n;i++)
    {
        if(!vis[i]) pri[++cnt]=i;
        for(int j=1;j<=cnt;j++)
        {
            if(i*pri[j]>n) break;
            vis[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }

}
signed main()
{
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    #define NDEBUG
    	cin.tie(0), cout.tie(0);
    #define file(a)                               \
    	FILE *FI = freopen(#a ".in", "r", stdin); \
    	FI = freopen(#a ".out", "w", stdout)
    	// file();
    #else
    #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
    #endif
    	freopen("in.in", "r", stdin);
    	freopen("out.out", "w", stdout);
    	// #include "../local.h"
    #endif
    ask_prime(1000000);
    cin>>T;
    while(T--)
    {
        int a,l,r;
        cin>>a>>l>>r;
        for(int j=1;j<=cnt;j++)
        {
            if(pri[j]*pri[j]>a) break;
            int cas=pri[j]*pri[j];
            while(a%cas==0) a/=cas;
        }
        int b=l/a;
        b=sqrt(b);
        if(b*b*a==l)
        {
            cout<<b*b*a<<"\n";
            continue;
        }
        if((b+1)*(b+1)*a>r) cout<<(-1)<<'\n';
        else cout<<(b+1)*(b+1)*a<<"\n";
    }
    return 0;
}
