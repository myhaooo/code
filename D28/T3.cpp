#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=2e5+10,mod=998244353;
int n,k,a[MAXN],cnt[MAXN];ll ans=1,T=1,P=1;
inline int ksm(ll a,int b=mod-2)
{
    ll ans=1;
    for(;b;b>>=1,a=a*a%mod)
        if(b&1) ans=ans*a%mod;
    return ans;
}
int main()
{
    // freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
    cin.tie(0),cout.tie(0);
    ios::sync_with_stdio(0);
    cin>>n>>k;
    for(int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+1+n);
    for(int i=1;i<=n&&a[i]<=(k-1)/2;++i)
    {
        if(a[n]+a[i]<k) cout<<"0\n",exit(0);
        ++cnt[lower_bound(a+1,a+n+1,k-a[i])-a];
    }
    for(int i=n;i&&a[i]>(k-1)/2;--i)
    {
        ans=ans*T%mod,++T;
        for(int j=1;j<=cnt[i];++j)
            ans=ans*T%mod,--T;
    }
    for(int i=1,j=1;i<=n;i=j)
    {
        while(a[j]==a[i]) ++j;
        for(int k=1;k<=j-i;++k)
            P=P*k%mod;
    }
    cout<<ans*ksm(P)%mod<<'\n';return 0;
}