#include<bits/stdc++.h>
using namespace std;
#define clear(a) memset(a, 0, sizeof(a))
#define ll long long
#define ull unsigned long long
#define int long long
bool be;
const int MAXN=2e5+5;
int T,a[MAXN],n,sum;
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
    cin>>T;
    while (T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        if(a[1]==n&&a[n]==1){
            cout<<"3"<<'\n';
            continue;
        }
        for(int i=2;i<=n;i++){
            if(a[i]<a[i-1]){
                goto ed1;
            }
        }
        cout<<"0"<<'\n';
        continue;
        ed1:;
        sum=0;
        for(int i=1;i<=n;i++){
            sum+=a[i];
            if(sum==i*(i+1)/2 && a[i]==i){
                goto ed2;
            }
            
        }
        cout<<"2"<<"\n";
        continue;
        ed2:;
        cout<<"1"<<'\n';
        continue;


    }

}
