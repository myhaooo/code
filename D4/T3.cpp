#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int fa[N], v[N], son[N], n, m, a[N];

int main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    cin.tie(0),cout.tie(0);
    #else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #include "../local.h"
    #endif
  cin>>n>>m;
  for(int i = 2; i <= n; ++i) {
    cin>>fa[i]; 
    son[fa[i]]++;
  }
  
  for(int k = 1; k <= m; ++k) {
    cin>>n;
    for(int i = 1; i <= n; ++i) {
      cin>>a[i];
      v[a[i]] = 1;
    }
    int sum = 0;
    for(int i = 1; i <= n; ++i) {
      int x = a[i];
      if(!v[fa[x]]) ++sum;
      else --sum;
      sum += son[x];
    }
    cout<<sum<<"\n";
    for(int i = 1; i <= n; ++i) v[a[i]] = 0;
  }
  
  return 0;
}