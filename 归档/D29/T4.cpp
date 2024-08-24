#include<bits/stdc++.h>
using namespace std;

struct rec{int x,y;double u,v,s;}e[201];
int n,m,cnt;
int fa[510],sum;
double ans,θ[40001];
bool cmp(rec a,rec b){return a.s>b.s;}
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

int main()
{
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
        #define file(a) FILE *FI = freopen(#a".in","r",stdin); FI = freopen(#a".out","w",stdout)
        file(mst);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n"
        , abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        //#include "../local.h"
    #endif

    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>e[i].x>>e[i].y>>e[i].u>>e[i].v;
    for(int i=1;i<=n;i++){
        fa
    }
    for(double deg=0.0;deg<=M_PI*2.0;deg+=0.06){
		for(int i=1;i<=n;i++)fa[i]=i;
		sum=0;
		for(int i=1;i<=m;i++)e[i].s=(double)e[i].x*cos(deg)+(double)e[i].y*sin(deg);
		sort(e+1,e+1+m,cmp);
		int Y=0,X=0;
		for(int i=1;i<=m;i++){
			int u=e[i].u,v=e[i].v;
			int fu=find(u),fv=find(v);
			if(fu==fv)continue;
			fa[fu]=fv;
			Y+=e[i].y;
			X+=e[i].x;
			++sum;
			if(sum==n-1)break;
		}
		ans=max(ans,(double)sqrt((double)X*(double)X+(double)Y*(double)Y));
	}
    cout<<ans<<endl;
}