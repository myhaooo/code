#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 1010010
double cal(ll x1,ll y1,ll x2,ll y2){
    return sqrt((double)((x1-x2)*(x1-x2))+(double)((y1-y2)*(y1-y2)));
}
ll n,m,k;
double ans;
ll x[MAXN],y[MAXN];
double dis[MAXN];
bool vis[MAXN];
int main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    for(ll i=1;i<=k;i++){
        scanf("%lld%lld",&x[i],&y[i]);
        dis[i]=y[i];
    }
    dis[k+1]=m;
    while(1){
        ll mi=0;
        for(ll j=1;j<=k+1;j++)
            if(!vis[j]&&(mi==0||dis[j]<dis[mi]))
                mi=j;
//        printf("mi=%lld\n",mi);
        ans=max(ans,dis[mi]);
        vis[mi]=1;
        if(mi==k+1){
            printf("%.10lf\n",ans/2);
            return 0;
        }
        for(ll j=1;j<=k;j++)
            dis[j]=min(dis[j],cal(x[j],y[j],x[mi],y[mi]));
        dis[k+1]=min(dis[k+1],(double)(m-y[mi]));
    }
}