#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> ans;
vector<int> toBaseB(int num, int B) {
    vector<int> digits;
    while (num > 0) {
        digits.push_back(num % B);
        num /= B;
    }
    return digits;
}

bool cleck(int num, int B) {
    vector<int> digits = toBaseB(num, B);
    set<int> seen;
    for (int d : digits) {
        if (seen.count(d)) return false;
        seen.insert(d);
    }
    return true;
}
int to10(const vector<int>& digits, int B) {
    int num = 0;
    for (int d : digits) {
        num = num * B + d;
    }
    return num;
}

void per(vector<int>& digits, int B, vector<int>& results) {
    sort(digits.begin(), digits.end()); 
    do {
        int number = to10(digits, B);
        results.push_back(number);
    } while (next_permutation(digits.begin(), digits.end())); 
}

 
 main() {
	freopen("multi.in","r",stdin);
	freopen("multi.out","w",stdout);
    int n, B;
    cin >> n >> B;
if(n>1){
	for (int i = 1; i <= 1000000; i++) { 
        int mul = n * i;
        if (cleck(mul, B)) {
            ans.push_back(mul);
        }
    }
    if (ans.size() < 2) {
        cout << -1 << endl; 
    } else {
        sort(ans.rbegin(), ans.rend()); 
        cout << ans[1] << endl; 
    }
		
}
else{
    vector<int> digits;
    for (int i = 0; i < B; ++i) {
        digits.push_back(i);
    }

    vector<int> results;
    per(digits, B, results);
    for (int num : results) {
        if (num % n == 0) {
            ans.push_back(num);
        } 
    }

    if (ans.size() < 2) {
        cout << -1 << endl; 
    } else {
        sort(ans.rbegin(), ans.rend());
        cout << ans[1] << endl;
    }
}
}

