#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int MAXN = (1 << 20) + 5;
char s[MAXN];
int n, z[MAXN];
int before[30], after[30];
int pre, suf, all;

int c[30];

inline int lbt(int x) {
    return x & -x;
}

void update(int x) {
    while (x <= 27) {
        c[x]++;
        x += lbt(x);
    }
}

int sum(int x) {
    int r = 0;
    while (x > 0) {
        r += c[x];
        x -= lbt(x);
    }
    return r;
}

void Z() {
    z[0] = n;
    int now = 0;
    while (now + 1 < n && s[now] == s[now + 1]) {
        now++;
    }
    z[1] = now;
    int p0 = 1;
    for (int i = 2; i < n; ++i) {
        if (i + z[i - p0] < p0 + z[p0]) {
            z[i] = z[i - p0];
        } else {
            now = p0 + z[p0] - i;
            now = max(now, 0);
            while (now + i < n && s[now] == s[now + i]) {
                now++;
            }
            z[i] = now;
            p0 = i;
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        n = strlen(s);
        memset(before, 0, sizeof(before));
        memset(after, 0, sizeof(after));
        memset(c, 0, sizeof(c));
        all = pre = suf = 0;
        Z();
         
        for (int i = 0; i < n; ++i) {
            if (i + z[i] == n) z[i]--;
        }
        
        for (int i = 0; i < n; ++i) {
            after[s[i] - 'a']++;
        }
        
        for (int i = 0; i < 26; ++i) {
            if (after[i] & 1) {
                all++;
            }
        }
        suf = all;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {

            if (after[s[i] - 'a'] & 1) {
                suf--;
            } else {
                suf++;
            }
            after[s[i] - 'a']--;
            if (before[s[i] - 'a'] & 1) {
                pre--;
            } else {
                pre++;
            }
            before[s[i] - 'a']++;
            if (i != 0 && i != n - 1) {
                int t = z[i + 1] / (i + 1) + 1;
                ans += 1LL * (t / 2) * sum(all + 1) + 1LL * (t - t / 2) * sum(suf + 1);
            }
            update(pre + 1);
        }
        cout << ans << endl;
    }
    return 0;
}
