#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 200010
int n,sgn[N];
int pre_n1,pre_p1,suf_n1,suf_p1;
//(前/后缀)_(d_a)
//pre(fix), suf(fix)
//n(egative)1, p(ositive)1
ll ans[N],s;
int main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    cin.tie(0),cout.tie(0);
    #else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #include "../local.h"
    #endif
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&sgn[i]);
        ans[i]=i,s+=sgn[i]*i;
    }
    for(int i=1,cnt=0;i<=n;i++){
        cnt+=sgn[i];
        //由于变化量为 ±1，cnt 第一次变为正/负时绝对值一定为 1
        if(!pre_n1&&cnt<0)pre_n1=i;
        if(!pre_p1&&cnt>0)pre_p1=i;
        if(pre_n1&&pre_p1)break;
    }
    for(int i=n,cnt=0;i;i--){
        cnt+=sgn[i];
        if(!suf_n1&&cnt<0)suf_n1=i;
        if(!suf_p1&&cnt>0)suf_p1=i;
        if(suf_n1&&suf_p1)break;
    }
    int pre=0,suf=0;
    //根据 s 的正负性选择需要的区间
    if(s<0)s=-s,pre=pre_n1,suf=suf_p1;
    else if(s>0)pre=pre_p1,suf=suf_n1;
    if(s){
        if(pre){
            for(int i=1;i<=pre;i++)ans[i]-=s;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if(suf){
            for(int i=suf;i<=n;i++)ans[i]+=s;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else{
            printf("No");return 0;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
    }
    printf("Yes\n");;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    for(int i=1;i<=n;i++){
        printf("%lld ",ans[i]);;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    }
    return 0;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
}