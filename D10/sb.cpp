#include <bits\stdc++.h>
using namespace std;
#define clear(a) memset(a, 0, sizeof(a))
#define ll long long
#ifdef linux
    #define getchar   getchar_unlocked
    #define getchar() getchar_unlocked()
    #define putchar   putchar_unlocked
    #define putchar() putchar_unlocked()
#endif
#ifdef _UNIX
    #define getchar   getchar_unlocked
    #define getchar() getchar_unlocked()
    #define putchar   putchar_unlocked
    #define putchar() putchar_unlocked()
#endif
#ifdef _WIN32
    #define getchar() _getchar_nolock()
    #define getchar   _getchar_nolock
    #define putchar() _putchar_nolock()
    #define putchar   _putchar_nolock
#endif


const int N = (int)1e5 + 10;
short a[N];
unsigned char t[N];
int b[N];
long long cnt;
inline int read()
{
	int w{1},x=0;
	char c=getchar();
	while(c<'0'||c>'9'){if(c == '-')w=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return w * x;
}
void update(int l, int r)
{
    int t1 = a[r];int t2 = t[r];
    memmove(a+l+1,a+l,(r - l) * sizeof(short));
    memmove(t+l+1,t+l,(r - l) * sizeof(unsigned char));
    a[l] = t1;
    t[l] = t2;
}
 
int query(int l, int r, int k)
{
    if (r - l <= N / 2)
    {
        cnt += (r - l + 1);
        int ans = 0;
        for (int i = l; i <= r; ++i)
            ans += ((a[i] << 8) + t[i] == k);
        return ans;
    }
    else
    {
        cnt += l + N - r;
        int ans = b[k];
        for (int i = 0; i < l; i++)
            ans -= ((a[i] << 8) + t[i] == k);
        for (int i = r + 1; i < N; i++)
            ans -= ((a[i] << 8) + t[i] == k);
        return ans;
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    #ifndef LOCAL
        #define NDEBUG
        cin.tie(0),cout.tie(0);
    #else
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
        #include "../local.h"
    #endif
    int n = read();
    int q, v;
    for (int i=0; i < n; i++)
    {
    	v = read();b[v]++;
        a[i] = v >> 8;
        t[i] = v & 255;
    }
	q = read();
 
    int lastans=0;
    for (int i = 0; i < q; i++)
    {
        int op, l, r, k;
        op = read();
 
        if (op == 1)
        {
            l = read(),r = read();
            l = (l + lastans - 1) % n;
            r = (r + lastans - 1) % n;
            if (l > r)swap(l, r);
            update(l, r);
        }
        else
        {
            l = read(),r = read(),k = read();
            l = (l + lastans - 1) % n;
            r = (r + lastans - 1) % n;
            k = (k + lastans - 1) % n + 1;
            if (l > r) swap(l, r) ;
            lastans = query(l, r, k);
            cout<<lastans<<"\n";
        }
    }
}
 