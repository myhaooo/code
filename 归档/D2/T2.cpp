#include <bits/stdc++.h>
using namespace std;
const int N = 100000+5;
int Q;
set<int>s[N]; 
int main() {
	scanf("%d", &Q);
	while (Q--) {
		int t; scanf("%d", &t);
		if (t == 1) {
			int u; scanf("%d", &u);//用 set 预处理一下加入到集合的数u，记录 u 的各个因子。 
			for (int i = 1; i <= (int)sqrt(u); i ++ ) 
				if (u % i == 0) s[i].insert(u), s[u/i].insert(u);
		}
		else {
			int x, k, ss, ans = -1, maxn = -1; scanf("%d%d%d", &x, &k, &ss);
			if (x % k) {printf("-1\n"); continue;} //若 x 不是 k 的倍数 => 直接输出 “-1” 
			auto it = s[k].upper_bound(ss - x);//找到 > x的元素中最小的一个 
			if(s[k].empty() || it == s[k].begin()) {printf("-1\n"); continue;}  
			--it;
			for (; it != s[k].begin(); --it) { 
				int v = *it;
				if (maxn > x + v) break;//v xor x 最大的结果就是 x + v，又 v 在递减 
				if (maxn < (v ^ x)) maxn = v ^ x, ans = v;//找出最大的异或值 
			}
			if (maxn < (*it ^ x)) ans = *it;//判断s[k].begin() 
			printf("%d\n", ans);
		}
	}
	return 0;
}
