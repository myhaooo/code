#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int main() {
	freopen("yilihun.in","r",stdin);
	freopen("yilihun.out","w",stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> lst(n, vector<int>(m)); 
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            lst[i][j] = s[j] - '0';
        }
    }

    vector<int> result(m, 0);  
    vector<int> perm(n);     
    for (int i = 0; i < n; i++) perm[i] = i;  
    do {
        vector<bool> ok(m, true);
        int cnt = m;       

        for (int i = 0; i < n && cnt > 1; i++) {
            int idx = perm[i];
            int ans = 0;
            for (int j = 0; j < m; j++) {
                if (ok[j] && lst[idx][j]) {
                    ans++;
                }
            }
            if (ans > 0 && ans < cnt) {
                for (int j = 0; j < m; j++) {
                    if (ok[j] && !lst[idx][j]) {
                        ok[j] = false;
                        cnt--;
                    }
                }
            }
        }

        if (cnt == 1) {
            for (int j = 0; j < m; j++) {
                if (ok[j]) {
                    result[j] = (result[j] + 1) % MOD;
                    break;
                }
            }
        }
    } while (next_permutation(perm.begin(), perm.end()));

    for (int i = 0; i < m; i++) {
        cout << result[i] << endl;
    }

    return 0;
}

