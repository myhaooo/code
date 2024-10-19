#include<bits/stdc++.h>
#define int long long
using namespace std;
bool be;
const int N=3e5+5;
int n,q;
int tot,lmin,rmax,a[N],L[N],R[N];
bool overl[N],overr[N];
struct node{
	int id,dis;
}d[N];
bool ed;
#define LEN
bool cmp(node a,node b){return a.dis<b.dis;}
signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif

    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        if(i>1) 
            d[i-1].dis=a[i]-a[i-1],
            d[i-1].id=i-1;
    }
    sort(d+1,d+n,cmp);
    int now=1;
    for(int i=1;i<=q;i++){
        int w;cin>>w;
        tot+=w;
        if(tot>0) rmax=max(rmax,tot);
        else lmin=min(lmin,tot);
        while(now<=n-1 && rmax-lmin>=d[now].dis){
            int xi=d[now].id,xj=xi+1;
            if(tot>0) 
                L[xj]=a[xj]+lmin,R[xi]=L[xj];
            else 
                R[xi]=a[xi]+rmax,L[xj]=R[xi];
            overl[xj]=1,overr[xi]=1;
            now++;
        }
    }
    for(int i=1;i<=n;i++){
        if(overl[i]==0) L[i]=a[i]+lmin;
        if(overr[i]==0) R[i]=a[i]+rmax;
        cout<<(R[i]-L[i])<<'\n';
    }
    return 0;
}
