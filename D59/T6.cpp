#include<cstdio>
#include<algorithm>
#define min(a,b) (a<b?a:b)
using namespace std;
const int N=505,inf=1e9;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int n,k,a[N];
double ans=inf,f[N][N];
struct node{
	int a,b;
}p[N];
inline bool cmp(node x,node y){
	return x.b<y.b;
}
int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		p[i].a=read(),p[i].b=read();
		if(p[i].b==-1)p[i].b=inf;
	}
	sort(p+1,p+n+1,cmp);
	for(int x=0;x<=k;x++){
		for(int i=1;i<=n;i++)a[i]=p[i].a;
		for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)f[i][j]=inf;
	    f[0][0]=0;
	    double res=inf;
	    for(int i=1;i<=n;i++){
	        for(int j=0;j<=min(x,i);j++){
	            f[i][j]=f[i-1][j]+1.0*p[i].a/(x+1);
	            if(j>=1&&p[i].b!=inf)f[i][j]=min(f[i][j],f[i-1][j-1]+1.0*p[i].b/j);
	        }
	    }
	    for(int i=k;i<=n;i++)res=min(res,f[i][x]);
	    for(int i=k;i>=x;i--){
	        sort(a+i+1,a+n+1);
	        double sum=0;
	        for(int j=i+1;j<=k;j++)sum+=a[j];
	        res=min(res,f[i][x]+sum/(x+1));
	    }
	    ans=min(ans,res);
	}
	printf("%.10lf",ans);
	return 0;
}
