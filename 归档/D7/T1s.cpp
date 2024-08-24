#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#define Mod 1000000007
#define ll long long
using namespace std;
ll n,m,mod1,mod2,g,b=1;
ll p[34][1005],f[2][1005],xp[1005],a[1005],cnt[1005];
ll get(ll x)
{
    for(int i=1;i<=x;i++)
    {
        ll p=1;bool flag=1;
        for(int j=1;j<x-1;j++)
        {
            p=p*i%mod1;
            if(p==1){flag=0;break;}
        }
        if(flag)return i; 
    }
}
int main()
{
    //freopen("rand.in","r",stdin);
    //freopen("rand.out","w",stdout);
    scanf("%lld%lld%lld",&n,&m,&mod1);mod2=mod1-1;
    for(ll x=Mod-2,y=n;x;x/=2,y=y*y%Mod)if(x&1)b=b*y%Mod;
    g=get(mod1);xp[0]=1;int x;
    for(int i=1;i<=mod1;i++)xp[i]=xp[i-1]*g%mod1;
    for(int i=0;i<mod2;i++)a[xp[i]]=i;
    for(int i=1;i<=n;i++)scanf("%d",&x),cnt[a[x]]++;
    for(int i=0;i<mod2;i++)p[0][i]=b*cnt[i]%Mod;
    for(int i=1;i<=32;i++)
        for(int j=0;j<mod2;j++)
            for(int k=0;k<mod2;k++)
                (p[i][(j+k)%mod2]+=p[i-1][j]*p[i-1][k]%Mod)%=Mod;
    f[0][0]=1;
    for(int k=0;m;m/=2,k++)
    {
        if(m&1)
        {
            for(int i=0;i<mod2;i++)f[1][i]=0;
            for(int i=0;i<mod2;i++)
                for(int j=0;j<mod2;j++)
                   (f[1][(i+j)%mod2]+=f[0][i]*p[k][j]%Mod)%=Mod; 
            for(int i=0;i<mod2;i++)f[0][i]=f[1][i];
        }
    }   
    ll ans=0;   
    for(int i=0;i<mod2;i++)(ans+=f[0][i]*xp[i]%Mod)%=Mod;
    cout<<ans;
}