#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
struct Edge{int to,next;}a[maxn<<1];
int n,q,dfn[maxn],low[maxn],bc[maxn],h[maxn],dfx,cnt;
void add(int x,int y) {
    a[++cnt]=(Edge){y,h[x]},h[x]=cnt;
    a[++cnt]=(Edge){x,h[y]},h[y]=cnt;
}

void Dfs(int x)
{
	bc[dfn[x]=++dfx]=x;
	for(int i=h[x];i;i=a[i].next)
		if(!dfn[a[i].to]) Dfs(a[i].to);
	low[x]=dfx;
}

struct Array_Tree{
	int c[maxn];
	void ins(int x,int d) {for(;x<=n;x+=x&-x) c[x]+=d;}
	int ask(int x) {int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
}A,B;
set<int> st[maxn];
void upd(int x,int d)//修改
{
	A.ins(dfn[x],d);
	A.ins(low[x]+1,-d);//第一种情况：祖先来的贡献
	B.ins(dfn[x],(low[x]-dfn[x]+1)*d);//第二种情况：子树的贡献（注意：因为直接把x子树的贡献加给x了，所以要乘子树大小）
}
int que(int x) {return (low[x]-dfn[x]+1)*A.ask(dfn[x])+B.ask(low[x])-B.ask(dfn[x]);}
signed main()
{
	int x,y;
	cin>>n>>q;
	for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        add(x,y);
    }
	Dfs(1);
    int opt;
	while(q--){
        cin>>opt;
		if(opt==1){
			cin>>x>>y;
			auto it=st[y].upper_bound(dfn[x]);
			if(it!=st[y].begin()&&low[bc[*prev(it)]]>=low[x]) continue;//ancestors
            
			while(it!=st[y].end()&&(*it)<=low[x]) upd(bc[*it],-1),st[y].erase(it++);
			st[y].insert(dfn[x]),upd(x,1);
		}
		else cin>>x,printf("%d\n",que(x));
    }
	return 0;
}