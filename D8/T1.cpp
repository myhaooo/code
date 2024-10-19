/*
莫听穿林打叶声，何妨吟啸且徐行。竹杖芒鞋轻胜马，谁怕？一蓑烟雨任平生。
料峭春风吹酒醒，微冷，山头斜照却相迎。回首向来萧瑟处，归去，也无风雨也无晴。
*/
#include<bits/stdc++.h>
using namespace std;
#define gcd __gcd
const int N = 2e5 + 10;
int n, a[N], gcdn, cnt;
int b[N];

signed main(){
    ios::sync_with_stdio(false);
    #ifndef LOCAL
    cin.tie(0),cout.tie(0);
    #define endl '\n'
    #define clear(a) memset(a, 0, sizeof(a))
    #else
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    #include "../local.h"
    #endif
	cin>>n>>a[1]>>a[2];
	
	gcdn = gcd(a[1], a[2]);
	for(int i=3; i<=n; i++){
		cin>>a[i];
		gcdn = gcd(gcdn, a[i]);
	}

	if(gcdn != 1){
		cout<<1; return 0;
	}

	sort(a+1, a+1+n);
	for(int i=2; i<=n; i++){
		b[++cnt] = a[i] - a[1];
	}
    //cout<<cnt<<endl;
	gcdn = gcd(b[1], b[2]);
	for(int i=2; i<=cnt; i++){
		gcdn = gcd(gcdn, b[i]);
	}

	if(gcdn != 1) cout<<1;
	else cout<<2;
}