#include<bits/stdc++.h>
using namespace std;
int cost[4010][4010];
int n,i,j;
#ifdef linux
    #define getchar   getchar_unlocked
    #define getchar() getchar_unlocked()
    #define putchar   putchar_unlocked
    #define putchar() putchar_unlocked()
#endif
#ifdef _UNIX
    #define getchar   getchar_unlocked
    #define getchar() getchar_unlocked()
    #define putchar   putchar_unlocked
    #define putchar() putchar_unlocked()
#endif
#ifdef _WIN32
    #define getchar() _getchar_nolock()
    #define getchar   _getchar_nolock
    #define putchar() _putchar_nolock()
    #define putchar   _putchar_nolock
#endif
inline int read(){
    int ans=0,f=1;char ch;
    ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        ans=ans*10+ch-'0';
        ch=getchar();
    }
    return ans*f;
}
bitset<4010>f[4010];
bool check(int mid){
	for(int i=1;i<=n;i++){
		f[i].reset();
		f[i][i-1]=1;
	}
	for(int l=n;l>=1;l--){
		for(int r=l+1;r<=n;r+=2){
			if(!f[l][r]&&cost[l][r]<=mid&&f[l+1][r-1]){
				f[l][r]=1;
				f[l]|=f[r+1];
			}
		}
	}
	return (f[1][n]);
}
int main()
{
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
        #include "../local.h"
    #endif

    int l=1,r,mid,ans=0;
	n=read();
	r=n*n/4;
	for(i=1;i<=n-1;i++){
		for(j=i+1;j<=n;j+=2){
			cost[i][j]=read();
		}
	}
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans<<'\n';
	return 0;
}