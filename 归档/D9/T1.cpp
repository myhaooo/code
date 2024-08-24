#include<bits/stdc++.h>
#define int long long 
using namespace std;
constexpr int MAXN=2005;
int n,lenA,lenB,a[MAXN],b[MAXN],c[MAXN];
int ans[MAXN*MAXN], cnt;
signed main()
{
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    #define NDEBUG
    cin.tie(0),cout.tie(0);
    #define clear(a) memset(a, 0, sizeof(a))
    #else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #include "../local.h"
    #endif
    cin>>n;
    for(int i=1;i<=n;++i) 
        cin>>a[i];
    for(int i=1;i<=n;++i) 
        cin>>b[i];

    sort(a+1,a+n+1);lenA=unique(a+1,a+n+1)-(a+1);
    sort(b+1,b+n+1);lenB=unique(b+1,b+n+1)-(b+1);
    for(int i=1,x;i<=lenA;++i){
        x=b[i]^a[2];
        for(int j=1;j<=lenA;++j)
            c[j]=a[j]^x;
        sort(c+1,c+lenA+1);
        for(int j=1;j<=lenA;++j)
            if(b[j]!=c[j]){
                goto ed;
            }
       ans[++cnt]=x;
       ed:;
    }
    cout<<cnt<<"\n";
    for(int i=1;i<=cnt;++i) cout<<ans[i]<<"\n";
    return 0;
}