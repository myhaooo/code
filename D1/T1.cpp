#include <iostream>
#include <deque>
#include<climits>
#include <vector>
struct node{
    int maxn=INT_MIN;
    int id=1;
}m;
struct node2{
    int minn=INT_MAX;
    int id=1;
}k;
int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+(c^48);
        c=getchar();
    }
    return x*f;
}
const int N=2e5+10;
int a[N];
short b[N];
bool ans[N];
using namespace std;
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    #ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
    int n=read();
    for (int i = 1; i <= n; ++i) {
        a[i]=read();
    }
    b[1]=1;
    for(int i=2;i<=n;i++){
        if(a[i]>a[i-1]){
            b[i]=1;
        }
        else if (a[i]<a[i-1])
        {
            b[i]=-1;
        }
        if(b[i-1]==-1&&a[i]==a[i-1]){
            b[i]=1;
        }
    }
    #ifdef LOCAL
    for(int i=1;i<=n;i++){
        cout<<b[i]<<" ";
    }
    cout<<endl;
    #endif
    m.id=1;
    m.maxn=a[1];
    for(int i=1;i<=n;i++){
        if(b[i]==1){//买
            if(m.maxn<a[i]){
                m.maxn=a[i];m.id=i;
            }
        }
        if(b[i]==-1){//卖
            if(k.minn>a[i]){
                k.minn=a[i], k.id=i;
            }
        }
        if(b[i]==-1&&b[i+1]!=-1){//决策点
            ans[m.id]=1,ans[k.id]=1,m.id=-1,k.id=-1,m.maxn=INT_MIN,k.minn=INT_MAX;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }

}