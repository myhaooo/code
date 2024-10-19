#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define get(a, b) (a == b ? a + 1 : a < b ? b : a)
const int N = 20, P = 1e9 + 7;

int n, k;
ll ans;
ll a[N], dp[1 << 18][18], cnt[1 << 18][18];
set<int> v[1 << 18];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int H = (1 << n) - 1;
    v[0].insert(0);
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
                continue;
            int opt = i | (1 << j);
            for (int val : v[i])
                v[opt].insert(get(a[j], val));
        }
    }
    cnt[0][0] = 1;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
                continue;
            int opt = i | (1 << j);
            int x = 0, y = 0;
            auto it = v[opt].begin();
            for (int val : v[i])
            {
                int d = get(a[j], val);
                while ((*it) != d)
                    it++, y++;
                if (i)
                    dp[opt][y] = (dp[opt][y] + dp[i][x] + cnt[i][x] * d % P * k % P) % P;
                cnt[opt][y] = (cnt[opt][y] + cnt[i][x]) % P;
                x++;
            }
        }
    }
    int c = v[H].size();
    ans = dp[H][c - 1];
    for (int i = 1, p = 1; i < n; i++, p <<= 1)
        ans = (ans + cnt[H][c - 1] * (p - 1) % P) % P;
    auto it = v[H].end();
    it--;
    cout << (*it) << " " << ans;
    return 0;
}