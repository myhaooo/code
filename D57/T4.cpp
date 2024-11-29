//9312
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 10;
const int inf = 0x3f3f3f3f;
int A[maxn], B[maxn], C[maxn], P[maxn];
int H[maxn];
int f[maxn][maxn];
int ordL[maxn], ordR[maxn];
int up[maxn][2], dw[maxn][2];
priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> ql[maxn], qr[maxn];
int n, k;
int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)	scanf("%d", H + i);
	for(int i = 1; i <= k; i++)	scanf("%d%d%d%d", P + i, C + i, A + i, B + i);
	for(int i = 1; i <= k; i++) ordL[i] = ordR[i] = i;
	sort(ordL + 1, ordL + k + 1, [](int x, int y){return A[x] < A[y];});
	sort(ordR + 1, ordR + k + 1, [](int x, int y){return B[x] > B[y];});
	for(int i = 1; i <= k; i++){
		for(up[i][0] = P[i]; up[i][0] && H[up[i][0]] <= B[i]; up[i][0]--);
		for(up[i][1] = P[i]; up[i][1] <= n && H[up[i][1]] <= B[i]; up[i][1]++);
		for(dw[i][0] = P[i]; dw[i][0] && H[dw[i][0]] >= A[i]; dw[i][0]--);
		for(dw[i][1] = P[i]; dw[i][1] <= n && H[dw[i][1]] >= A[i]; dw[i][1]++);
	}
	for(int i = 1; i <= k; i++){
		for(int j = 1; j <= k; j++){
			int u = ordL[i];
			int v = ordR[j];
			f[u][v] = inf;
			int l = max(dw[u][0], up[v][0]), r = min(dw[u][1], up[v][1]);
			if(P[u] <= l || P[u] >= r || P[v] <= l || P[v] >= r || (A[u] > A[v] && B[u] > B[v])) continue;
			if(A[u] == 1 && B[v] == n) f[u][v] = 0;
			else if(A[u] > A[v])f[u][v] = f[v][v];
			else if(B[v] < B[u])f[u][v] = f[u][u];
			else{
				while(!ql[u].empty() && (P[ql[u].top().second] <= l || P[ql[u].top().second] >= r || A[ql[u].top().second] > B[v] || B[ql[u].top().second] < A[u]))ql[u].pop();
				if(!ql[u].empty())
					f[u][v] = min(f[u][v], ql[u].top().first);
				while(!qr[v].empty() && (P[qr[v].top().second] <= l || P[qr[v].top().second] >= r || A[qr[v].top().second] > B[v] || B[qr[v].top().second] < A[u]))qr[v].pop();
				if(!qr[v].empty())
				 	f[u][v] = min(f[u][v], qr[v].top().first);
				
			}
			if(f[u][v] < inf){
				ql[u].emplace(f[u][v] + C[v], v);
				qr[v].emplace(f[u][v] + C[u], u);
			}
		}
	}
	for(int i = 1; i <= k; i++){
		printf("%d\n", (f[i][i] >= inf) ? -1 : f[i][i] + C[i]);
	}
}