#include <bits/stdc++.h>
using namespace std;

inline void work() {
	set<pair<int, int> > st;
	int mx = 2e9, pos = 2e9, last = -1;
	bool ok = true;
	int n, m;
	cin >> n >> m;
	while (m--) {
		string op;
		int p, q;
		cin >> op;
		if (op == "min") {
			if (!ok)
				cout << "bad" << endl;
			else if (last != -1) {
				auto ptr = st.lower_bound({last, 0});
				if ((prev(ptr) -> first) == (ptr -> first) - 1)
					cout << (ptr -> first) << endl;
				else
					cout << (prev(ptr) -> first) + 1 << endl;
			} else {
				if (st.size() == 0)
					cout << "0" << endl;
				else {
					auto ptr = *st.begin();
					cout << (ptr.first + ptr.second + 1) % 2 << endl;
				}
			}
		} else if (op == "max") {
			if (!ok)
				cout << "bad" << endl;
			else if (mx == 2e9)
				cout << "inf" << endl;
			else
				cout << mx << endl;
		} else {
			cin >> p >> q;
			if (abs(p - 1) > q) {
				ok = false;
				continue;
			}
			if (p > 1)
				pos = min(pos, q);
			if (p > 1)
				mx = min(mx, q - abs(p - 1));
			st.insert({q, p});
			auto ptr = st.find({q, p});
			if (ptr != st.begin() && next(ptr) != st.end() && last == (next(ptr) -> first))
				last = -1;
			if (ptr != st.begin()) {
				auto pre = *prev(ptr);
				if ((pre.first + pre.second) % 2 != (p + q) % 2)
					last = max(last, q);
				if (abs(pre.second - p) > abs(pre.first - q)) {
					ok = false;
					continue;
				}
			}
			if (next(ptr) != st.end()) {
				auto nxt = *next(ptr);
				if ((nxt.first + nxt.second) % 2 != (p + q) % 2)
					last = max(last, nxt.first);
				if (abs(nxt.second - p) > abs(nxt.first - q)) {
					ok = false;
					continue;
				}
			}
			if (last > pos) {
				ok = false;
				continue;
			}
		}
	}
}

int main() {
	freopen("drunkard.in", "r", stdin);
	freopen("drunkard.out", "w", stdout);
	cin.tie(0);
	ios::sync_with_stdio(false);
	work();
	return 0;
}