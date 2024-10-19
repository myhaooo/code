#include<bits/stdc++.h>
#define MAXN 3005
#define ll long long
using namespace std;
const int mod=1e9+7;
ll n,in_deg[MAXN],root,son_num[MAXN],ans=0;
ll to[MAXN],nxt[MAXN],pre[MAXN],cnt;
void add(ll u,ll v){
    cnt++,to[cnt]=v,nxt[cnt]=pre[u],pre[u]=cnt;
}
ll qpow(ll a,ll b,ll p){
    ll ans=1;
    for(;b;b>>=1){
        if(b&1) ans=ans*a%p;
        a=a*a%p;
    }
    return ans;
}
ll size[MAXN],g[MAXN],h[MAXN],f[MAXN][MAXN];//f[i][j]表示在点 i 为根的子树中,向下最长轻链长度小于等于 j 的概率,h表示临时的f数组，g[x][i]表示x节点之前的儿子中最长轻链长度(包括x)小于等于k的概率，但第一维可以随时清空，所以只有g[i]
void dfs(ll x){
    size[x]=1;
    for(ll i=pre[x];i;i=nxt[i]){
        ll y=to[i];
        dfs(y),size[x]+=size[y];
    }
    ll q=qpow(son_num[x],mod-2,mod);
    for(ll i=pre[x];i;i=nxt[i]){//枚举重儿子
        for(ll j=0;j<=n;j++) g[j]=1;
        ll h_son=to[i];//heavy son
        for(ll j=pre[x];j;j=nxt[j]){//枚举其他儿子
            ll a_son=to[j];//another son
            for(ll k=0;k<=size[a_son]+1;k++){
                ll gs=g[k],fs=f[a_son][k];//gs为a_son之前考虑的儿子中最长轻链长度为k的概率
                if(k) gs-=g[k-1],fs-=f[a_son][k-1];
                if(a_son==h_son) h[k]=(gs*f[a_son][k]%mod+fs*g[k]%mod-fs*gs%mod+mod)%mod;//若a_son为重儿子，fs为以a_son为根的子树最长轻链长度为k的概率
                else{
                    fs=f[a_son][k-1];if(k>1) fs-=f[a_son][k-2];//若a_son为轻儿子，则设fs为以a_son为根的子树最长轻链长度为k-1的概率
                    h[k]=(gs*f[a_son][k-1]%mod+fs*g[k]%mod-gs*fs%mod+mod)%mod;
                }
            }
            g[0]=h[0],h[0]=0;
            for(ll k=1;k<=size[a_son]+1;k++) g[k]=(g[k-1]+h[k])%mod,h[k]=0;
        }
        for(ll j=size[x];j>=1;j--) g[j]=(g[j]-g[j-1]+mod)%mod;
        for(ll j=0;j<=size[x];j++) f[x][j]=(f[x][j]+g[j]*q%mod)%mod;
    }
    if(!pre[x]) f[x][0]=1;
    for(ll i=1;i<=size[x]+1;i++)
        f[x][i]=(f[x][i]+f[x][i-1])%mod;
    return ;
}
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++){
        scanf("%lld",&son_num[i]);
        for(ll j=1,son;j<=son_num[i];j++){
            scanf("%lld",&son);
            add(i,son);
            in_deg[son]++;
        }
    }
    for(ll i=1;i<=n;i++){
        if(!in_deg[i]){
            root=i;
            break;
        }
    }
    dfs(root);
    for(ll i=1;i<=n;i++)
        ans=(ans+i*(f[root][i]-f[root][i-1]+mod)%mod)%mod;
    printf("%lld\n",ans);
    return 0;
}