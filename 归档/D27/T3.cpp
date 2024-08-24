#include<bits/stdc++.h>
using namespace std;
const int N=2005;

struct Edge{
	int vet,nxt;
}e[N<<1];

int n,B,Top=0,cnt=0,edge=0,head[N];
int sta[N],Belong[N],Root[N];

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)) { x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline void add(int x,int y){
	e[++edge].vet=y;
	e[edge].nxt=head[x];
	head[x]=edge;
}

inline void dfs(int x,int fa){
	int rec=Top; 		//记录栈此时的状态，类似的思想可以在可撤销并查集中见到（可能吧）
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].vet;
		if (v==fa) continue;
		dfs(v,x);
		if (Top-rec>=B){		
			Root[++cnt]=x;
			while (Top!=rec)	
				Belong[sta[Top--]]=cnt;
		}
	}
	sta[++Top]=x;		
}

int main(){
	n=read(),B=read();
	for (int i=1;i<=n-1;i++){
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	if (cnt==0) Root[++cnt]=1;		
	while (Top!=0) Belong[sta[Top--]]=cnt;	
	printf("%d\n",cnt);
	for (int i=1;i<=n;i++)
		printf("%d ",Belong[i]);
	putchar(10);
	for (int i=1;i<=cnt;i++)
		printf("%d ",Root[i]);
	return 0;
}