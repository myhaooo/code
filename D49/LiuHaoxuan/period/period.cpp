#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("period.in","r",stdin);
	freopen("period.out","w",stdout);
    int n, m, q;
    cin >> n;

    string d;
    cin >> d;

   
    vector<string> S(n + 1);
    S[0] = "";  
    for (int i = 1; i <= n; ++i) {
        if (islower(d[i - 1])) {
            S[i] = d[i - 1] + S[i - 1]; 
        } else {
            S[i] = S[i - 1] + (char)tolower(d[i - 1]);  
        }
    }

    cin >> m;
    vector<int> p(m);
    bool no_sort=1;
    for (int i = 0; i < m; ++i) {
        cin >> p[i];
    }
    for (int i = 1; i < m; ++i) {
    	if(p[i]<p[i-1])	no_sort=0;
	}
	vector<int> ls;
    cin >> q;
    while (q--) {
        int k, l, r;
        cin >> k >> l >> r;
		string s=S[k];
		int len = s.size();
        int result = INT_MAX;
		ls.clear();
		for(int y=l-1;y<r;y++){
			ls.push_back(p[y]);
		}
		if(!no_sort) sort(ls.begin(),ls.end());
//		for(auto it : ls){
//			cout<<it<<" ";
//		}
//		putchar(10);
        for (auto it:ls) {
            bool ok = true;
        	for (int i = 0; i + it< len; ++i) {
          		if (s[i] != s[i + it]) {
             	   	ok = false;
             	   	break;
          			}
          		}	
        	if(ok) {
        		result=min(result,it);
        		if(m>5) break;	
			}
			
        }
        cout << (result>len?-1:result) << endl;
        continue;
    }

    return 0;
}

