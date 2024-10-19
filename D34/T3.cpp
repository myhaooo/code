#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define inf 0x3f3f3f3f
int a,b,u,v,w,ans,in;
il void pre(int &x)
{
	if(b)
	{
		x^=ans;
	}
}
struct XDS
{
	#define N 1100011
	#define M 500005
	int left[N<<1],right[N<<1],num[N<<1],A[N][2],B[N][2];//0 a+a 1 b+b
	multiset<int> msa[M][2],msb[M][2];
	il int lft(int x)
	{
		return x<<1;
	}
	il int iht(int x)
	{
		return x<<1|1;
	}
	il bool leaf(int x)
	{
		return left[x]==right[x];
	}
	il void pu(int x)
	{
		ri na[2][2],nb[2][2];
		if(leaf(lft(x)))
		{
			ri y=left[lft(x)];
			na[0][0]=*(msa[y][0].begin());
			na[0][1]=*(msa[y][1].begin());
			nb[0][0]=*(msb[y][0].begin());
			nb[0][1]=*(msb[y][1].begin());
		}
		else
		{
			na[0][0]=A[lft(x)][0];
			na[0][1]=A[lft(x)][1];
			nb[0][0]=B[lft(x)][0];
			nb[0][1]=B[lft(x)][1];
		}
		if(leaf(iht(x)))
		{
			ri y=right[iht(x)];
			na[1][0]=*(msa[y][0].begin());
			na[1][1]=*(msa[y][1].begin());
			nb[1][0]=*(msb[y][0].begin());
			nb[1][1]=*(msb[y][1].begin());
		}
		else
		{
			na[1][0]=A[iht(x)][0];
			na[1][1]=A[iht(x)][1];
			nb[1][0]=B[iht(x)][0];
			nb[1][1]=B[iht(x)][1];
		}
		A[x][0]=min(na[0][0],na[1][0]);
		A[x][1]=min(na[0][1],na[1][1]);
		B[x][0]=min(nb[0][0],nb[1][0]);
		B[x][1]=min(nb[0][1],nb[1][1]);
		num[x]=min(num[lft(x)],num[iht(x)]);
		num[x]=min(num[x],na[0][1]+na[1][0]);
		num[x]=min(num[x],nb[0][0]+nb[1][1]);
	}
	void make(int x,int lt,int rt)
	{
		left[x]=lt;
		right[x]=rt;
		num[x]=inf;
		if(lt==rt)
		{
			msa[lt][0].insert(inf);
			msa[lt][1].insert(inf);
			msb[lt][0].insert(inf);
			msb[lt][1].insert(inf);
			return;
		}
		A[x][0]=A[x][1]=B[x][0]=B[x][1]=inf;
		ri me=(lt+rt)>>1;
		make(lft(x),lt,me);
		make(iht(x),me+1,rt);
	}
	void add(int x,int pl,bool y,pair<int,int>z)
	{
		if(left[x]==right[x])
		{
			msa[pl][y].insert(z.first);
			msb[pl][y].insert(z.second);
			num[x]=min((*msa[pl][y].begin())+(*msa[pl][y^1].begin()),(*msb[pl][y].begin())+(*msb[pl][y^1].begin()));
			return;
		}
		ri me=(left[x]+right[x])>>1;
		if(pl<=me)
		{
			add(lft(x),pl,y,z);
		}
		else
		{
			add(iht(x),pl,y,z);
		}
		pu(x);
	}
	void del(int x,int pl,bool y,pair<int,int>z)
	{
		if(left[x]==right[x])
		{
			msa[pl][y].erase(msa[pl][y].find(z.first));
			msb[pl][y].erase(msb[pl][y].find(z.second));
			num[x]=min((*msa[pl][y].begin())+(*msa[pl][y^1].begin()),(*msb[pl][y].begin())+(*msb[pl][y^1].begin()));
			return;
		}
		ri me=(left[x]+right[x])>>1;
		if(pl<=me)
		{
			del(lft(x),pl,y,z);
		}
		else
		{
			del(iht(x),pl,y,z);
		}
		pu(x);
	}
	#undef N
	#undef M
}tree;
int main()
{
	scanf("%d%d",&a,&b);
	tree.make(1,1,500001);
	while(a--)
	{
		scanf("%d%d%d%d",&in,&u,&v,&w);
		pre(v),pre(w);
		if(in==1)
		{
			if(!u)
			{
				tree.add(1,v-w+250001,u,{v,w});
			}
			else
			{
				tree.add(1,w-v+250001,u,{v,w});
			}
		}
		else
		{
			if(!u)
			{
				tree.del(1,v-w+250001,u,{v,w});
			}
			else
			{
				tree.del(1,w-v+250001,u,{v,w});
			}
		}
		ans=tree.num[1];
		if(ans>500000)
		{
			ans=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
