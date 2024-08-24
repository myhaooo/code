#include<bits/stdc++.h>
#define ll long long
using namespace std;
string s;int k,n,m,y;
int a[35],b[35],c[35],sz;
ll dp[35][35][35][605],ans;
int sm1[35],sm2[35],sm3[35];
inline void getin(){
    cin>>s>>k;sz=s.size();
    k=min(k,sz*(sz-1)/2);
    for(int i=0;s[i];i++){
        sm1[i+1]=sm1[i];
        sm2[i+1]=sm2[i];
        sm3[i+1]=sm3[i];
        if(s[i]=='K')
            a[++n]=i+1,sm1[i+1]++;
        if(s[i]=='E')
            b[++m]=i+1,sm2[i+1]++;
        if(s[i]=='Y')
            c[++y]=i+1,sm3[i+1]++;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    getin();
    dp[0][0][0][0]=1;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int l=0;l<=y;l++)
                for(int t=0;t<=k;t++){
                    if(i<n){
                        int p=a[i+1],cnt=max(0,sm2[p]-j)+max(0,sm3[p]-l);
                        //cnt指将第i+1个K移动到第i+j+l+1位所用的代价，下同 
                        dp[i+1][j][l][t+cnt]+=dp[i][j][l][t];
                    }if(j<m){
                        int p=b[j+1],cnt=max(0,sm1[p]-i)+max(0,sm3[p]-l);
                        dp[i][j+1][l][t+cnt]+=dp[i][j][l][t];
                    }if(l<y){
                        int p=c[l+1],cnt=max(0,sm1[p]-i)+max(0,sm2[p]-j);
                        dp[i][j][l+1][t+cnt]+=dp[i][j][l][t];
                    }if(i+j+l==sz) ans+=dp[i][j][l][t];
                }
    cout<<ans;
    return 0;
}
