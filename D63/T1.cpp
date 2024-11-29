#include <iostream>
#include <set>
#include <vector>
#define int long long
using namespace std;

 main() {
    int n, a, m;
    cin >> n >> a >> m;
    
    vector<int> is_bad(n + 1, 0); 
    set<int> bad_positions;      
    
    auto count_max_sticks = [&](int len) {
        if (len < a) return 0; 
        return 1ll*(len - a) / (a + 1) + 1ll;
    };

    int max_sticks = count_max_sticks(n); 

    for (int i = 0; i < m; ++i) {
        int pos;
        cin >> pos;
        pos--;

        if (is_bad[pos]) {
            cout << max_sticks << endl; 
            continue;
        }

        auto it = bad_positions.lower_bound(pos);
        int right = (it == bad_positions.end()) ? n : *it;
        int left = (it == bad_positions.begin()) ? -1 : *prev(it);
        max_sticks -= count_max_sticks(right - left - 1);
        is_bad[pos] = 1;
        bad_positions.insert(pos);


        max_sticks += count_max_sticks(pos - left - 1);
        max_sticks += count_max_sticks(right - pos - 1);

        cout << max_sticks << endl;
    }
    
    return 0;
}

