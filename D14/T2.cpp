#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar();
	int x = 0, pd = 0;
	while (ch < '0' || ch > '9') pd |= ch == '-', ch = getchar();
	while ('0' <= ch && ch <= '9') x = x * 10 + (ch ^ 48), ch = getchar();
	return pd ? -x : x;
}
const int maxn = 100005;
int n, m, a[maxn];
#define ls (o << 1)
#define rs (o << 1 | 1)
#define lson ls,l,mid
#define rson rs,mid+1,r
bool lm[maxn << 2][4], rm[maxn << 2][4];
ll s[maxn << 2][4];
void pushup(int o, int l, int r) {
	int mid = (l + r) >> 1;
	if (rm[ls][0] && lm[rs][0]) {
		if (a[mid] >= a[mid + 1]) {
			lm[o][0] = lm[ls][0], rm[o][0] = rm[rs][1];
			s[o][0] = s[ls][0] + s[rs][1];
		} else{
			lm[o][0] = lm[ls][2], rm[o][0] = rm[rs][0];
			s[o][0] = s[ls][2] + s[rs][0];
		}
	} else lm[o][0] = lm[ls][0], rm[o][0] = rm[rs][0], s[o][0] = s[ls][0] + s[rs][0];

	if (rm[ls][1] && lm[rs][0]) {
		if (a[mid] >= a[mid + 1]) {
			rm[o][1] = rm[rs][1];
			s[o][1] = s[ls][1] + s[rs][1];
		} else {
			rm[o][1] = rm[rs][0];
			s[o][1] = s[ls][3] + s[rs][0];
		}
	} else rm[o][1] = rm[rs][0], s[o][1] = s[ls][1] + s[rs][0];

	if (rm[ls][0] && lm[rs][2]) {
		if (a[mid] >= a[mid + 1]) {
			lm[o][2] = lm[ls][0];
			s[o][2] = s[ls][0] + s[rs][3];
		} else {
			lm[o][2] = lm[ls][2];
			s[o][2] = s[ls][2] + s[rs][2];
		}
	} else lm[o][2] = lm[ls][0], s[o][2] = s[ls][0] + s[rs][2];

	if (rm[ls][1] && lm[rs][2]) {
		if (a[mid] >= a[mid + 1]) s[o][3] = s[ls][1] + s[rs][3];
		else s[o][3] = s[ls][3] + s[rs][2];
	} else s[o][3] = s[ls][1] + s[rs][2];
}
void build(int o, int l, int r) {
	if (l == r) {
		s[o][0] = a[l] = read();
		lm[o][0] = rm[o][0] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(lson), build(rson), pushup(o, l, r);
}
void upd(int o, int l, int r, int x) {
	if (l == r) { s[o][0] = a[l]; return; }
	int mid = (l + r) >> 1;
	if (x <= mid) upd(lson, x);
	else upd(rson, x);
	pushup(o, l, r);
}
int main() {
	n = read();
	build(1, 1, n);
	m = read();
	while (m--) {
		int x = read(), y = read();
		a[x] = y, upd(1, 1, n, x);
		printf("%lld\n", s[1][0]);
	}
	return 0;
}