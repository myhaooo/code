#include<stdio.h>
#include<cstring>
#define clear(a) memset(a, 0, sizeof(a))
const int maxn = 100005;
int all, punchh, delta;
int num, n, t, T, fake, rightt;
int h[maxn], ans[maxn], a[maxn], b[maxn], sum[maxn], dis[maxn], cnt[maxn];
inline const int read(){
    int x = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x;
}
struct edge{ int nxt, v;}e[maxn * 2];
inline void add(int u, int v){
    e[++num].v = v, e[num].nxt = h[u], h[u] = num;
    e[++num].v = u, e[num].nxt = h[v], h[v] = num;
}
inline void ed(){
    num = 0, all = 0, punchh = 0, rightt = 0;
    clear(h), clear(ans), clear(cnt);
}
void dfs(int u, int fa){
    sum[u] = a[u]; 
    for(int i = h[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa) continue;
        dis[v] = dis[u] + 1, dfs(v, u); 
        sum[u] += sum[v];
    }
}
void calc_A(int u, int fa){
    for(int i = h[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa) continue;
        ans[v] = ans[u] + sum[1] - sum[v] * 2;
        calc_A(v, u);
    }
}
inline void work_A(){
    for(int i = 1; i <= n; ++i) a[i] = read();
    dfs(1, 1);
    for(int i = 1; i <= n; ++i) ans[1] += dis[i] * a[i]; 
    calc_A(1, 1);
}

void dfss(int u, int fa){
    a[u] = sum[u];
    for(int i = h[u]; i; i = e[i].nxt){
        int v = e[i].v;
        if(v == fa) continue;
        sum[v] = (sum[1] - b[v] + b[u]) / 2;
        dis[v] = dis[u] + 1, dfss(v, u);
        a[u] -= sum[v];
        cnt[u]++;
    }
}
inline void work_B(){
    for(int i = 1; i <= n; ++i) b[i] = read();
    if((10000000 + b[1] - b[fake]) & 1) sum[1] = 10000001;
    else sum[1] = 10000000;
    dfss(1, 1);
    for(int i = 2; i <= n; ++i) all += a[i] * dis[i], punchh += dis[i];
    delta = (b[1] - all) * 2;
    for(int i = 2; i <= n; ++i) rightt += dis[i] * (1 - cnt[i]);
    delta /= rightt, sum[1] += delta;
    dfss(1, 1);
    for(int i = 1; i <= n; ++i) ans[i] = a[i];
}
int main(){
    T = read();
    while(T--){
        n = read();
        for(int i = 1; i < n; ++i){
            int u = read(), v = read();
            if(u != v) add(u, v);
            else continue;
            if(u == 1) fake = v;
            if(v == 1) fake = u;
        }
        t = read();
        if(!t) work_A();
        else   work_B();
        for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
        puts("");
        ed();
    }
}