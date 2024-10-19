#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
struct node1{
    int a,p;
}a[MAXN];
struct node2{
    int l,r,p;
}q[MAXN];
int n,m,j,ansn,rk[MAXN],cnt[MAXN],ans[MAXN],num[MAXN];
//cnt[i]:共出现i次的有几个数；num[i]:第i个数一共出现了几次 
int len,pos[MAXN];

bool cmp1(node1 a,node1 b){
    return a.a<b.a||(a.a==b.a&&a.p<b.p);
}

bool cmp2(node2 a,node2 b){
    return pos[a.l]<pos[b.l]||(pos[a.l]==pos[b.l]&&a.r<b.r);
}

void add(int x)
{
    int d=num[x];
    if (ansn==d) ansn++;
    cnt[d]--; cnt[d+1]++;
    num[x]++;
}

void del(int x){
    int d=num[x];
    if (ansn==d&&cnt[d]==1) ansn--;
        cnt[d]--; cnt[d-1]++;
        num[x]--;
}

signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
    	//fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif

    cin>>n>>m;
    for (int i=1; i<=n; i++) {
        cin>>a[i].a; a[i].p=i;
    }
    sort(a+1,a+n+1,cmp1);
    for (int i=1; i<=n; i++){
        if (i==1||a[i].a!=a[i-1].a) j++;
        rk[a[i].p]=j;
    }
    
    len=sqrt(n);
    for (int i=1; i<=n; i++) pos[i]=i/len;
    for (int i=1; i<=m; i++) {
        cin>>q[i].l>>q[i].r; 
        q[i].p=i;
    }
    sort(q+1,q+m+1,cmp2);
    
    int x=1,y=0; cnt[0]=j; ansn=0;
    for (int i=1; i<=m; i++){ 
        while (y<q[i].r) {y++; add(rk[y]);}
        while (y>q[i].r) {del(rk[y]); y--;}
        while (x<q[i].l) {del(rk[x]); x++;}
        while (x>q[i].l) {x--; add(rk[x]);}
        ans[q[i].p]=-ansn;
    }
    
    for (int i=1; i<=m; i++) cout<<ans[i]<<endl;
}