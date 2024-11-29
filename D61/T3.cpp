#include<bits/stdc++.h>
using namespace std;
#define ll int
#define ull unsigned long long
const int N=100007,op[3][3]={{0,1,1},{1,1,2},{1,2,1}};
const ull B=13331;
ll T,n,a[N],k,p,lst0;
char s[N];
ull ans;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>(s+1);n=strlen(s+1);k=a[1]=s[1]-'0';ans=0;
		for (int i=2;i<=n;++i){a[i]=s[i]-'0';k=op[k][a[i]];}
		if (k<2){
			cout<<k<<' ';
			for (int i=1;i<n;++i) ans=ans*B+1;
			cout<<ans<<'\n';
			continue;
		}
		lst0=0;
		for (int i=n;i;--i) if (!a[i]){lst0=i;break;}
		if (!lst0){
			cout<<k<<' ';
			for (int i=1;i<n;++i) ans=ans*B+1;
			cout<<ans<<'\n';
			continue;
		}
		bool fl=0;
		for (int i=1;i<lst0;++i) fl|=(bool)a[i];
		if (!fl){
			cout<<"1 ";
			k=a[lst0+1];p=lst0+1;
			for (int i=1;i<lst0;++i) ans=ans*B+1;
			while(k==a[lst0+1]){
				ans=ans*B+2;k=op[k][a[++p]];
			}
			for (int i=0;i<=n-p;++i) ans=ans*B+1;
			cout<<ans<<'\n';
			continue;
		}
		k=a[1];
		for (int i=2;i<lst0;++i){ans=ans*B+1;k=op[k][a[i]];}
		ll tmp=a[lst0+1],p=lst0+1;
		while(k==tmp&&p<=n){tmp=op[tmp][a[++p]];ans=ans*B+3;}
		if (p<=n){
			ans=ans*B+2;
			for (int i=0;i<=n-p;++i) ans=ans*B+1;
			cout<<"1 "<<ans<<'\n';continue;
		}
		ans=0;
		tmp=a[lst0-1];p=lst0-1;
		while(tmp!=1&&p) tmp=op[tmp][a[--p]];
		if (!p){
			cout<<"2 ";
			for (int i=1;i<n;++i) ans=ans*B+1;
			cout<<ans<<'\n';
			continue;
		}
		cout<<"1 ";
		k=a[1];
		for (int i=2;i<p;++i){k=op[k][a[i]];ans=ans*B+1;}
		if (a[p]==0){
			if (k==1){
				for (int i=2;i<lst0-p;++i) ans=ans*B+3;
				ans=((ans*B+2)*B+1)*B+2;
				for (int i=1;i<=n-lst0;++i) ans=ans*B+1;
				cout<<ans<<'\n';
			}
			else if (k==2){
				if (lst0==p+2){
					ans=(ans*B+2)*B+2;
					for (int i=1;i<n-p;++i) ans=ans*B+1;
					cout<<ans<<'\n';
				}
				else{
					ans=ans*B+2;
					for (int i=1;i<lst0-p;++i) ans=ans*B+1;
					ans=ans*B+2;
					for (int i=1;i<=n-lst0;++i) ans=ans*B+1;
					cout<<ans<<'\n';
				}
			}
			else{
				if (p>1) ans=ans*B+1;
				if (lst0==p+2){
					ans=(ans*B+1)*B+2;
					for (int i=1;i<=n-lst0;++i) ans=ans*B+1;
					cout<<ans<<'\n';
				}
				else{
					for (int i=2;i<lst0-p;++i) ans=ans*B+2;
					ans=(ans*B+1)*B+2;
					for (int i=1;i<=n-lst0;++i) ans=ans*B+1;
					cout<<ans<<'\n';
				}
			}
		}
		else{
			if (k==2){
				for (int i=1;i<=lst0-p;++i) ans=ans*B+2;
				for (int i=0;i<=n-lst0;++i) ans=ans*B+1;
				cout<<ans<<'\n';
			}
			else{
				for (int i=1;i<lst0-p;++i) ans=ans*B+2;
				ans=(ans*B+1)*B+2;
				for (int i=1;i<=n-lst0;++i) ans=ans*B+1;
				cout<<ans<<'\n';
			}
		}
	}
	return 0;
}
