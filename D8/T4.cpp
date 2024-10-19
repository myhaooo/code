#include<bits/stdc++.h>
using namespace std;
template<class T> using V = vector<T>;
using LL = long long;
const int NN = 1.2E4 + 5;
int R, C, B[NN];
void M(int k, int d){for(; k; k -= k & (-k)) B[k] += d;}
int Q(int k){
	int res = 0;
	for(; k <= (C + 1) / 2; k += k & (-k)) res += B[k];
	return res;
}
using VI = V<int>;
LL solve(V<string> &G){
	V<VI> U(2 * R, VI(2 * C)), D(U), T(2 * C);
	auto pd = [&](int a, int b){return G[a][b] != ' ';};
	LL ans = 0; 
	for(int r = 1; r < 2 * R; r += 2){
		int mx = 0;
		for(int c = pd(r, 1) ? 1 : 3, k = 1, l = 0; c < 2 * C; c += 4, ++k){
			int &u =  U[r][c], &d = D[r][c];
			u = pd(r - 1, c - 1) ? U[r - 2][c - 2] + 1 : 0,
			d = pd(r - 1, c + 1) ? D[r - 2][c + 2] + 1 : 0,
			l = pd(r, c - 1) ? l + 1 : 0, ans += Q(k - min(u, l)),
			M(k, 1), T[k + d].push_back(k), mx = max(mx, k + d);
			while(!T[k].empty()) M(T[k].back(), -1), T[k].pop_back(); 
		}
		for(int i = C / 2 + 1; i <= mx; ++i) while(!T[i].empty())
			M(T[i].back(), -1), T[i].pop_back();	
	}
	return ans;
}
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> R >> C, cin.ignore();
	V<string> G(2 * R, string(2 * C + 2, ' '));
	for(int i = 1; i < 2 * R; ++i){
		string s;
		getline(cin, s);
		for(int j=0;j<s.length();j++){
			if(s[i]=='\r')
			s.erase(s.begin()+j);
		}
		copy(begin(s), end(s), begin(G[i]) + 1); 
	}
	LL ans = solve(G);
	reverse(begin(G) + 1, end(G)), ans += solve(G);
	return printf("%lld", ans), 0; 
}