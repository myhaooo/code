#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define fi first
#define se second
#define ls tr[o][0]
#define rs tr[o][1]
const int maxn = 1e6 + 10;
const int mod = 998244353;
const int N = mod - mod / 2;
bool M1;
int n;
char s[maxn];
int tr[maxn][2], tot;
char tp[maxn];
int pos = 0;
ll f[maxn][2];
int init() {
    ++pos;
    int o = ++tot;
    if (s[pos] == 'x') {
        return tp[o] = 'x', tot;
    }
    tr[o][0] = init();
    tp[o] = s[++pos];
    tr[o][1] = init();
    ++pos;
    return o;
}

void dfs(int o) {
    if (!o)
        return;
    dfs(tr[o][0]);
    cout << o << " " << tp[o] << "\n";
    dfs(tr[o][1]);
}
void dp(int o) {
    if (tp[o] == 'x')
        return f[o][0] = f[o][1] = N, void();
    dp(tr[o][0]);
    dp(tr[o][1]);
    if (tp[o] == '^') {
        f[o][0] = (f[ls][0] * f[rs][0] + f[ls][1] * f[rs][1]) % mod;
        f[o][1] = (f[ls][0] * f[rs][1] + f[ls][1] * f[rs][0]) % mod;
    } else if (tp[o] == '&') {
        f[o][1] = f[ls][1] * f[rs][1] % mod;
        f[o][0] = (1 - f[o][1] + mod) % mod;
    } else  // '|'
    {
        f[o][0] = f[ls][0] * f[rs][0] % mod;
        f[o][1] = (1 - f[o][0] + mod) % mod;
    }
}

void sol(int o, ll p) {
    if (tp[o] == 'x')
        return cout << p << "\n", void();
    if (tp[o] == '^') {
        sol(ls, p);
        sol(rs, p);
    } else if (tp[o] == '&') {
        sol(ls, p * f[rs][1] % mod);
        sol(rs, p * f[ls][1] % mod);
    } else  // '|'
    {
        sol(ls, p * f[rs][0] % mod);
        sol(rs, p * f[ls][0] % mod);
    }
}
int main() {
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> s + 1;
    init();
    dp(1);
    sol(1, 1);
    return 0;
}
