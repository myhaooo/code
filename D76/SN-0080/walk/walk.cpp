
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,a[11],c[1000100],d[1000100],dw[11],up[11],len[11],res,qwq[11],tms[20],lim,val[20][20],mal[20][20],lam[20][20],mil[20];
vector<int>v,u;
bool cheimp(){
	for(int i=0;i<m;i++)if(v[i])return false;
	for(int i=0;i<m;i++)if(dw[i]>up[i])return false;
	return true;
}
int ksm(int x,int y=mod-2){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)z=1ll*z*x%mod;
	return z; 
}
void Involution(int *arr,int &sz,int slop,int cons){
//	printf("%d %d\n",slop,cons);
	for(int i=sz;i>=0;i--){
		(arr[i+1]+=1ll*arr[i]*slop%mod)%=mod;
		arr[i]=1ll*cons*arr[i]%mod;
	}
	if(arr[sz+1])sz++;
}
void Revolution(int *arr,int &sz,int slop,int cons){
	if(!cons){
		for(int i=0;i<sz;i++)arr[i]=arr[i+1];
		arr[sz]=0;
	}else{
		cons=ksm(cons);
		for(int i=0;i<sz;i++){
			arr[i]=1ll*arr[i]*cons%mod;
			(arr[i+1]+=mod-1ll*arr[i]*slop%mod)%=mod;
		}
	}
	sz--;
}
int Calc(int *arr,int sz,int x){
	int ret=0;
	for(int i=0,j=1;i<=sz;i++,j=1ll*j*x%mod)(ret+=1ll*j*arr[i]%mod)%=mod;
	return ret;
}
void Lagrange(){
	for(int i=0;i<=m;i++){
		for(int j=1;j<=i+1;j++)val[i][j]=(val[i][j-1]+ksm(j,i))%mod;
		mal[i][0]=1,mil[i]=0;
		for(int j=0;j<=i+1;j++)Involution(mal[i],mil[i],1,(mod-j)%mod);
		for(int j=0;j<=i+1;j++){
			Revolution(mal[i],mil[i],1,(mod-j)%mod);
			int lambda=val[i][j];
			for(int k=0;k<=mil[i];k++)if(k!=j)lambda=1ll*lambda*ksm((j-k+mod)%mod)%mod;
			for(int k=0;k<=mil[i];k++)(lam[i][k]+=1ll*mal[i][k]*lambda%mod)%=mod;
			Involution(mal[i],mil[i],1,(mod-j)%mod);
		}
	}
}
int main(){
//	freopen("walk.in","r",stdin);
//	freopen("walk.out","w",stdout);
	scanf("%d%d",&n,&m);
	Lagrange();
	for(int i=0;i<m;i++)scanf("%d",&a[i]),up[i]=a[i]-1,dw[i]=0,len[i]=a[i];
	v.resize(m);
	for(int i=1,x,y;i<=n;i++){
		scanf("%d%d",&x,&y),x--,v[x]+=y;
		c[i]=x,d[i]=y;
		if(v[x]>=0)up[x]=min(up[x],a[x]-v[x]-1);
		else dw[x]=max(dw[x],-v[x]);
	}
	if(cheimp()){puts("-1");return 0;}
	for(int i=0;i<m;i++)up[i]=a[i]-1,dw[i]=0,len[i]=a[i];
	u.resize(m);
	for(int i=1;i<=2*n;i++){
		if(i>n)c[i]=c[i-n],d[i]=d[i-n];
		u[c[i]]+=d[i];
		if(u[c[i]]>=0)up[c[i]]=min(up[c[i]],a[c[i]]-u[c[i]]-1);
		else dw[c[i]]=max(dw[c[i]],-u[c[i]]);
		int TTT=max(0,up[c[i]]-dw[c[i]]+1);
		if(TTT<len[c[i]]){
			bool ok=true;
			int tmp=i;
			for(int j=0;j<m;j++){
				if(j==c[i])continue;
				if(len[j]<=0){tmp=ok=0;break;}
				tmp=1ll*tmp*len[j]%mod;
			}
			(res+=tmp)%=mod;
			if(i>n){
				for(int j=0;j<=lim;j++)tms[j]=0;
				tms[1]=n,tms[0]=i,lim=1;
				for(int j=0;j<m;j++){
					if(j==c[i])continue;
					Involution(tms,lim,(mod-abs(v[j]))%mod,len[j]);
				}
				int x=0x3f3f3f3f;
				for(int j=0;j<m;j++){
					if(len[j]<=0){x=0;continue;}
					if(v[j])x=min(x,(len[j]-1)/abs(v[j]));
				}
				for(int j=0;j<=lim;j++)(res+=1ll*tms[j]*Calc(lam[j],mil[j]-1,x)%mod)%=mod;
			}
			len[c[i]]=TTT;
		}
	}
	printf("%d\n",res);
	return 0;
}
