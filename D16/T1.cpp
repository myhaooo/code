#include<cstdio>
#include<cstring>
#define mod 1000000009ll
using namespace std;
int n,can[1000005];
long long hsh[2000005],bc[2000005]= {1};
char a[2000005];
long long Hash(int l,int r) {
	if(l>r)return Hash(2*n+1-l,2*n+1-r);
	return (hsh[r]-hsh[l-1]*bc[r-l+1]%mod+mod)%mod;
}
int main() {
	int T;
	scanf("%d",&T);
	for(int i=1; i<=2000000; i++)bc[i]=bc[i-1]*29%mod;
	while(T--) {
		scanf("%s",a+1);
		n=strlen(a+1);
		for(int i=1;i<=n;i++)a[2*n+1-i]=a[i];
        // for(int i=1;i<=2*n;i++){
        //     putchar(a[i]);
        // }
        putchar(10);
		for(int j=1; j<=2*n; j++)hsh[j]=(hsh[j-1]*29+a[j]-'a'+1)%mod;
		memset(can,0,(sizeof(int)*(n+5)));
		can[n]=1;
		for(int i=n-1;i>=1;i--){
			if(i*2-1>=n){
				if(Hash(i,n)==Hash(i,2*i-n))can[i]=1;
			}
			else {
				if(can[2*i-1]&&Hash(i,2*i-1)==Hash(i,1))can[i]=1;
			}
		}
		for(int i=1;i<=n;i++)if(can[i])printf("%d ",i);
		putchar(10);
	}
	return 0;
}