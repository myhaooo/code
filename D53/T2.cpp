#include <bits/stdc++.h>
using namespace std;
struct PointHash {
    long long operator() (const pair<int, int>& p) const {
        return hash<long long>()(((long long)p.first << 32) | (unsigned int)p.second);
    }
};
#define ll long long
const int MAXN=2e5+5;
bool vis[MAXN];
int n,x,y;
int mpx[MAXN],mpy[MAXN],tot1,tot2;
pair<int,int> points[MAXN];
bitset <50005> bs[50005];
void s1(){
	for(int i=1;i<=x;i++)bs[i].reset();
	for(int i=1;i<=n;i++){
		bs[points[i].first][points[i].second]=1;
	}
	for(int i=1;i<=x;i++){
		if(bs[i].count()<=1)vis[i]=1;
	}
	ll ans=0;
	for(int i=1;i<=x;i++){
		if(vis[i])continue;
		for(int j=1;j<i;j++){
			if(vis[j])continue;
			ll val=(bs[i]&bs[j]).count();
			ans+=val*(val-1)/2;
		}
	}
	cout<<ans<<endl;
}
void s2(){
	cin >> n;
    unordered_set<pair<int, int>, PointHash> pointSet;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
        pointSet.insert({x, y});
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x1 = points[i].first, y1 = points[i].second;
            int x2 = points[j].first, y2 = points[j].second;
            if (x1 != x2 && y1 != y2) {
                if (pointSet.count({x1, y2}) && pointSet.count({x2, y1})) {
                    ans++;
                }
            }
        }
    }
    cout << ans / 2 << endl;
    exit(0);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(0);
	#ifndef LOCAL
	freopen("rect.in","r",stdin);
	freopen("rect.out","w",stdout); 
	#endif
	cin>>n;
	if(n<2000){
		s2();exit(0);
	}
	x=1,y=1;
	for(int i=1;i<=n;i++){
		int x, y;
        cin >> x >> y;
        points[i] = {x, y};
		if(!mpx[points[i].first])mpx[points[i].first]=++tot1;
		if(!mpy[points[i].second])mpy[points[i].second]=++tot2;
		points[i].first=mpx[points[i].first];
		points[i].second=mpy[points[i].second];
		
	}
	for(int i=1;i<=n;i++){
		x=max(x,points[i].first);y=max(y,points[i].second);
	}
	s1();
    

	
}

