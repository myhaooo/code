#include<iostream>
using namespace std;
#define int long long
typedef pair<int, int> pii;

const int P = 998244353;
inline int plu(int x, int y) {return x + y >= P ? x + y - P : x + y;}
inline int del(int x, int y) {return x - y < 0 ? x - y + P : x - y;}
inline void add(int &x, int y) {x = plu(x, y);}
inline void sub(int &x, int y) {x = del(x, y);}

inline int qpow(int a, int x){
    int ans = 1;
    while(x){
        if(x & 1) ans = ans * a % P;
        a = a * a % P;
        x >>= 1;
    } return ans;
}

inline pii operator + (const pii &a, const pii &b) {return make_pair(plu(a.first, b.first), plu(a.second, b.second));}
inline pii operator * (const pii &a, const pii &b) {
 return make_pair(1ll * a.first * b.first % P, plu(1ll * a.second * b.first % P, 1ll * b.second * a.first % P));
}
bool be;
const int N = 1010, M = 55;
int n, m, p[M << 1];
pii w[M << 1], f[N][M], g[N + M][M];
bool ed;

signed main() {
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        fprintf(stderr, "你的code使用了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        //#include "./local.h"
    #endif


    cin>>n>>m;
    int inv = qpow(1e8, P - 2);
    for(int i = 0,ls; i <= m << 1;i++){
        cin>>ls;
        p[i] = 1ll * inv *ls % P;
    }
        

    for(int i = 0; i <= n - 1;i++) {
        for(int j = 0; j <= m << 1;j++) w[j] = make_pair(0, 0);
        for(int j = 0; j <= m << 1;j++) add(w[max(-i, j - m) + m].first, p[j]);
        for(int j = 0; j <= m << 1;j++) w[j].second = w[j].first;

        for(int j = max(0ll, m - i); j <= m - 1;j++) 
            for(int k = 1; k <= m;k++) 
                w[j + k] = w[j + k] + w[j] * f[i + j - m][k];
        int inv = qpow(del(1, w[m].first), P - 2);

        for(int j = 1; j <= m;j++) {
            f[i][j].first = w[j + m].first * inv % P;
            f[i][j].second = plu(w[j + m].second,w[m].second * f[i][j].first % P) * inv % P;
        }
    }

    g[0][0] = make_pair(1, 0);

    for(int i = 0; i <= n - 1;i++) {
        for(int j = min(i, m); j >= 0;j--){
            for(int k = 1; k <= j;k++) 
                g[i][j - k] = g[i][j - k] + g[i][j] * f[i - j][k];
            for(int k = j + 1; k <= m;k++)
                g[i - j + k][k - j] = g[i - j + k][k - j] + g[i][j] * f[i - j][k];
        }	
    }
    int ans = 0;
    for(int i = n; i <= n + m;i++) 
        for(int j = 0; j <= m;j++)
            add(ans, g[i][j].second);
    cout<<ans<<'\n';

    return 0;
}
