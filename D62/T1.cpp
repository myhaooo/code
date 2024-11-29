// ubsan: undefined
// accoders
#include<bits/stdc++.h>
using namespace std;
short n,m;
short sx,sy,tx,ty;
bool mp[105][105];
double s,ans;
short f[105][105][5005];
struct sta{short x,y,k,r;};
queue<sta> q;
signed main(){
    freopen("msg.in", "r", stdin);
    freopen("msg.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ans=1e18;
    cin>>n>>m>>sx>>sy>>tx>>ty;
    for(int xx=1;xx<=n;xx++)
        for(int yy=1;yy<=m;yy++)
            for(int i=0;i<=((n+1)>>1)*n;i++)
                f[xx][yy][i]=10000;
    for(int i=1,inp;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>inp;
            mp[i][j]=inp;
        }
    }
    cin>>s;
    q.push({sx,sy,0,0});f[sx][sy][0]=0;
    while(!q.empty()){
        sta x=q.front();q.pop();
        if(x.x-1>0&&!(mp[x.x-1][x.y]==1)){
            sta y=x;
            y.x--;y.k++;
            if(f[y.x][y.y][y.k]>y.r)
                f[y.x][y.y][y.k]=y.r,
                q.push(y);
        }
        if(x.x+1<=n&&!(mp[x.x+1][x.y]==1)){
            sta y=x;
            y.x++;y.k++;
            if(f[y.x][y.y][y.k]>y.r)
                f[y.x][y.y][y.k]=y.r,
                q.push(y);
        }
        if(x.y-1>0&&!(mp[x.x][x.y-1]==1)){
            sta y=x;
            y.y--;y.r++;
            if(f[y.x][y.y][y.k]>y.r)
                f[y.x][y.y][y.k]=y.r,
                q.push(y);
        }
        if(x.y+1<=m&&!(mp[x.x][x.y+1]==1)){
            sta y=x;
            y.y++;y.r++;
            if(f[y.x][y.y][y.k]>y.r)
                f[y.x][y.y][y.k]=y.r,
                q.push(y);
        }
    }
    for(int k=1;k<=((n+1)>>1)*n;k++){
        if(f[tx][ty][k]==10000)continue;
        double tr=1.0*(s-f[tx][ty][k])/k;
        bool flg=0;
        for(int kv=1;kv<=((n+1)>>1)*n;kv++){
            if(kv==k)continue;
            double vl=tr*kv+f[tx][ty][kv];
            if(vl<s){flg=1;break;}
        }
        if(!flg){
            ans=min(ans,tr);
        }
    }
    cout<<fixed<<setprecision(3)<<ans<<'\n';
    return 0;
}
