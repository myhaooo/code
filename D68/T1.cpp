#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans;
void dfs(int X)
{
	if(X==n+m-1)
	{
		int res=0,cx=0,cy=0;
		for(int i=1;i<=n+m-2;i++)
		{
			if(p[i]>n-1) res+=y[p[i]-n+1]*(cx+1),++cy;
			else res+=x[p[i]]*(cy+1),++cx;
		}
//		if(ans>res)
//		{
//			cout<<res<<"\n";
//			for(int i=1;i<=n+m-2;i++) cout<<p[i]<<" ";
//			cout<<"\n";
//		}
		ans=min(ans,res);
		return ;
	}
	for(int i=1;i<=n+m-2;i++)
	{
		if(vis[i]) continue;
		p[X]=i,vis[i]=1,dfs(X+1);vis[i]=0;
	}
}
signed main() {
	freopen("guiltiness.in","r",stdin);
	freopen("guiltiness.out","w",stdout);
    cin >> n >> m;
    if(n+m<=10)
	{
		ans=1e9;
		dfs(1);
		cout<<ans<<"\n";
		return 0;
	}
    vector<int> x(n - 1), y(m - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> x[i];
    }
    for (int i = 0; i < m - 1; ++i) {
        cin >> y[i];
    }
    int xnum = 0, ynum = 0;
    long long ans = 0;
    vector<pair<int, int>> vec;
    for (int i = 0; i < n - 1; ++i) {
        vec.push_back({x[i], 0});  
    }
    for (int i = 0; i < m - 1; ++i) {
        vec.push_back({y[i], 1});
    }
    sort(vec.rbegin(), vec.rend());
    for (auto& it : vec) {
        int cost = it.first;
        int type = it.second;
        if (type == 0) {
            ans += cost * (ynum + 1);
            ++xnum;
        } else {
            ans += cost * (xnum + 1);
            ++ynum;
        }
    }

    cout << ans << endl;
    return 0;
}

