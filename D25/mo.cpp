#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1000000;
struct node
{
    int pos,val;
}a[N+5];
bool cmp(node r,node s){return r.val==s.val?r.pos<s.pos:r.val<s.val;}
int n;
int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x*10%n+(ch-'0')%n)%n,ch=getchar();
    return f*x;
}
int main()
{
    //ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        //#include "../local.h"
    #endif

    scanf("%d",&n);
    for(int i=1;i<=n;i++)a[i].val=(a[i-1].val+read())%n,a[i].pos=i;
    sort(a+1,a+1+n,cmp);
    for(int i=2;i<=n;i++)
    if(a[i].val==a[i-1].val)
    {
        printf("%d\n",a[i].pos-a[i-1].pos);
        for(int j=a[i-1].pos+1;j<=a[i].pos;j++)printf("%d ",j);
        return 0;
    }
    return 0;
}
