#include <iostream>
#include <cmath>

using namespace std;

const int MOD = 1e9 + 7;

// 快速幂计算 (x^y) % p
long long power(long long x, long long y, long long p) {
    long long res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) 
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    // 计算 2^n
    long long total_combinations = power(2, n, MOD);

    // 包含-排除原理计算
    long long result = 0;
    for (int i = 0; i <= n; ++i) {
        long long term = power(2, i, MOD);
        term = (term * power(2, n - i, MOD)) % MOD;
        if (i % 2 == 0)
            result = (result + term) % MOD;
        else
            result = (result - term + MOD) % MOD;
    }

    cout << result << endl;

    return 0;
}
