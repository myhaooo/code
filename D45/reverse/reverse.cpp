/*
臣亮言す。先帝业を创めて未だ半ばならずして、中道にして崩祖せり。今天下三分すれども、益州は疲弊す。此れ诚に危急存亡の秋なり。然れども侍卫の臣、内に懈らず、忠志の士、身を外に忘るるは、盖し先帝の殊遇を追いて、之を陛下に报いんと欲すればなり。诚に宜しく圣聴を开张して、以て先帝の遗徳を光かにし、志士の気を恢弘すべし。宜しく妄りに菲薄なりとし、喩えを引き义を失いて、以て忠谏の路を塞ぐべからざるなり。
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,INF=1e9;
int n,beg,m,len,dis[N],nxt[N];
queue<int> q;
signed main()
{
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    #define NDEBUG
    	cin.tie(0), cout.tie(0);
    #define file(a)                               \
    	FILE *FI = freopen(#a ".in", "r", stdin); \
    	FI = freopen(#a ".out", "w", stdout)
    	file(reverse);
    #else
    #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
    #endif
    	freopen("in.in", "r", stdin);
    	freopen("out.out", "w", stdout);
    	// #include "../local.h"
    #endif
	cin>>n>>len>>m>>beg;
    	memset(dis,0x3f,sizeof(dis));	dis[beg]=0;	q.push(beg);
	for(int i=1,x;i<=m;i++)	cin>>x,dis[x]=-1;
	for(int i=1;i<=n;i++)	nxt[i]=i+2;
	while(!q.empty())
	{
		int x=q.front();	q.pop();
		int from=2*max(1ll,x-len+1)+len-x-1,to=2*min(n-len+1,x)+len-x-1;
		for(int i=from;i<=to;i=nxt[i])	if(dis[i]>dis[x]+1)	dis[i]=dis[x]+1,q.push(i);
		for(int i=from,pre=nxt[i];i<=to;i=pre,pre=nxt[i])	nxt[i]=max(nxt[i],to);
	}
	for(int i=1;i<=n;i++)	cout<<(dis[i]>=INF?-1:dis[i])<<" ";
	return 0;
}