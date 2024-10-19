#include <bits/stdc++.h>
using namespace std;
int n, m;
priority_queue<int, vector<int>, greater<int> >q;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			q.push(max(i - 1 + j - 1, max(n - i + j - 1, max(i - 1 + m - j, n - i + m - j))));
	for (int i = 1; i <= n * m; i++) {
		cout << q.top() << " ";
		q.pop();
	}
	cout << "\n";
	return 0; 
}