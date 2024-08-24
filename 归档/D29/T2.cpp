#include<bits/stdc++.h>
using namespace std;
#define ll long long

map<int,ll>M[10];
int k,apk,S=0,tim[26],endd,buc[10];char ss[888];long long c;
int bit(int x){return x?1<<4*x-4:0;}
ll sch(int l,int Start,ll rk,int lst){
    if(M[lst].find(Start)!=M[lst].end()&&rk>=M[lst][Start])return M[lst][Start];
    if(Start==endd){
        if(!rk){puts(ss);exit(0);}
        return M[lst][Start]=1;
    }
    long long pl=0,r;
    for(int z=S;z<26;++z)if('a'+z!=ss[l-1]){
        ss[l]=z+'a';tim[z]++;buc[tim[z]]++;
        if(buc[tim[z]]<=k-tim[z]+1)r=sch(l+1,Start+bit(tim[z])-bit(tim[z]-1),rk,tim[z]),pl+=r,rk-=r;
        buc[tim[z]]--;tim[z]--;
    }return M[lst][Start]=pl;
}

int main(){
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
        #define file(a) FILE *FI = freopen(#a".in","r",stdin); FI = freopen(#a".out","w",stdout)
        file(string);
    #else
        #ifdef LEN
    	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n"
        , abs(&be - &ed) / 1048576.0);
        #endif
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        //#include "../local.h"
    #endif

    cin>>k>>c;
    while(k>8){
        for(int i=1;i<k;++i)putchar(S+'a'),putchar(S+'b');
        putchar(S+'a');k-=2;S+=2;
    }
    for(int i=1;i<=k;++i)endd|=bit(i);
    sch(0,0,c-1,9);
    puts("-1");
}
