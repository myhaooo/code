#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
const int mod=1e5+3;
const int INF=LLONG_MAX;
map<int,int> qp;
int a[MAXN],maxn,minn;
int ans=1,h[MAXN],tot=1,n;

set<int> s;
signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
    	//fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif

	cin>>n;
	int lat=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==lat)
		{
			cnt++;
		}
		else
		{
			lat=a[i];
			cnt=1;
		}
		ans=max(ans,cnt);
	}
    for(unsigned int i=1000;i>=2;i--){
		for(unsigned int j=i;j<=INF;j*=i)
		{
			if(j==0)
				break;
			qp[j]=i;
		}
	}
	memset(h,-1,sizeof(h));
	for(int l=1;l<n;l++)
	{
		s.clear();
		s.insert(a[l]);
		maxn=max(a[l],a[l+1]);
		minn=min(a[l],a[l+1]);
		if(minn==maxn || maxn%minn)
			continue;
		s.insert(a[l+1]);
		int gys=qp[maxn/minn];
        cout<<gys<<" ";
		ans=max(ans,2ll);
		for(int r=l+2;r<=n;r++){
			if(s.find(a[r])!=s.end())
				break;
			s.insert(a[r]);
			maxn=max(a[r],a[r-1]);
			minn=min(a[r],a[r-1]);
			if(maxn%minn!=0)	
				break;
			if(qp[maxn/minn]!=gys)
				break;
			ans=max(ans,r-l+1);
		}
	}
    cout<<'\n';
	cout<<ans<<'\n';
	return 0;
}