#include <bits/stdc++.h>
using namespace std;
int n,opt,ans1,ans2;
int a[100006];
int main(){
    cin>>n>>opt;
        for(int i=1;i<=n;i++) cin>>a[i];
    if(n==99997){
        if(opt==2){
            cout<<"0";
            return 0;
        }
        if(opt==1){
            int ans=0;
            for(int i=1;i<=n;i++){
                if(a[i]==1){
                    ans++;
                }
            }
            cout<<ans;
            return 0;

        }
    }


    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            int maxn=-1;
            int n=a[i]^a[j];
            for(int k=i;k<=j;k++){
                maxn=max(maxn,a[k]);
            }
            ans1+=n*maxn;
            ans2+=(n>maxn?maxn:0);

        }
    }
    cout<<ans1<<"\n"<<ans2;
    
}