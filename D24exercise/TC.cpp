#include<bits/stdc++.h>
using namespace std;
const int N=2e5+6;

int n,a[N],f;
vector<int> e[N],o;
priority_queue<int> q[N];

void merge(int x,int y){
    if(q[x].size()<q[y].size())swap(q[x],q[y]);
    while(!q[y].empty()){
        o.push_back(max(q[x].top(),q[y].top()));
        q[x].pop(),q[y].pop();
    }
    while (!o.empty())
    {
        q[x].push(o.back()),o.pop_back();
    }
    
}


void dfs(int x){
    int len=e[x].size();
    for(int i=0;i<len;i++){
        dfs(e[x][i]),merge(x,e[x][i]);
    }
    q[x].push(a[x]);
}


signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=2;i<=n;i++){
        cin>>f;
        e[f].push_back(i);
    }
    dfs(1);
    long long ans=0;
    while(!q[1].empty())ans+=q[1].top(),q[1].pop();
    cout<<ans<<endl;
}