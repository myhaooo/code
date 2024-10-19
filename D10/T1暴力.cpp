#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MOD=1e9+7;
int a,b,c,d,ans;
signed main(){
    cin>>a>>b>>c>>d;
    for(int i=a;i<=b;i++){
        for(int j=c;j<=d;j++){
            int gcdn=__gcd(i,j);
            int z=i/gcdn+j/gcdn;
            ans+=(z>999||z<0)?0:z;
            ans%=MOD;
        }
    }
    cout<<ans;
}