#include <bits/stdc++.h>
#include <ctime>
#include <random>
using namespace std;

void work(FILE *fp, int t)//t表示这是第几组数据 
{
	mt19937 myrand(time(0));
    int n=myrand()%1000000;
	fprintf(fp, "%d\n", n);//用这个输出你想造的数据即可 
    for(int i=1;i<=n;i++){
        fprintf(fp, "%d ", myrand()%1000000);

    }

	/*balabala......*/
}

int main()//下面这部分改个文件名字就行，这里用的名字是A 
{

  
	char s[100];
	for (int i = 1; i <= 100; i++)
	{
		sprintf(s, "data%d.in", i);
		FILE *fp = fopen(s, "w");
		work(fp, i);
		fclose(fp);
		fp = 0;
		sprintf(s, "std.exe < data%d.in > data%d.out", i, i);//std.exe是标程的exe 
		system(s);
	}
	return 0;
}