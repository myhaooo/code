#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,l,r,sum;
signed main(){
    cin>>n>>x;
    y=x;
    while(n--){
        cin>>l>>r;
        if(x<=r&&l<=y){
            if(l > x)x=l;
            if(r < y)y=r;	
        }
    //	cout<<x<<" "<<y<<endl;
        if(r < x){
            sum+=x-r;
            y=x,x=r;
        }
        if(l > y){
            sum+=l-y;
            x=y,y=l;
        }
    //	cout<<x<<" "<<y<<" "<<sum<<endl;
    }
    cout<<sum<<endl;
    return 0;
}