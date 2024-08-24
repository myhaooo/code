//make.cpp
#include<bits/stdc++.h>
using namespace std;
const int n=1e5;
int a[n+10];
signed main(){
    freopen("in.in","w",stdout);
    cout<<n<<"\n";
    for(int i=1;i<=n;i++){
        a[i]=i;
    }
    mt19937 myrand(time(0));
    random_shuffle(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";

    random_shuffle(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";

}