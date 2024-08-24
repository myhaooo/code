#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e3+5;
struct node{
    int x,y,v,w;
}edge[N*N];

int n,m=INT_MAX;
int a[N][N],b[N][N];
int num,temp[4],maxn[4]={-1,-1,-1,-1};
int dp[N*N];
int ans;
bool flag;
bool cmp(node a,node b){return a.v<b.v;}
signed main()
{
    ios::sync_with_stdio(false);
	#ifndef LOCAL
	cin.tie(0),cout.tie(0);
    #endif
    #ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>a[i][j];
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            cin>>b[i][j];
            if(a[i][j])edge[++num]=(node){i,j,a[i][j],b[i][j]};
        }
    sort(edge+1,edge+num+1,cmp);
    int lft=0;
    dp[1]=edge[1].w;

    for(int i=1;i<=num;i++)
    {
        if(edge[i].v!=edge[i-1].v &&  i!=1)
        {
            lft=i;
            break;
        }
        dp[i]=edge[i].w;
        maxn[0]=max(maxn[0],dp[i]+edge[i].x+edge[i].y);
        maxn[1]=max(maxn[1],dp[i]-edge[i].x+edge[i].y);
        maxn[2]=max(maxn[2],dp[i]+edge[i].x-edge[i].y);
        maxn[3]=max(maxn[3],dp[i]-edge[i].x-edge[i].y);
    }
    for(int i=lft;i<=num;i++)
    {
        if(edge[i].v!=edge[i-1].v)
            for(int j=0;j<4;j++)
            {
                temp[j]=maxn[j];
                maxn[j]=-1;
            }
        dp[i]=max({temp[0]-edge[i].x-edge[i].y,temp[1]+edge[i].x-edge[i].y,temp[2]-edge[i].x+edge[i].y,temp[3]+edge[i].x+edge[i].y})+edge[i].w;
        maxn[0]=max(maxn[0],dp[i]+edge[i].x+edge[i].y);
        maxn[1]=max(maxn[1],dp[i]-edge[i].x+edge[i].y);
        maxn[2]=max(maxn[2],dp[i]+edge[i].x-edge[i].y);
        maxn[3]=max(maxn[3],dp[i]-edge[i].x-edge[i].y);
    }
    for(int i=1;i<=num;i++)
        ans=max(ans,dp[i]);
    cout<<ans<<endl;
    return 0;
}/*



*/