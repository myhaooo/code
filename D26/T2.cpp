#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &x){
    static char ch; x = 0,ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - '0',ch = getchar();
}
inline void write(int x){if (x > 9) write(x/10); putchar(x%10+'0'); }

const int INF = 1e9 + 7,N = 100005;
int n,m,rt,a[N],fa[N],ch[N][2],z[N];

int dpt[N],son[N],size[N];
inline void dfs1(int x){
    dpt[x] = dpt[fa[x]] + 1,size[x] = 1;
    for (int i = 0,y; i < 2; ++i) if (y=ch[x][i]){
        dfs1(y),size[x] += size[y];
        if (size[y] > size[son[x]]) son[x] = y;
    }
}
int top[N];
int Time,id[N],tl[N],tr[N],node[N];
inline void dfs2(int x){
    id[x] = tl[x] = ++Time; node[Time] = x;
    if (son[x]) top[son[x]] = top[x],dfs2(son[x]);
    for (int i = 0,y; i < 2; ++i) if (ch[x][i] && !top[y=ch[x][i]]) top[y] = y,dfs2(y);
    tr[x] = Time;
}

struct Node{
    int mx,mn;
    Node(int Mx = -INF,int Mn = INF){ mx = Mx,mn = Mn; }
}f0[N<<2],f1[N<<2]; bool rev[N<<2];
Node operator + (Node A,Node B){ return Node(max(A.mx,B.mx),min(A.mn,B.mn)); }
//IIlllllIIIIlIIlll
#define lc root<<1
#define rc root<<1|1
#define mid ((l+r)>>1)
inline void up(int root){ f0[root] = f0[lc] + f0[rc],f1[root] = f1[lc] + f1[rc]; }
inline void Build(int root,int l,int r){
    if (l ^ r){ Build(lc,l,mid); Build(rc,mid+1,r); up(root); return; }
    if (fa[node[l]]){
        if (z[node[l]]) f1[root] = Node(a[fa[node[l]]],a[fa[node[l]]]);
        else f0[root] = Node(a[fa[node[l]]],a[fa[node[l]]]);
    }
}
int ll,rr,pp;
inline void Tag(int root){ if (root) rev[root] ^= 1,swap(f0[root],f1[root]); }
inline void down(int root){ if (rev[root]) Tag(lc),Tag(rc),rev[root] = 0; }
inline void Modify(int root,int l,int r){
    if (l == r){
        f0[root] = f1[root] = Node();
        z[node[l]] ^= rev[root],rev[root] = 0;
        if (fa[node[l]]){
            if (z[node[l]]) f1[root] = Node(a[fa[node[l]]],a[fa[node[l]]]);
            else f0[root] = Node(a[fa[node[l]]],a[fa[node[l]]]);
        }
        return;
    }
    down(root); if (pp <= mid) Modify(lc,l,mid); else Modify(rc,mid+1,r); up(root);
}
inline void Rev(int root,int l,int r){
    if (ll <= l && rr >= r){ Tag(root); return; }
    down(root); 

    if (ll <= mid) Rev(lc,l,mid); 
    if (rr > mid) Rev(rc,mid+1,r); 
    up(root);
}
Node q0,q1;
inline void Ask(int root,int l,int r){
    if (ll <= l && rr >= r){ q0 = q0 + f0[root],q1 = q1 + f1[root]; return; }
    down(root); 
    if (ll <= mid) Ask(lc,l,mid); 
    if (rr > mid) Ask(rc,mid+1,r); 
}
inline bool Query(int x){
    int v = a[x]; q0 = q1 = Node();
    while (x) ll = id[top[x]],rr = id[x],Ask(1,1,n),x = fa[top[x]];
    return q1.mx < v && v < q0.mn;
}

#undef lc
#undef rc
#undef mid

int main(){
    int i;
    read(n),read(m);
    for (i = 1; i <= n; ++i){
        read(a[i]),read(ch[i][0]),read(ch[i][1]);
        if (ch[i][0]) fa[ch[i][0]] = i;
        if (ch[i][1]) fa[ch[i][1]] = i,z[ch[i][1]] = 1;
    }
    for (i = 1; i <= n; ++i) if (!fa[i]) rt = i;
    dfs1(rt),top[rt] = rt,dfs2(rt);
    Build(1,1,n);
    int op,x;
    while (m--){
        read(op),read(x);
        if (op == 1){
            read(a[x]);
            if (ch[x][0]) pp = id[ch[x][0]],Modify(1,1,n);
            if (ch[x][1]) pp = id[ch[x][1]],Modify(1,1,n);
        }
        if (op == 2){
            ll = tl[x]+1,rr = tr[x]; if (ll <= rr) Rev(1,1,n); 
        }
        if (op == 3){
            puts(Query(x) ? "YES" : "NO");
        }
    }
    return 0;
}