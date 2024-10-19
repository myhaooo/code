#include<bits/stdc++.h>
#define int long long
using namespace std; FILE *wsn;
auto read=[](){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
};
const int NN=2e6+5,inf=1e18;
const int lim=1e6;
int n,m,a[NN],b[NN],ans[NN],lst;
int sufa[NN],sufb[NN],prea[NN],preb[NN];
struct Query{
	int p,k,id;
	bool operator<(const Query&x)const{
		return p==x.p?k<x.k:p<x.p;
	}
}qu[NN];
namespace segment_tree{
	#define lid (id<<1)
	#define rid (id<<1|1)
	#define mid ((l+r)>>1)
	struct seg{
		int k,b;
		seg(){k=lim;b=inf;}
		seg(int k,int b):k(k),b(b){}
		int calc(int x){return k*x+b;}
	}tr[NN<<2];
	inline void update(seg x,int id=1,int l=-lim,int r=lim){
		if(tr[id].calc(mid)>x.calc(mid)) swap(tr[id],x);
		if(tr[id].calc(l)>x.calc(l))update(x,lid,l,mid);
		if(tr[id].calc(r)>x.calc(r))update(x,rid,mid+1,r);
	}
	inline int query(int pos,int id=1,int l=-lim,int r=lim){
		if(l>pos||r<pos) return inf;
		if(l==r) return tr[id].calc(pos);
		return min((mid<pos?query(pos,rid,mid+1,r):query(pos,lid,l,mid)),tr[id].calc(pos));
	}
}using namespace segment_tree;
namespace WSN{
	inline short main(){
		wsn=freopen("seq.in","r",stdin);
		wsn=freopen("seq.out","w",stdout);
		n=read(); m=read();
		for(int i=1;i<=n;i++)a[i]=read(),b[i]=read();
		for(int i=1;i<=n;i++)prea[i]=prea[i-1]+a[i],preb[i]=preb[i-1]+b[i];
		for(int i=n;i;i--)sufa[i]=sufa[i+1]+a[i],sufb[i]=sufb[i+1]+b[i];
		for(int o=1,p,k;o<=m;o++) p=read(),k=read(),qu[o]=Query{p,k,o};
		sort(qu+1,qu+m+1);
		lst=0;
		for(int i=1;i<=m;i++){
			Query x=qu[i];
			for(int j=lst;j<x.p;j++)
				update(seg{-preb[j],prea[j]});
			ans[x.id]=prea[x.p]-x.k*preb[x.p]-query(x.k);
			lst=x.p;
		}
		memset(tr,0,sizeof(tr));
		lst=n+1;
		for(int i=m;i;i--){
			Query x=qu[i];
			for(int j=lst;j>=x.p+1;j--)
				update(seg{-sufb[j],sufa[j]});
			ans[x.id]+=sufa[x.p+1]-x.k*sufb[x.p+1]-query(x.k);
			lst=x.p+1;
		}
		for(int i=1;i<=m;i++)printf("%lld\n",ans[i]);
		return 0;
	}
}
signed main(){return WSN::main();}
