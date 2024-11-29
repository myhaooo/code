#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010

inline ll read() {
	char ch=getchar();ll ans=0,f=1;
	for (;!isdigit(ch);ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) ans=(ans<<3)+(ans<<1)+ch-'0';
	return ans*f;
}

struct Node{
	int l,r;
}node[N];

int a[N];

int gcd(int x,int y) {
	if (!y) return x;
	return gcd(y,x%y);
}

bool cmp(Node a,Node b) {
	return a.r-a.l<b.r-b.l;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t=read();
	while (t--) {
		int tot=0;
		int n=read(),k=read();
		for (int i = 1;i <= n;++ i) a[i]=read();
		a[0]=a[n+1]=0;
		for (int i = 2;i <= n-1;++ i) {
			if (k && gcd(a[i],a[i-1])==1 && gcd(a[i],a[i+1])==1 && a[i-1]!=1 && a[i+1]!=1) {
				a[i]=0;
				--k;
			} 
		}
		int lst=0;
		int e1=0;
		for (int i = 1;i <= n;++ i) {
			if (a[i]!=1) {
				if (lst>1) {
					node[++tot]={lst,i-1};
				} else if (lst==1) {
					e1=i-1;
				}
				lst=0;
			} else {
				if (lst) continue;
				lst=i;
			}
		}
		sort(node+1,node+tot+1,cmp);
		for (int i = 1;i <= tot;++ i) {
			if (!k) break;
			int len=node[i].r-node[i].l+1;
			if (k>=len) {
				for (int j = node[i].l;j <= node[i].r;++ j) --k,a[j]=0;
			} else {
				for (int j = node[i].l;k;++ j,-- k) a[j]=0;
			}
		}
		if (!lst) lst=n+1;
		for (int j = e1;j >= 1 && k;-- j,--k) a[j]=0;
		for (int j = lst;j <= n && k;++ j,-- k) a[j]=0;
		for (int i = 1;i <= n;++ i) {
			if (!k) break;
			if (k && (gcd(a[i],a[i-1])==1 && a[i-1]!=1 || gcd(a[i],a[i+1])==1 && a[i+1]!=1)) {
				a[i]=0;
				--k;
			}
		}
		int ans=0;
		for (int i = 1;i <= n-1;++ i) ans+=(gcd(a[i],a[i+1])==1);
		cout<<ans<<"\n";
	}
	return 0;
}

