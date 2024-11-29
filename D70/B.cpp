#include<bits/stdc++.h>
const int N=100010;
int n,m,id,ans,tr[N][26];
bool b[N]; 
char s[N];
std::priority_queue<int>q[N];
void dfs(int x,int d){
    for(int y,i=0;i<26;++i)
	if(y=tr[x][i]){
        dfs(y,d+1);
        while(q[y].size()){
            q[x].push(q[y].top());
            q[y].pop();
        } 
    }
    if(x&&!b[x]){
        ans-=q[x].top()-d;
        q[x].pop();
        q[x].push(d);
    } 
}
int main(){
    scanf("%d",&n);
    for(int x,i=1;i<=n;++i){
        x=0;
        scanf("%s",s+1);
        m=strlen(s+1);
        for(int j=1;j<=m;++j){
            if(!tr[x][s[j]-'a'])tr[x][s[j]-'a']=++id;
            x=tr[x][s[j]-'a']; 
        }
        b[x]=true;
        q[x].push(m);
        ans+=m;
    }
    dfs(0,0);
    printf("%d",ans);
}
