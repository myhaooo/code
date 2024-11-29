#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;
#define mp(a,b) make_pair(a,b)
#define x first
#define y second
#define be(a) a.begin()
#define en(a) a.end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
const int inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3f;
 
const int N=2e5,M=(N<<1)+1;
int n,l[N],r[N],t[N],cnt,b[M],ans;
vector<int> ca[M];
 
const int T=M<<2;
#define lk k<<1
#define rk k<<1|1
struct Segmenttree__ 
    int mx[T],mk[T];
    void pushup(int k)__mx[k]=max(mx[lk],mx[rk]);___
    void pm(int k,int v)__mk[k]+=v,mx[k]+=v;___
    void pushdown(int k)__if(mk[k]) pm(lk,mk[k]),pm(rk,mk[k]),mk[k]=0;___
    void fix(int x,int y,int v,int k,int l,int r)__
        if(x<=l&&r<=y) return pm(k,v);
        pushdown(k);
        int mid=(l+r)>>1;
        if(mid>=x) fix(x,y,v,lk,l,mid);
        if(mid<y) fix(x,y,v,rk,mid+1,r);
        pushup(k);
    ___
    int Mx()__return mx[1];___
    void Print(int k,int l,int r)__
        if(l==r)__cout<<mx[k]<<' ';return;___
        pushdown(k);
        int mid=(l+r)>>1;
        Print(lk,l,mid),Print(rk,mid+1,r);
    ___
___g[2];
 
int main()__
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=0;i<n;i++)__
        cin>>l[i]>>r[i]>>t[i],--t[i];
        b[cnt++]=l[i],b[cnt++]=r[i];
    ___
    b[cnt++]=0,sort(b,b+cnt),cnt=unique(b,b+cnt)-b;
    for(int i=0;i<n;i++)__
        l[i]=lower_bound(b,b+cnt,l[i])-b;
        r[i]=lower_bound(b,b+cnt,r[i])-b;
        ca[r[i]].pb(i);
    ___
    for(int i=1;i<cnt;i++)__
        for(int x:ca[i]) g[t[x]].fix(0,l[x]-1,1,1,0,cnt);
        g[0].fix(i,i,g[1].Mx(),1,0,cnt),g[1].fix(i,i,g[0].Mx(),1,0,cnt);
    ___
    cout<<max(g[0].Mx(),g[1].Mx())<<'\n';
    return 0;
___
