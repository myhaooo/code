#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 15;
vector<int> E[N];
int n, m, fa[N], X[N], Y[N], Z[N], C[N], Tmp[N][N];
inline int find(int x) {
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
int main() {
//    freopen("str.in", "r", stdin);
//    freopen("str.out", "w", stdout);
    cin>>n>>m;
    assert(n<10);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) {
        cin>>X[i]>>Y[i]>>Z[i];
        for (int j = 0; j < Z[i]; j++) {
            int fx = find(X[i] + j), fy = find(Y[i] + j);
            fa[fy] = fx;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (X[i] + Z[i] > n || Y[i] + Z[i] > n)
            continue;
        int fx = find(X[i] + Z[i]), fy = find(Y[i] + Z[i]);
        if (fx == fy)
            return cout<<-1<<endl, 0;
        E[fx].pb(fy), E[fy].pb(fx);
    }
    fill(C + 1, C + n + 1, -1);
    for (int i = 1; i <= n; i++) {
        int f = find(i);
        if (C[f] != -1)
            continue;
        int j = 0;
        while (Tmp[f][j]) j++;
        C[f] = j;
        for (int x : E[f]) Tmp[x][j] = 1;
    }
    for (int i = 1; i <= n; i++) {
       cout<<C[find(i)]<<" ";
    }
}

