#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll N = 5e5 + 5;
 
ll n, ans[N];
string s;

int main () {
    ios::sync_with_stdio(false);
	#ifndef LOCAL
	cin.tie(0),cout.tie(0);
    #endif
    #ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #endif
    cin >> n >> s;
    ll pos = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        while (pos < n && s[pos] != '<') pos++;
        if (pos == n) break;
        sum += 2 * (pos - i) + 1;
        ans[i] += sum;
        pos++;
    }
    // for (int i = 0; i < n; i++) cout << ans[i] << " ";
    // cout<<"\n";
    pos = n - 1, sum = 0;
    for (int i = n - 1; i >= 0 ;i--) {
        while (pos >= 0 && s[pos] != '>') pos--;
        if (pos < 0) break;
        sum += 2 * (i - pos) + 1;
        ans[i] += sum;
        pos--;
    }
    for (int i = 0; i < n; i++) cout << ans[i] << " ";
    cout << "\n";

   
}