#include <bits/stdc++.h>
using ll = long long;
const int N = 1e3 + 5;
using namespace std;
int T, n, k, a[N][N]; // 丨|lI

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    for (cin >> T; T--;)
    {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = 0;
        if (k & 1)
        {
            cout << "No\n";
            continue;
        }

        if (n == 2)
        {
            if (!k)
                cout << "Yes\n0 0\n0 0\n";
            if (k == 2)
                cout << "Yes\n1 0\n0 1\n";
            if (k == 4)
                cout << "Yes\n1 1\n1 1\n";
            continue;
        }
        if (k == n * n - 2 || k == 2){
            cout << "No\n";
            continue;
        }
        for (int i = 1; i <= n; i += 2)
            for (int j = 1; j <= n; j += 2)
                if (k >= 8 && (i > 4 || j > 4))
                    a[i][j] = a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 1] = 1, k -= 4;
        if (k % 4)
            a[1][1] = a[1][2] = a[2][1] = a[2][3] = a[3][2] = a[3][3] = 1, k -= 6;
        else
            for (int i = 1; i <= 4; i += 2)
                for (int j = 1; j <= 4; j += 2)
                    if (k >= 4)
                        a[i][j] = a[i + 1][j] = a[i][j + 1] = a[i + 1][j + 1] = 1, k -= 4;
        if (k)
            assert(k == 4), a[3][1] = a[4][1] = a[3][4] = a[4][4] = 1, k -= 4;
        assert(k == 0);
        cout << "Yes\n";
        for (int i = 1; i <= n; i++, cout << "\n")
            for (int j = 1; j <= n; j++)
                cout << a[i][j] << " ";
    }
}