#include<bits/stdc++.h>
using namespace std;
const int N=5e4+10,Mod=998244353,INF=INT_MAX>>1;

int n,arr[N],res[N];



namespace ST{
	int g[N][20];

	void Init(){
		for(int i=1;i<=n;i++){
			g[i][0]=arr[i];
		}
		for(int j=1;j<20;++j){
			for(int i=1;i+(1<<j)-1<=n;i++){
				g[i][j]=__gcd(g[i][j-1],g[i+(1<<(j-1))][j-1]);
			}
		}
	}

	int Query(int l,int r){
		int k=__lg((r-l)+1);
		return __gcd(g[l][k],g[r-(1<<k)+1][k]);
	}
};

int L(int p,int d){
	int l=0,r=p;
	while((r-l)>1){
		int mid=l+((r-l)>>1);
		ST::Query(mid,p)>=d?r=mid:l=mid;
	}
	return r;
}

int R(int p,int d){
	int l=p,r=n+1;
	while((r-l)>1){
		int mid=l+((r-l)>>1);
		ST::Query(p,mid)>=d?l=mid:r=mid;
	}
	return l;
}

struct Seg{
	int p,l,r,w;
	friend bool operator<(const Seg& a,const Seg& b){
		return a.w<b.w;
	}
};
vector<Seg> vecl,vecr;

struct Data{
	struct Ver{
		int sum,laz;
	} V[N<<2];

	void Pushup(int p){
		V[p].sum=(V[p<<1].sum+V[p<<1|1].sum)%Mod;
	}

	void Laz(int p,int l,int r,int d){
		V[p].laz=(V[p].laz+d)%Mod;
		V[p].sum=(V[p].sum+1LL*d*((r-l)+1))%Mod;
	}

	void Pushdown(int p,int l,int r){
		int mid=l+((r-l)>>1);
		if(V[p].laz){
			Laz(p<<1,l,mid,V[p].laz);
			Laz(p<<1|1,mid+1,r,V[p].laz);
			V[p].laz=0;
		}
	}

	void Modify(int p,int l,int r,int x,int y,int d){
		if(x<=l&&r<=y){
			return Laz(p,l,r,d),void();
		}
		Pushdown(p,l,r);
		int mid=l+((r-l)>>1);
		if(x<=mid){
			Modify(p<<1,l,mid,x,y,d);
		}
		if(y>mid){
			Modify(p<<1|1,mid+1,r,x,y,d);
		}
		Pushup(p);
	}

	int Query(int p,int l,int r,int x,int y){
		if(x<=l&&r<=y){
			return V[p].sum;
		}
		Pushdown(p,l,r);
		int mid=l+((r-l)>>1),res1=0,res2=0;
		if(x<=mid){
			res1=Query(p<<1,l,mid,x,y);
		}
		if(y>mid){
			res2=Query(p<<1|1,mid+1,r,x,y);
		}
		return(res1+res2)%Mod;
	}
} F,G;

set<int> Set;
vector<int> uni;

void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
	}
	ST::Init();
	for(int i=1;i<=n;i++){
		for(int r=i,l;r>=1;r=l-1){
			l=L(i,ST::Query(r,i));
			vecl.push_back(Seg{i,l,r,ST::Query(r,i)});
			Set.insert(ST::Query(r,i));
		}
	}
	for(int i=n;i>=1;i--){
		for(int l=i,r;l<=n;l=r+1){
			r=R(i,ST::Query(i,l));
			vecr.push_back(Seg{i,l,r,ST::Query(i,l)});
		}
	}
	sort(vecl.begin(),vecl.end(),[](const Seg& a,const Seg& b){
		if(a.w != b.w) return a.w<b.w;
		return a.p<b.p;
	});
	sort(vecr.begin(),vecr.end(),[](const Seg& a,const Seg& b){
		if(a.w != b.w) return a.w<b.w;
		return a.p<b.p;
	});
	F.Modify(1,0,n+1,0,n+1,1),G.Modify(1,0,n+1,0,n+1,1);
	for(auto it:Set){
		uni.clear();
		int ll=lower_bound(vecl.begin(),vecl.end(),Seg{0,0,0,it})-vecl.begin(),lr=upper_bound(vecl.begin(),vecl.end(),Seg{0,0,0,it})-vecl.begin()-1;
		int rl=lower_bound(vecr.begin(),vecr.end(),Seg{0,0,0,it})-vecr.begin(),rr=upper_bound(vecr.begin(),vecr.end(),Seg{0,0,0,it})-vecr.begin()-1;
		for(int i=ll;i<=lr;i++){
			F.Modify(1,0,n+1,vecl[i].p,n,F.Query(1,0,n+1,vecl[i].l-1,vecl[i].r-1));
			uni.push_back(vecl[i].p);
		}
		for(int i=rr;i>=rl;i--){
			G.Modify(1,0,n+1,1,vecr[i].p,G.Query(1,0,n+1,vecr[i].l+1,vecr[i].r+1));
			uni.push_back(vecr[i].p);
		}

		int all=F.Query(1,0,n+1,n,n);
		uni.push_back(1);
		uni.push_back(n);
		sort(uni.begin(),uni.end());
		uni.erase(unique(uni.begin(),uni.end()),uni.end());
		for(int i=0;i+1<uni.size();i++){
			int que=(0LL+all-1LL*F.Query(1,0,n+1,uni[i],uni[i])*G.Query(1,0,n+1,uni[i+1],uni[i+1])%Mod+Mod)%Mod;
			res[uni[i]+1]=(0LL+res[uni[i]+1]+que)%Mod;
			res[uni[i+1]]=(0LL+res[uni[i+1]]-que+Mod)%Mod;
		}
		for(int i=0;i<uni.size();i++){
			int que=(0LL+all-1LL*F.Query(1,0,n+1,uni[i]-1,uni[i]-1)*G.Query(1,0,n+1,uni[i]+1,uni[i]+1)%Mod+Mod)%Mod;
			res[uni[i]]=(0LL+res[uni[i]]+que)%Mod;
			res[uni[i]+1]=(0LL+res[uni[i]+1]-que+Mod)%Mod;
		}
		for(int i=lr;i>=ll;i--){
			F.Modify(1,0,n+1,vecl[i].p,n,-F.Query(1,0,n+1,vecl[i].l-1,vecl[i].r-1));
		}
		for(int i=rl;i<=rr;i++){
			G.Modify(1,0,n+1,1,vecr[i].p,-G.Query(1,0,n+1,vecr[i].l+1,vecr[i].r+1));
		}
	}
	for(int i=1;i<=n;i++){
		res[i]=(res[i]+res[i-1])%Mod,cout<<(res[i]+Mod)%Mod<<" ";
	}
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	Solve();
	return 0;
}
