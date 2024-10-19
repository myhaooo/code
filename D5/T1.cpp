
#include<bits/stdc++.h>
using namespace std;
int a[(int)2e5+5],T,n;

int main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    cin.tie(0),cout.tie(0);
    #else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #include "../local.h"
    #endif
    cin>>T;
    while(T--){
        memset(a,0,sizeof(a));
        cin>>n;
	    if(n==1){
            cout<<"1\n";
            continue;
        }
	    if(n==2) {
            cout<<"1 2\n";
            continue;
        }
	    int cnt=1;
    	for(int l=1,r=n;l<r;l++,r--) a[l]=++cnt,a[r]=++cnt;
    	a[n/2+1]=1;
    	for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    	cout<<'\n';
    }
    return 0;
}