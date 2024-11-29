#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
int T, n;
int main() {
    freopen("election.in", "r", stdin);
    freopen("election.out", "w", stdout);
    cin >> T;
    while (T--) {
        cin >> n;
        if (n == 2)
            cout << "10" << endl;
        else if (n == 1)
            cout << "0" << endl;
        else {
            for (int i = 1; i <= n - 2; i++) cout << 1;
            cout << "00" << endl;
        }
    }
    return 0;
}
