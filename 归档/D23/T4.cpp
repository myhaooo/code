#include<bits/stdc++.h>
using namespace std;

int a[5005],n,m;

signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif

    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int uslewe=1,opt,l,r,x;uslewe<=m;uslewe++){
        cin>>opt;
        if(opt==1){
            cin>>l>>r>>x;
            for(int i=l;i<=r;i++){
                a[i]=x;
            }
        }
        else{
            cin>>l>>r;
            int tot=0,cpy[5005];
            for(int i=l;i<=r;i++){
                cpy[++tot]=a[i];
            }
            int ans=unique(cpy+1,cpy+1+tot)-cpy-1;
            cout<<ans<<'\n';
        }
    }

}