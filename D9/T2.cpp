#include<bits/stdc++.h>
using namespace std;
const int N=405, INF=0x3f3f3f3f;
string s;
int f[N][N][N][3];//已填x个r,y个g，z个b，最后一位是k
int G[N][N], num[3];
signed main()
{
    cout<<sizeof f;
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    cin.tie(0),cout.tie(0);
    #define clear(a) memset(a, 0, sizeof(a))
    #else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #include "../local.h"
    #endif
    int n;
    cin>>n>>s;

    for(int i=1,t;i<=n;++i)
    {
        if(s[i-1]=='R')t=0;
        else if(s[i-1]=='G')t=1;
        else t=2;
        G[t][num[t]++]=i;
    }
    int numa=num[0], numb=num[1], numc=num[2];
    memset(f, 0x3f, sizeof f);
    f[0][0][0][0]=f[0][0][0][1]=f[0][0][0][2]=0;
    for(int tot=0;tot<n;++tot){
        for(int x=0;x<=tot&&x<=numa;++x){
            for(int y=0;y<=numb&&x+y<=tot;++y){
                int z=tot-x-y;
                if(0<=z && z<=tot && z<=numc){
                    for(int k=0;k<3;++k){
                        if(f[x][y][z][k]==INF)continue;
                        if(k!=0)f[x+1][y][z][0]=min(f[x+1][y][z][0], f[x][y][z][k]+abs(x+y+z+1-G[0][x]));
                        if(k!=1)f[x][y+1][z][1]=min(f[x][y+1][z][1], f[x][y][z][k]+abs(x+y+z+1-G[1][y]));
                        if(k!=2)f[x][y][z+1][2]=min(f[x][y][z+1][2], f[x][y][z][k]+abs(x+y+z+1-G[2][z]));
                    }
                }
            }
        }
    }
    int ans=min({f[numa][numb][numc][0],f[numa][numb][numc][1],f[numa][numb][numc][2]});
    cout<<(ans==INF?-1:ans/2);
    return 0;
}