#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
const int mod=998244353;
ll f[52][52][2610];
ll an[52][2502]; 

inline void m(ll &x,const ll &y)
{
	x=(x+y)%mod;
}

signed main()
{

    freopen("in.in","r",stdin);
    freopen("ansfull.txt","w",stdout);

    for(int n=1;n<=50;n++){
        for(int k=1;k<=n*n;k++){
            memset(f,0,sizeof f);
            f[1][0][0]=1;
            for(int i=2;i<=n;++i)
            	for(int j=0;j<=n;++j)
            		for(int u=0;u<=k;++u)
            		{
            			//两边 
            			m(f[i][j][u+i],f[i-1][j][u]*2);//贴边
            			m(f[i][j+1][u],f[i-1][j][u]*2);//空

            			//中间
            			m(f[i][j][u+i],f[i-1][j][u]*j*2);//贴边
            			m(f[i][j+1][u],f[i-1][j][u]*j);//中间
            			if(j)m(f[i][j-1][u+2*i],f[i-1][j][u]*j);//连接 
            		}

            ll ans=0;	
            for(int i=0;i<=k;++i)
            	m(ans,f[n][0][i]);
            an[n][k]=ans;
            //if(ans!=0)
			printf("a[%lld][%lld]=%lld;\n",n,k,ans);
        }
    }
    
//	for(int i=0;i<52;i++){
//		for(int j=0;j<2502;j++){
//			cout<<an[i][j]<<",";
//		}
//	}        
	
	
	
	return 0;
}
