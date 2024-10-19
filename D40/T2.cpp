#include <bits/stdc++.h>
using namespace std;
set<pair<int, int> > st;
int mx = 2e9, pos = 2e9;
bool ok = true;
int n, m;

int main() {
	freopen("drunkard.in", "r", stdin);
	freopen("drunkard.out", "w", stdout);
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	while (m--) {
		string op;
		int p, q;
		cin >> op;
		if (op == "min") {
			if (!ok)
				cout << "bad" << endl;
			else if (st.size() == 0)
				cout << "0" << endl;
			else {
				auto ptr = *st.begin();
				cout << (ptr.first + ptr.second + 1) % 2 << endl;
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
				mx = min(mx, q - abs(p - 1));
			st.insert({q, p});
			auto it = st.find({q, p});
			if (it != st.begin()) {
				auto pre = *(it--);
				if (abs(pre.second - p) > abs(pre.first - q)) {
					ok = false;
					continue;
				}
			}
			if ((it++) != st.end()) {
				auto nxt = *(it++);
				if (abs(nxt.second - p) > abs(nxt.first - q)) {
					ok = false;
					continue;
				}
			}
		}
	}
	return 0;
}