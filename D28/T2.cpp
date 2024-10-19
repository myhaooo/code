#include<bits/stdc++.h>
using namespace std;
const double eps=1e-10;
int w[2010],x[2010],v[2010];
map<double,int>d;
int main()
{
	int n,a,ans=0,sum,i,j;
	double l,r;
	cin>>n>>a;
	for(i=1;i<=n;i++){
		cin>>w[i]>>x[i]>>v[i];
	}
	for(i=1;i<=n;i++){
		d.clear();
		sum=w[i];
		for(j=1;j<=n;j++){
			if(i!=j){
				if(v[i]==v[j]){
					if(x[i]<=x[j]&&x[j]<=x[i]+a){
						sum+=w[j];
					}
				}
				else{
					l=1.0*(x[i]-x[j])/(v[j]-v[i]);
					r=1.0*(x[i]+a-x[j])/(v[j]-v[i]);	
					if(l-r>eps){
						swap(l,r);
					}
					if(r>=0){
						l=max(l,0.0);
						d[l]+=w[j];
						d[r+eps]-=w[j];
					}
				}
			}
		}
		ans=max(ans,sum);
		for(auto it=d.begin();it!=d.end();it++){
			sum+=it->second;
			ans=max(ans,sum);
		}
	}
	cout<<ans<<endl;
	return 0;
}