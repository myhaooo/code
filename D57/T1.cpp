#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000005;
bool f[maxn];
vector<int> pr;
int main() {
    freopen("factorial.in", "r", stdin);
    freopen("factorial.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        if (!f[i])
            pr.push_back(i);
        for (int p : pr) {
            if (i * p > n)
                break;
            f[i * p] = true;
            if (!(i % p))
                break;
        }
    }
    printf("f(%d)=", n);
    for (int p : pr) {
        long long e = 0, pw = p;
        while (pw <= n) {
            int x = n / pw;
            e += (n + 1) * x - pw * (x * (x + 1) >> 1);
            pw *= p;
        }
        if (p != 2)//744
            putchar('*');
        printf("%d", p);
        if (e != 1)
            printf("^%lld", e);
    }
    printf("\n");
    return 0;
}

