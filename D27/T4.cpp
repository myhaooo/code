
#include<bits/stdc++.h>
using namespace std;
int n,q,l,r,k,a[120005],b[120005],c[120005],f[305];
void get_cir(){
    int lr=0,rr=0;
	for(int i=l;i<=r-k;i++)    b[++lr]=a[i];
	for(int i=r-k+1;i<=r;i++)    c[++rr]=a[i];
	for(int i=l;i<=l+rr-1;i++)    a[i]=c[i-l+1];
	for(int i=l+rr;i<=r;i++)    a[i]=b[i-l-rr+1];
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>q;
	while(q--){
		cin>>l>>r>>k;
		int mod=(r-l+1);
		k%=mod;
		get_cir();
		int fl=0;
		for(int i=1;i<=n;i++){
			f[i]=1;
		}
		for(int i=1;i<=n;i++){
			for(int j=i-1;j>=1;j--){
				if(a[j]<a[i]&&f[j]+1>f[i]){
					f[i]=f[j]+1;
				}
			}
			if(f[i]>=3){
				fl=1;
				goto ed1;
			}
		}
        ed1:
		if(fl==1)printf("YES\n");
		else printf("NO\n");
		
	}
	return 0;
}


