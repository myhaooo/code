#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
void read(T &x){
    char c; bool f = 0;
    while(((c = getchar()) < '0' || c > '9') && c != '-');
    if(c == '-'){f = 1; c = getchar();}
    x = c - '0';
    while((c = getchar()) >= '0' && c <= '9')x = x * 10 + c - '0';
    if(f) x = -x;
}
template <typename T>
void write(T x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9)write(x / 10);
    putchar(x % 10 + '0');
}
const ll mod=998244353;
int main(){
    int T;
    read(T);
    while(T--){
        int n;
        read(n);
        int *a=new int[n+2];
        for(int i=1;i<=n;i++){
            read(a[i]);
        }
        if(a[n]!=n){
            write(0);
            putchar('\n');
            delete[] a;
            continue;
        }
        int last=0;
        ll ans=1;
        for(int i=1;i<=n;i++){
            if(a[i]-last>2||a[i]-last<0){
                ans=0;
                break;
            }
            if(a[i]-last==1){
                if(2*i-2*last-1<0){
                    ans=0;
                    break;
                }
                ans=ans*(2*i-2*last-1)%mod;
            }
            else if(a[i]-last==2){
                if(i-1-last<0){
                    ans=0;
                    break;
                }
                ans=ans*(i-1-last)%mod*(i-1-last)%mod;
            }
            last=a[i];
        }
        write(ans);
        putchar('\n');
        delete[] a;
    }
    return 0;
}