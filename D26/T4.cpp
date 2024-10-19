#include<bits/stdc++.h>
#define lid(x) (x<<1)
#define rid(x) (x<<1|1)
using namespace std;
const int N=50005;
typedef long long ll;
ll n,m,p,c;
ll w[N];
struct seg_tree {
    ll sum, l, r;
}
t[N<<2];
ll read() {
    ll ans = 0 , f = 1;
    char i=getchar();
    while(i<'0'||i>'9') {
        if(i=='-')f=-1;
        i=getchar();
    }
    while(i>='0'&&i<='9') {
        ans=ans*10+i-'0';
        i=getchar();
    }
    return ans * f;
}

void up(ll root) {
    t[root].sum = t[lid(root)].sum + t[rid(root)].sum;
}

void build(ll root, ll l, ll r) {
    int mid = l + r >> 1;
    t[root].l = l, t[root].r = r;

    if (l == r) {
        t[root].sum = w[l];
        return;
    }

    build(lid(root), l, mid);
    build(rid(root), mid + 1, r);
    up(root);
}


ll query_sum(ll root,ll l,ll r) {
    //查找sum
    if(l<=t[root].l && t[root].r<=r) return t[root].sum;
    if(r<t[root].l || t[root].r<l) return 0;
    return query_sum(lid(root),l,r)+query_sum(rid(root),l,r);
}
ll qpow(ll x,ll b,ll mod)
{
	ll res = 1;
	while(b)
	{
		if(b&1) res=res*x;
		x=x*x,b>>=1;
	}
	return res;
}


int main() {
    n = read(),m=read(),p=read(),c=read();
    if(n==0) return 0;
    for (ll i=1;i<=n;i++) w[i] = read();
    build(1,1,n);
    if(n>100){
        while(m--){
            int opt,l,r;
            cin>>opt>>l>>r;
            cout<<query_sum(1,l,r)%p<<"\n";
        }
    }
    else{
        while(m--){
            int opt,l,r;
            cin>>opt>>l>>r;
            if(opt==0){
                for(int i=l;i<=r;i++){
                    w[i]=qpow(c,w[i],p);
                }
            }
            else{
                int ans=0;
                for(int i=l;i<=r;i++){
                    ans+=w[i];
                    ans%=p;
                }
                cout<<ans<<"\n";
            }
        }
    }

}
