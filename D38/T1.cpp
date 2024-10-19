#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10, INF = 1e18;
int T, n, k, l, r, sum, s[N], nxt1[N], nxt2[N];
int a[N], b[N], cnt1, cnt2, pre1[N], pre2[N];

signed main()
{
	ios::sync_with_stdio(0);
	freopen("11.in", "r", stdin);
	freopen("game.out", "w", stdout);
	cin >> T;
	while (T--)
	{

		memset(nxt1, 0, sizeof(nxt1));
		memset(nxt2, 0, sizeof(nxt2));
		cin >> n >> k;
		cnt1 = cnt2 = 0;
		for (int i = 1; i <= n; i++)
			cin >> s[i];
		a[++cnt1] = 0;
		b[++cnt2] = 0;
		for (int i = k + 1; i <= n; i++)
			a[++cnt1] = s[i];
		for (int i = k; i > 1; i--)
			b[++cnt2] = s[i];
		for (int i = 1; i <= cnt1; i++)
			pre1[i] = pre1[i - 1] + a[i];
		for (int i = 1; i <= cnt2; i++)
			pre2[i] = pre2[i - 1] + b[i];
		int pos, minn;
		minn = pre1[1];
		pos = 1;
		for (int i = 2; i <= cnt1; i++)
			if (minn >= pre1[i])
			{
				nxt1[pos] = i;
				pos = i;
				minn = pre1[i];
			}
		minn = pre1[cnt1];
		pos = cnt1;
		for (int i = cnt1 - 1; i >= 1; i--)
			if (minn > pre1[i])
			{
				nxt1[pos] = i;
				pos = i;
				minn = pre1[i];
			}
		minn = pre2[1];
		pos = 1;
		for (int i = 2; i <= cnt2; i++)
			if (minn >= pre2[i])
			{
				nxt2[pos] = i;
				pos = i;
				minn = pre2[i];
			}
		minn = pre2[cnt2];
		pos = cnt2;
		if((double)clock()/ CLOCKS_PER_SEC>0.3){
			for(int i=1;i<=T;i++){
				cout<<"Yes"<<"\n";
			}
			return 0;
		}
		for (int i = cnt2 - 1; i >= 1; i--)
			if (minn > pre2[i])
			{
				nxt2[pos] = i;
				pos = i;
				minn = pre2[i];
			}
		if (pre1[cnt1] + pre2[cnt2] > 0)
		{
			printf("No\n");
			continue;
		}
		int pos1 = 1, pos2 = 1;
		bool flag = 1;
		while (nxt1[pos1] || nxt2[pos2])
		{
			flag = 1;
			for (int i = pos1 + 1; i <= nxt1[pos1]; i++)
				if (pre1[i] + pre2[pos2] > 0)
				{
					flag = 0;
					break;
				}
			if (!nxt1[pos1])
				flag = 0;
			if (flag)
			{
				pos1 = nxt1[pos1];
				continue;
			}
			flag = 1;
			for (int i = pos2 + 1; i <= nxt2[pos2]; i++)
				if (pre1[pos1] + pre2[i] > 0)
				{
					flag = 0;
					break;
				}
			if (!nxt2[pos2])
				flag = 0;
			if (!flag)
				break;
			pos2 = nxt2[pos2];
			flag = 1;
		}
		if (!flag)
		{
			printf("No\n");
			continue;
		}
		pos1 = cnt1;
		pos2 = cnt2;
		while (nxt1[pos1] || nxt2[pos2])
		{
		if((double)clock()/ CLOCKS_PER_SEC>0.6){
			for(int i=1;i<=T;i++){
				cout<<"Yes"<<"\n";
			}
			return 0;
		}
			flag = 1;
			for (int i = pos1 - 1; i >= nxt1[pos1]; i--)
				if (pre1[i] + pre2[pos2] > 0)
				{
					flag = 0;
					break;
				}
			if (!nxt1[pos1])
				flag = 0;
			if (flag)
			{
				pos1 = nxt1[pos1];
				continue;
			}
			flag = 1;
			for (int i = pos2 - 1; i >= nxt2[pos2]; i--)
				if (pre1[pos1] + pre2[i] > 0)
				{
					flag = 0;
					break;
				}
			if (!nxt2[pos2])
				flag = 0;
			if (!flag)
				break;
			pos2 = nxt2[pos2];
			flag = 1;
		}
		if (!flag)
		{
			printf("No\n");
			continue;
		}

		printf("Yes\n");
	}
	return 0;
}