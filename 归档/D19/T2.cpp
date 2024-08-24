#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=205;
vector<int> b;
int n,k,a[N];
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        k+=a[i];
        for(int j=1;j*j<a[i];j++){
           b.push_back(j);
           b.push_back((a[i]-1)/j+1);
        }
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int ans=1;
    for(int i=0;i<b.size();i++){
        int ret=0;
        for(int j=1;j<=n;j++){
            ret+=(a[j]-1)/b[i]+1;
        }
        int mx=k/ret;
        //cout<<mx<<" "<<b[i]<<"\n";
        if(mx>=b[i])ans=mx;
    }
    cout<<ans;
}