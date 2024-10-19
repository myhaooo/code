#include <bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint unsigned int
using namespace std;
const int M = 6e5 + 5;
const int p = 998244353;
const ull q = 13331;
const int qq = 131;
int z(char c){
	return c - 'a';
}
vector<ull> hs[M];
vector<int> hh[M];
string s;
ull qp[M];
int n, m, l[M], pq[M];
unordered_map<int, int> mp[M];
int get(int i, int j){
	for (int k = min(l[i], l[j]); k; k--)
		if (hs[i][l[i]] - hs[i][l[i] - k] * qp[k] == hs[j][k])
				return k;
	return 0;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m, qp[0] = pq[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		cin >> s, s = " " + s;
		l[i] = s.size() - 1;

		hs[i].push_back(0);
		for (int j = 1; j <= l[i]; j++)
			hs[i].push_back(hs[i][j - 1] * q + z(s[j]));

	}
	for (int i = 1; i < M; i++)
		qp[i] = qp[i - 1] * q;
	while (m--)
	{
		int x, y;
		cin >> x >> y;
		if (!mp[x].count(y))
			mp[x][y] = get(x, y);
		cout << mp[x][y] << "\n";
	}
	return 0;
}
