#include<bits/stdc++.h>
using namespace std;
int n,q,ans;
vector<int> a; 
signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
        #define 下面是代码 上面是模版------------------
    #endif
    #define clear(a) memset(a, 0, sizeof(a))
    cin>>n;
    for(int i=1,ls;i<=n;i++){
        cin>>ls;
        a.push_back(ls);
    }
    // for(auto i=a.begin();i!=a.end();++i){
    //     cout<<*i<<" ";
    // }
    cin>>q;
    while(q--){
        int opt,l,r,k;
        cin>>opt>>l>>r;
        l=(l+ans-1)%n+1;
        r=(r+ans-1)%n+1;
        if(l>r)swap(l,r);
        if(opt==1){
            int num=*(a.begin()-1+r);
            //cout<<"num"<<num<<"\n";
            a.erase(a.begin()+r-1);
            a.insert(a.begin()+l-1,num);
            
            //for(auto i=a.begin();i!=a.end();++i){
            //    cout<<*i<<" ";
            //}
        }
        else{
            cin>>k;
            k=(k+ans-1)%n+1;
            ans=0;
            #ifndef NDEBUG
            for(auto i=a.begin();i!=a.end();++i){
               cout<<*i<<" ";
            }
            cout<<endl;
            cout<<"begin end: "<<l<<" "<<r<<" "<<*(a.begin()+l-1)<<" "<<*(a.begin()+r-1)<<endl;
            cout<<"k= "<<k<<endl;
            #endif
            for(auto it=a.begin()+l-1;it!=a.begin()+r;++it){
                if(*it==k){
                    ans++;
                }
            }
            cout<<ans<<endl;
        }
    }
}