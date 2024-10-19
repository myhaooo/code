#include <bits/stdc++.h>
using namespace std;
#include "1.h"

const int maxn=1005;
struct node{double x,y;int id;}a[maxn],tmp[maxn];
double f[maxn][maxn][2];
bool pre[maxn][maxn][2];

double dis(int i,int j){return sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));}

void print(int l,int r,int op)
{
    if(l==r) return cout<<a[l].id<<' ',void();
    if(op) cout<<a[r].id<<' ',print(l,r-1,pre[l][r][op]);
    else cout<<a[l].id<<' ',print(l+1,r,pre[l][r][op]);
}

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i].x>>a[i].y,a[i].id=i,tmp[i]=a[i];
    int k=1;
    for(int i=2;i<=n;i++) if(a[i].y>a[k].y) k=i;
    for(int i=1;i<=k;i++) a[i+n-k]=tmp[i];
    for(int i=k+1;i<=n;i++) a[i-k]=tmp[i];
    
    for(int len=2;len<n;len++)
        for(int i=1,j=len;j<n;i++,j++)
        {
            f[i][j][0]=f[i][j][1]=1e18;
            if(f[i][j][0]>f[i+1][j][0]+dis(i,i+1)) f[i][j][0]=f[i+1][j][0]+dis(i,i+1),pre[i][j][0]=0;
            if(f[i][j][0]>f[i+1][j][1]+dis(i,j)) f[i][j][0]=f[i+1][j][1]+dis(i,j),pre[i][j][0]=1;
            if(f[i][j][1]>f[i][j-1][0]+dis(j,i)) f[i][j][1]=f[i][j-1][0]+dis(i,j),pre[i][j][1]=0;
            if(f[i][j][1]>f[i][j-1][1]+dis(j,j-1)) f[i][j][1]=f[i][j-1][1]+dis(j,j-1),pre[i][j][1]=1;
        }
    cout<<a[n].id<<' ';
    if(f[1][n-1][0]+dis(1,n)>f[1][n-1][1]+dis(n-1,n)) print(1,n-1,1);
    else print(1,n-1,0);
    return 0;
}