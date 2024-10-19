#include<bits/stdc++.h>
using namespace std;
#define M 998244352



namespace sb{
    #define int long long
    #define it __int128
    constexpr int N = 1e6 + 5;
    int p[N], ans, pt;
    inline int qpow(int a, int x){
    	int ans = 1;
    	while(x){
    		if(x & 1) ans = (it)ans * a % M;
    		a = (it)a * a % M;
    		x >>= 1;
    	} return ans;
    }
    inline int inv(int x){
    	return qpow(x, M-2);
    }
    inline int P(int a, int b){
    	return (it)p[a] * inv(p[b]) % M;
    }
    signed solution(int n,int k){
        memset(p,0,sizeof(p));
        ans=0,pt=0;
    	p[0] = 1; for(int i=1; i<=n; ++i) p[i] = (it)p[i-1] * i % M;
    	pt = inv(P(n, k));
    	for(int i=1; i<=k; ++i)
    		ans = ((it)ans + (it)P(n-i, k-i) * pt % M) % M;
    	return ans;
    }
    #undef it
    #undef int
    
}
namespace rig{
    #define int long long
    using namespace std;
    const int modd=M;
    int x,y,jie[1000010],ni[1000010],ans1,ans2;
    void exgcd(int q,int w){
    	if(w==0){
    		x=1;
    		y=0;
    		return;
    	}
    	exgcd(w,q%w);
    	int t=x;
    	x=y;
    	y=t-(q/w)*x;
    	return;
    }
    int C(int q,int w){
    	if(q<w){
    		return 1;
    	}
    	return jie[q]*ni[w]%modd*ni[q-w]%modd;
    }
    signed solution(int n,int m){
        x=0,y=0,ans1=0,ans2=0;
    	if(n==m){
    		return(n);
    	}
    	for(int i=1;i<=m+1;i++){
    		ans1=ans1+(i-1)*C(n-i,m-i+1);
    		ans1%=modd;
    	}
    	ans2=C(n,m);
    	exgcd(ans2,modd);
        int ans=(ans1*x%modd+modd)%modd;
    	return ans;
    }
}

signed main(){
	auto start = std::chrono::high_resolution_clock::now();  
	auto stop = std::chrono::high_resolution_clock::now();  
    rig::jie[0]=1;
    rig::ni[0]=1;
    for(int i=1;i<=1000000;i++){
    	rig::jie[i]=rig::jie[i-1]*i%rig::modd;
    	rig::exgcd(rig::jie[i],rig::modd);
    	rig::ni[i]=(rig::x%rig::modd+rig::modd)%rig::modd;
    }
    for(int n=1100;n<=(int)1e6;n++){
        for(int k=1;k<=n;k++){
            if(sb::solution(n,k)!=rig::solution(n,k)){
                cout<<n<<" "<<k<<endl<<sb::solution(n,k)<<endl<<rig::solution(n,k)<<endl;
                assert(0);

            }
            else{
            	if(n%100==0&&k==1){
					stop = std::chrono::high_resolution_clock::now();  
					auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();  
            		cout<<n<<" "<<k<<" right,time: "<<duration<<endl;
    				start = std::chrono::high_resolution_clock::now();  

    				

				}
			} 


        }
    }

    

}
