#include<bits/stdc++.h>
using namespace std;
const int maxn = 1005;
#define int long long
bool be;
int tot, m, K, cnt, n, ans, nmax, Count[maxn];
int last, most, S, x[maxn], y[maxn], z[maxn];
bool ed;
#define LEN 16
signed main(){
	ios::sync_with_stdio(false);
	#ifndef LOCAL
		#define NDEBUG
		cin.tie(0),cout.tie(0);
	#else
		#ifdef LEN
		fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
		#endif
		freopen("in.in","r",stdin);
		freopen("out.out","w",stdout);
		//#include "../local.h"
	#endif
	
	cin>>m>>K;
	for (int i = 1; i<=m; i++) cin>>Count[i], n += Count[i];  
	for (int i = 1; i<=m; i++) cin>>x[i];
	for (int i = 1; i<=m; i++) cin>>y[i];
	for (int i = 1; i<=m; i++) cin>>z[i];

	S = (1 << K) - 1;
	for (int i = 1; i<=m; i++)
	{
		last = x[i];
		if(!tot || most == last) tot++, most = last;
		else --tot;
		for (int j = 1; j < Count[i]; j++)
		{
			last = (last * y[i] + z[i]) & S;
			if(!tot || most == last) tot++, most = last;
			else --tot;
		}
	}
	for (int i = 1; i <= m; i++)
	{
		last = x[i];
		if(last == most) cnt++;
		for (int j = 1; j < Count[i]; j++)
		{
			last = (last * y[i] + z[i]) & S;
			if(most == last) cnt++;
		}
	}
	nmax = n / 2;
	if(n & 1)  nmax++;
	if(cnt > nmax)
	   cout<<((cnt<<1) - n - 1);
	else cout<<"0";
}