#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int, int> &a, pair<int, int> &b) {
	if (a.second != b.second)
		return a.second > b.second;
	return a.first > b.first;
}

int main() {
	freopen("binary.in", "r", stdin);
	freopen("binary.out", "w", stdout);

	int T;
	cin >> T;
	while (T--) {
		int L, R, a, b;
		cin >> L >> R >> a >> b;

		vector<pair<int, int>> nums;
		for (int i = L; i <= R; i++) {
			int ones_count = __builtin_popcount(i);
			nums.push_back({i, ones_count});
		}
		sort(nums.begin(), nums.end(), cmp);
		long long sum = 0;
		for (int i = a - 1; i < b; i++) {
			sum += nums[i].first;
		}
		cout << sum << endl;
	}
	return 0;
}
