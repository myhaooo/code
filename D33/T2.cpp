#include<bits/stdc++.h>
using namespace std;
int n, Q, M, a, b, x, y, z, tw, th, na, nb, l, r, mid, lx, rx, ly, ry;
int w[2010], h[2010], sw[2010], sh[2010], ans, f[2010][2010], g[2010][2010], u[2010][2010], v[2010][2010];
struct node
{
	int x, y, z;
} s[2010];
int read(int &x)
{
	x = 0;
	int w = 1;
	char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-')
			w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x *= w;
}
int cmp(node p, node q) { return p.x < q.x || q.x == p.x && q.y < p.y; }
int ksm(int x, int k)
{
	int s = 1;
	for (; k > 0; k >>= 1, x = 
            1ll * x * x % M)
		if (k & 1)
			s = 
            1ll * s * x % M;
	return s;
}
int main()
{

	read(n), read(Q), read(tw), read(th), read(M), read(a), read(b);
	for (int i = 1; i <= n; i++)
	{
		read(z);
		s[i] = node{read(x), read(y), z};
		w[i] = x, h[i] = y;
	}
	sort(s + 1, s + 1 + n, cmp);
	sort(w + 1, w + 1 + n), sort(h + 1, h + 1 + n);
	tw = th = 0;
	for (int i = 1; i <= n; i++)
		if (w[i] != w[i - 1])
		{
			w[++tw] = w[i];
			sw[tw] = ksm(a, w[tw] - w[tw - 1]);
		}
	for (int i = 1; i <= n; i++)
		if (h[i] != h[i - 1])
		{
			h[++th] = h[i];
			sh[th] = ksm(b, h[th] - h[th - 1]);
		}
	for (int i = 1; i <= n; i++)
	{
		for (l = 1, r = tw, mid = l + r >> 1; l <= r; mid = l + r >> 1)
			(s[i].x >= w[mid]) ? l = (x = mid) + 1 : r = mid - 1;
		for (l = 1, r = th, mid = l + r >> 1; l <= r; mid = l + r >> 1)
			(s[i].y >= h[mid]) ? l = (y = mid) + 1 : r = mid - 1;
		f[x][y] = g[x][y] = u[x][y] = v[x][y] = s[i].z;
	}
	for (int i = 1; i <= tw; i++)
	{
		for (int j = 1; j <= th; j++)
		{
			na = sw[i], nb = sh[j];
			f[i][j] = 
            1ll * (f[i][j] + 
            1ll * f[i - 1][j] * na % M) % M;
			f[i][j] = 
            1ll * (f[i][j] + 
            1ll * f[i][j - 1] * nb % M) % M;
			f[i][j] = 
            1ll * (f[i][j] - 
            1ll * f[i - 1][j - 1] * na % M * nb % M + M) % M;
		}
		for (int j = th; j >= 1; j--)
		{
			na = sw[i], nb = sh[j + 1];
			v[i][j] = 1ll * (v[i][j] + 
            1ll * v[i - 1][j] * na % M) % M;
			v[i][j] = 1ll * (v[i][j] + 
            1ll * v[i][j + 1] * nb % M) % M;
			v[i][j] = 1ll * (v[i][j] - 
            1ll * v[i - 1][j + 1] * na % M * nb % M + M) % M;
		}
	}
	for (int i = tw; i >= 1; i--)
	{
		for (int j = 1; j <= th; j++)
		{
			na = sw[i + 1], nb = sh[j];
			u[i][j] = 1ll * (u[i][j] + 
            1ll * u[i + 1][j] * na % M) % M;
			u[i][j] = 
            1ll * (u[i][j] + 
            1ll * u[i][j - 1] * nb % M) % M;
			u[i][j] = 
            1ll * (u[i][j] - 
            1ll * u[i + 1][j - 1] * na % M * nb % M + M) % M;
		}
		for (int j = th; j >= 1; j--)
		{
			na = sw[i + 1], nb = sh[j + 1];
			g[i][j] = 1ll * (g[i][j] + 
            1ll * g[i + 1][j] * na % M) % M;
			g[i][j] = 
            1ll * (g[i][j] + 
            1ll * g[i][j + 1] * nb % M) % M;
			g[i][j] = 
            1ll * (g[i][j] - 
            1ll * g[i + 1][j + 1] * na % M * nb % M + M) % M;
		}
	}
	for (int i = 1; i <= Q; i++)
	{
		read(x), read(y);
		ans = lx = ly = 0, rx = tw + 1, ry = th + 1;
		for (l = 1, r = tw, mid = l + r >> 1; l <= r; mid = l + r >> 1)
			(x >= w[mid]) ? l = (lx = mid) + 1 : r = mid - 1;
		for (l = 1, r = tw, mid = l + r >> 1; l <= r; mid = l + r >> 1)
			(x <= w[mid]) ? r = (rx = mid) - 1 : l = mid + 1;
		for (l = 1, r = th, mid = l + r >> 1; l <= r; mid = l + r >> 1)
			(y >= h[mid]) ? l = (ly = mid) + 1 : r = mid - 1;
		for (l = 1, r = th, mid = l + r >> 1; l <= r; mid = l + r >> 1)
			(y <= h[mid]) ? r = (ry = mid) - 1 : l = mid + 1;
		if (lx == rx && ly == ry)
		{
			ans = 1ll * (f[lx][ly] + 
            1ll * g[lx + 1][ly + 1] * sw[lx + 1] % M * sh[ly + 1] % M + 
            1ll * u[lx + 1][ly] * sw[lx + 1] % M + 
            1ll * v[lx][ly + 1] * sh[ly + 1] % M) % M;
		}
		else if (lx == rx && ly != ry)
		{
			int lf = ksm(b, y - h[ly]), rg = ksm(b, h[ry] - y);
			ans = 1ll * (
            1ll * f[lx][ly] * lf % M + 
            1ll * v[lx][ry] * rg % M + 
            1ll * u[lx + 1][ly] * sw[lx + 1] % M * lf % M + 
            1ll * g[lx + 1][ly + 1] * sw[lx + 1] % M * rg % M) % M;
		}
		else if (lx != rx && ly == ry)
		{
			int up = ksm(a, x - w[lx]), dn = ksm(a, w[rx] - x);ans = 
            1ll * (
            1ll * f[lx][ly] * up % M + 
            1ll * v[lx][ly + 1] * sh[ly + 1] % M * up % M + 
            1ll * u[rx][ly] * dn % M + 
            1ll * g[rx][ly + 1] * sh[ly + 1] % M * dn % M) % M;
		}
		else
		{
			int up = ksm(a, x - w[lx]), lf = ksm(b, y - h[ly]), dn = ksm(a, w[rx] - x), rg = ksm(b, h[ry] - y);
			ans = 1ll * (
            1ll * f[lx][ly] * up % M * lf % M + 
            1ll * v[lx][ry] * up % M * rg % M + 
            1ll * u[rx][ly] * dn % M * lf % M + 
            1ll * g[rx][ry] * dn % M * rg % M) % M;
		}
		printf("%d\n", ans);
	}
}
