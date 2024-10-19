#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 5e4 + 5;

int parent[MAXN];
int size[MAXN], p[MAXN], sum, cnt;

void init(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		parent[i] = i;
		size[i] = 1;
	}
}

int find(int x)
{
	if (x != parent[x])
	{
		parent[x] = find(parent[x]);
	}
	return parent[x];
}

void merge(int x, int y)
{
	int X = find(x);
	int Y = find(y);
	if (X != Y)
	{
		if (size[X] < size[Y])
		{
			swap(X, Y);
		}
		parent[Y] = X;
		size[X] += size[Y];
	}
}

struct Edge
{
	int u, v, w;
	bool operator<(const Edge &other) const
	{
		return w < other.w;
	}
};

vector<Edge> edges;

int main()
{

	ios::sync_with_stdio(false);
#ifndef LOCAL
#define NDEBUG
	cin.tie(0), cout.tie(0);
#define file(a)                               \
	FILE *FI = freopen(#a ".in", "r", stdin); \
	FI = freopen(#a ".out", "w", stdout)
	file(pmst);
#else
#ifdef LEN
	fprintf(stderr, "你的code声明了 %.3lf MB 的空间\n", abs(&be - &ed) / 1048576.0);
#endif
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
	// #include "../local.h"
#endif

	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> p[i];
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = i + 1; j <= n; ++j)
		{
			int w = abs(p[i] - p[j]) * abs(i - j);
			edges.push_back({i, j, w});
		}
	}
	sort(edges.begin(), edges.end());
	init(n);

	for (auto edge : edges)
	{
		if (find(edge.u) != find(edge.v))
		{
			merge(edge.u, edge.v);
			sum += edge.w;
			cnt++;
			if (cnt == n - 1)
				break;
		}
	}

	cout << sum << endl;

	return 0;
}
