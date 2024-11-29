#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;
const int MAXN = 1e5 + 5; 
int n, m, q;
vector<int> a(MAXN), temp(MAXN), opL(MAXN), opR(MAXN), queryL(MAXN), queryR(MAXN);

void ask(int l, int r, int value) {
    for (int i = l; i <= r; i++) temp[i] = value; 
}
int query(int L, int R) {
    unordered_set<int> distinctValues;
    for (int i = L; i <= R; i++) distinctValues.insert(temp[i]);
    return distinctValues.size();
}
int main() {
    cin >> n >> m ;
    for (int i = 1; i <= n; i++) a[i] = i;
    for (int i = 1; i <= m; i++) cin >> opL[i] >> opR[i];
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> queryL[i] >> queryR[i];
    for (int i = 1; i <= q; i++) {
        for (int j = 1; j <= n; j++) temp[j] = a[j];
        int L = queryL[i], R = queryR[i];
        for (int j = L; j <= R; j++) {
            ask(opL[j], opR[j], temp[opL[j]]);
        }
        cout << query(1, n) << endl;
    }
    return 0;
}

