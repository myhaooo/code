#include <iostream>
using namespace std;

const int kN = 3e5 + 1, kV = 1e6;

int n, m, x[kN], z;  // z 为原点位置
pair<int, int> p[kV + 1];       // 每个点的标记，first 存映射到那个点（-1 表示清零），second 存映射时间戳
pair<int, int> f[kV + 1];       // 用于记忆化
bool w;              // 原点在区间左边还是右边（0 为左边，1 为右边）

pair<int, int> G(int x) {
    if (f[x].second) {  // 记忆化
        return f[x];
    }
    if (p[x].first == -1) {            
        return f[x] = {0, p[x].second};
    }
    if (!p[x].first) {           
        return f[x] = {x - z, m};
    }
    pair<int, int> v = G(p[x].first);                     
    return f[x] = {-v.first, max(p[x].second, v.second)}; 
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }
    for (int d, i = 1, l = 1, r = kV; i <= m; ++i) {  // 处理每次操作，[l,r] 为当前区间
        cin >> d;
        z += d * (w ? -1 : 1);
        if (z < l) {          
            w = 0;            
        } 
        else if (z > r) {     
            w = 1;
        } 
        else {
            p[z] = {-1, i};      
            if (z - l > r - z) { 
                for (int j = z + 1; j <= r; ++j) {
                  p[j] = {z - (j - z), i};  
                }
                w = 1, r = z - 1;  // 缩小区间
            } else {         
                for (int j = l; j < z; ++j) {
                  p[j] = {z + (z - j), i};
                }
                w = 0, l = z + 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        pair<int, int> y = G(x[i]);            
        if (y.first) {                         
            cout << "No " << y.first << '\n';  
        } else {                               
            cout << "Yes " << y.second << '\n';
        }
    }
    return 0;
}