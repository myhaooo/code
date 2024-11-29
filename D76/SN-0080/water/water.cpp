#include <bits/stdc++.h>
#define int __int128
using namespace std;

inline void print(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        print(x / 10);
    }
    putchar(x % 10 + '0');
}

#define gcd __gcd
const int MAXN = 1e5+5;

vector<int> edge[MAXN]; 
signed n, m;

struct Fraction {
    int fenzi; 
    int fenmu;

    void clear() {
        fenzi = 0;
        fenmu = 0;
    }
};

Fraction add(Fraction a, Fraction b) {
    if (a.fenmu == 0) return b;
    Fraction result;
    int lcm = a.fenmu * b.fenmu / gcd(a.fenmu, b.fenmu); 
    result.fenzi = b.fenzi * (lcm / b.fenmu) + a.fenzi * (lcm / a.fenmu);
    result.fenmu = lcm;
    int res = gcd(result.fenzi, result.fenmu);
    result.fenzi /= res,result.fenmu /= res;
    return result;
}

Fraction result[MAXN], flow[MAXN];

void dfs(int x) {
    if (edge[x].empty()) {
        result[x] = add(result[x], flow[x]); 
        flow[x].clear(); 
        return;
    }

    Fraction tmp = flow[x];
    tmp.fenmu *= edge[x].size(); 

    for (auto it : edge[x]) {
        flow[it] = add(flow[it], tmp);
        dfs(it);
    }

    flow[x].clear();
}

signed main() {
		freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        result[i].clear();
    }
    for (int i = 1; i <= n; i++) {
        signed x, y;
        cin >> x;
        for (int j = 0; j < x; j++) {
            cin >> y;
            edge[i].push_back(y);
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) flow[j].clear();
        flow[i].fenzi = 1,flow[i].fenmu = 1;
        dfs(i);
    }

    for (int i = 1; i <= n; i++) {
        if (edge[i].empty()) {
            print(result[i].fenzi);
            putchar(' ');
            print(result[i].fenmu);
            putchar(10);
        }
    }

    return 0;
}

