#include<iostream>
#include<algorithm>
#include<iomanip>

using namespace std;
typedef long long ll;

const int N = 1e5 + 1; const ll mx = 6e9;
int n, q, p[N], t[N], x[N], y, m2[31], m3[19];
bool g[N][31][19];
double f[N][31][19], ans;

int main(){
		freopen("ship.in","r",stdin);
	freopen("ship.out","w",stdout);
	cin >> n >> q;
	for(int i = 1; i <= n; i++){
		cin >> p[i] >> t[i] >> x[i];
	}
	m2[0] = m3[0] = 1;
	for(int i = 1; i < 19; i++) m2[i] = m2[i-1] * 2, m3[i] = m3[i-1] * 3;
	for(int i = 19; i < 31; i++) m2[i] = m2[i-1] * 2;
	g[0][0][0] = 1;
	for(int i = 1; i < N; i++){
		for(int j = 0; j < 31; j++){
			for(int k = 0; k < 19; k++){
				f[i][j][k] = 1e9;
			}
		}
	}
	for(int i = 1; i <= n; i++){
		int n1, n2;
		if(x[i] == 1) n1 = n2 = 0;
		else if(x[i] == 2) n1 = 1, n2 = 0;
		else if(x[i] == 3) n1 = 0, n2 = 1;
		else n1 = 2, n2 = 0;
		for(int w1 = 0; w1 < 31; w1++){
			for(int w2 = 0; w2 < 19; w2++){
				if((ll)m2[w1] * m3[w2] > mx) continue;
				if(n1 <= w1 && n2 <= w2 && g[i-1][w1-n1][w2-n2]){
					f[i][w1][w2] = min(f[i-1][w1-n1][w2-n2] + (p[i] - p[i-1]) * 1.0 / ((ll)m2[w1-n1] * m3[w2-n2]) + t[i], f[i][w1][w2]);
					g[i][w1][w2] = 1;
				}
				if(g[i-1][w1][w2]){
					f[i][w1][w2] = min(f[i-1][w1][w2] + (p[i] - p[i-1]) * 1.0 / ((ll)m2[w1] * m3[w2]), f[i][w1][w2]);
					g[i][w1][w2] = 1;
				}
			}
		}
	}
	while(q--){
		cin >> y;
		int fd = upper_bound(p, p + n + 1, y) - p - 1;
		ans = 1e9;
		for(int w1 = 0; w1 < 31; w1++){
			for(int w2 = 0; w2 < 19; w2++){
				if((ll)m2[w1] * m3[w2] > mx) continue;
				if(g[fd][w1][w2]){
					ans = min(ans, f[fd][w1][w2] + (y - p[fd]) * 1.0 / ((ll)m2[w1] * m3[w2]));
				}
			}
		}
		cout << fixed << setprecision(8) << ans << '\n'; //避免用科学计数法输出。 
	}
	return 0;
}
