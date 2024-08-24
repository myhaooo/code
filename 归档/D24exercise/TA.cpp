#include<bits/stdc++.h>
using namespace std;

const int N=50005;
struct query{
	int l,r,id,type;
	query(int l=0,int r=0,int id=0,int type=0):l(l),r(r),id(id),type(type){}
	//这里的l,r表示的并不是区间,只是为了方便才这么写的
	//id表示属于哪个询问,type表示其正负
}q[N<<2];
int a[N],be[N],ans[N];
int cntl[N],cntr[N];
int n,m,len,res,tot,l,r;
inline void movel(int t){
	if(t==1){
		++cntl[a[l+1]];
		res += cntr[a[l+1]];  //计算移动端点对答案的贡献。这里可以自己思考一下
		++l;
	}else{
		--cntl[a[l]];
		res -= cntr[a[l]];
		--l;
	}
}

inline void mover(int t){
	if(t==1){
		++cntr[a[r+1]];
		res += cntl[a[r+1]];
		++r;
	}else{
		--cntr[a[r]];
		res -= cntl[a[r]];
		--r;
	}
}

inline bool cmp(query x,query y){
	if(be[x.l]==be[y.l]) return x.r < y.r;
	return x.l < y.l;
}


signed main(){
	int l1,r1,l2,r2;
	cin>>n;
	len = sqrt(n);
	for(int i=1;i<=n;++i){
		cin>>a[i];
		be[i] = (i-1)/len+1;
	}
	cin>>m;
	for(int i=1;i<=m;++i){
		cin>>l1>>r1>>l2>>r2;
		q[++tot] = query(r1,r2,i,1); //强拆成4个询问
		q[++tot] = query(r1,l2-1,i,-1);
		q[++tot] = query(l1-1,r2,i,-1);
		q[++tot] = query(l1-1,l2-1,i,1);
	}
	for(int i=1;i<=tot;++i){
		if(q[i].l<=q[i].r) continue;
		swap(q[i].l,q[i].r);
	}
	sort(q+1,q+1+tot,cmp);
	l = 0,r = 0;
	for(int i=1;i<=tot;++i){
		while(l<q[i].l) movel(1);
		while(l>q[i].l) movel(-1);
		while(r<q[i].r) mover(1);
		while(r>q[i].r) mover(-1);

		if(q[i].type==1) ans[q[i].id] += res;
		else ans[q[i].id] -= res;
	}
	for(int i=1;i<=m;++i){
        cout<<ans[i]<<'\n';
	}
	return 0;
}

