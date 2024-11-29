#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 7;
const int inf = 1e9 + 7;
int n, cnt[N << 1];
char s[N];
void Main() {
 scanf("%s", s + 1), n = strlen(s + 1);
 int now = 0;
 for(int i=1;i<=n;i++) {
  if(s[i] == '1') cnt[N + now] ++, now ++;
  else now --, cnt[N + now] ++;
 }
 now = 0;
 for(int i=1;i<=n;i++) {
  if(cnt[N + now - 1] > 0 && (!cnt[N + now] || cnt[N + now - 1] > 1)) --now, cnt[N + now] --, putchar('0');
  else cnt[N + now] --, now ++, putchar('1');
 }
 cout<<"\n";
 for(int i=-n;i<=n;i++) cnt[N + i] = 0;
}
int main() {
 int T; scanf("%d", &T);
 while(T--) Main();
 return 0;
}
