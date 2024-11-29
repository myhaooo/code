#include<bits/stdc++.h>
using namespace std;

inline int rd() { 
   int x = 0, f = 1;
   char c = getchar();
   while (c < '0' || c > '9') {
      if (c == '-') f = -1;
      c = getchar();
   } 
   while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
   return x * f;
}
#define int long long
const int N = 2e5 + 10;
int a[N];

void solve() {
   int n; cin >> n;
   for(int i=1;i<=n;i++) cin >> a[i];
   if (n == 1) printf("%lld\n", a[1]);
   else if (n == 2) {
      printf("%lld\n", max(2 * abs(a[1] - a[2]), a[1] + a[2]));
   } else if (n == 3) {
      printf("%lld\n", max({3 * abs(a[1] - a[2]), 3 * abs(a[3] - a[2]), 3 * a[1], 3 * a[3], a[1] + a[2] + a[3]}));
   } else { sort(a + 1, a + n + 1);
      printf("%lld\n", a[n] * n);
   }
}

signed main() {
   int q; cin >> q;
   while (q--) solve();
}
