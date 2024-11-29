#include<bits/stdc++.h>
//#define int long long
const int N=1e7+10;
int n,len,mod,num,num1,num2,cnt,pri[N],s[N],s2[N];
int sta[N];
int sum,sum1,sum2,vis[N];
bitset<18*N> jud;
double ans;
void Get_Prime()
{
	for(int i=2;cnt<n;i++)
	{
		if(!jud[i])	pri[++cnt]=i;
		for(int j=1;j<=cnt&&pri[j]*i<=18*n;j++){
			jud[pri[j]*i]=true;
			if(i%pri[j]==0)break;
		}
	}
}
signed main()
{
	cin>>n>>len>>mod;
	Get_Prime();
	for(int i=1;i<=n;i++)
		s[i]=1ll*i*pri[i]%mod;
	for(int i=1;i<=n;i++)
		s2[i]=s[i]+s[i/10+1];
	for(int i=1;i<=len;i++)
		sta[i]=s2[i],vis[s2[i]]++;
	sort(sta+1,sta+len+1);
	num=len/2;
	if(len&1)	ans+=sta[num+1]*1.0;
	else	ans+=(1.0*sta[num]+1.0*sta[num+1])/2.0;
	num=sta[len/2+1];
	num1=sta[len/2],num2=sta[len/2+1];
	if(len&1)
		for(int i=0;i<=num;i++)
			sum+=vis[i];
	else
	{
		for(int i=0;i<=num2;i++)
			sum1+=vis[i];
		for(int i=0;i<=num1;i++)
			sum2+=vis[i];
	}
	for(int l=2;l<=n-len+1;l++)
	{
		int r=l+len-1;
		if(len&1)
		{
			vis[s2[l-1]]--;
			if(s2[l-1]<=num)	sum--;
			vis[s2[r]]++;
			if(s2[r]<=num)	sum++;
			while(1)
			{			
				if(sum-vis[num]>len/2)	sum-=vis[num],num--;
				else	if(len-sum>len/2)	num++,sum+=vis[num];
				if(sum-vis[num]<=len/2&&len-sum<=len/2)
					break;
			}
			ans+=num;
		}
		else
		{
			vis[s2[l-1]]--;
			vis[s2[r]]++;
			if(s2[l-1]<=num1)	sum1--;
			if(s2[r]<=num1)	sum1++;
			if(s2[l-1]<=num2)	sum2--;
			if(s2[r]<=num2)	sum2++;
			while(sum1-vis[num1]>=len/2)	sum1-=vis[num1],num1--;
			while(sum1+vis[num1+1]<len/2)	sum1+=vis[num1+1],num1++;
			if(sum1<len/2)	num1++,sum1+=vis[num1];
			while(sum2-vis[num2]>=len/2+1)	sum2-=vis[num2],num2--;
			while(sum2+vis[num2+1]<len/2+1)	sum2+=vis[num2+1],num2++;
			if(sum2<len/2+1)	num2++,sum2+=vis[num2];
			ans+=(1.0*num1+1.0*num2)/2.0;
		}
	}
	printf("%.1lf",ans);
	return 0;
}
