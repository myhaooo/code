#include <bits/stdc++.h>
#define fre(x) freopen( #x ".in", "r", stdin ), freopen( #x ".out", "w", stdout )
using namespace std; typedef long long ll; typedef unsigned long long ull; typedef double db; typedef pair <int,int> pii;

const int N = 1e3 + 5, M = 50 + 5, Mod = 998244353, inv = 205817851;

mt19937 mt( (ull)(&N) );
int Rand ( int l, int r ) { return uniform_int_distribution<int>(l,r)(mt); }

int n, m, W[M<<1]; pii F[N][M], G[N+M][M];

int Pow ( int x, int y ) { int res = 1; for( ; y; y >>= 1, x = 1LL * x * x % Mod ) if( y&1 ) res = 1LL * res * x % Mod; return res; }

int Inv ( int x ) { return Pow( x, Mod - 2 ); }

int Add ( int x, int y ) { return x + y >= Mod ? x + y - Mod : x + y; }

pii Add ( const pii& a, const pii& b ) { return make_pair( Add( a.first, b.first ), Add( a.second, b.second ) ); }

pii Mul ( const pii& a, const pii& b ) { return make_pair( 1LL * a.first * b.first % Mod, ( 1LL * a.first * b.second + 1LL * b.first * a.second ) % Mod ); }

void Solve ()
{
	cin >> n >> m;
	for( int i = -m; i <= m; ++i ) cin >> W[i+m], W[i+m] = 1LL * W[i+m] * inv % Mod;
	
	for( int i = 0; i < n; ++i )
	{
		static pii T[M<<1];

		for( int j = -m; j <= m; ++j ) T[j+m] = make_pair( 0, 0 );
		for( int j = -m; j <= m; ++j ) T[ max( -i, j ) + m ] = Add( T[ max( -i, j ) + m ], make_pair( W[j+m], W[j+m] ) );

		for( int j = -m; j <  0; ++j ) for( int k = 1; k <= m; ++k ) T[ j + k + m ] = Add( T[ j + k + m ], Mul( T[j+m], F[i+j][k] ) );
		
		int tmp = Inv( ( 1 - T[m].first + Mod ) % Mod );

		for( int j =  1; j <= m; ++j )
			F[i][j].first = 1LL * T[j+m].first * tmp % Mod, F[i][j].second = 1LL * ( T[j+m].second + 1LL * F[i][j].first * T[m].second ) % Mod * tmp % Mod;
	}

	G[0][m] = make_pair( 1, 0 );
	for( int i = 0; i <  n; ++i ) for( int j = max( -i, -m ); j <= 0; ++j ) for( int k = 1; k <= m; ++k )
		if( k + j <= 0 ) G[i][k+j+m] = Add( G[i][k+j+m], Mul( G[i][j+m], F[i+j][k] ) ); else G[i+k+j][-k-j+m] = Add( G[i+k+j][-k-j+m], Mul( G[i][j+m], F[i+j][k] ) );

	int res = 0;
	for( int i = n; i <= n + m; ++i ) for( int j = max( -i, -m ); j <= 0; ++j ) res = Add( res, G[i][j+m].second );
	cout << res << "\n";
}

signed main ()
{
//	fre(x);
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0); Solve(); return 0;
}

