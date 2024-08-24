#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int Your=6,Other=6;
string daojuname[]={"放大镜","手铐","小刀","烟","饮料"};
double Yourmoney;

int shi,kong;
int q[10],qlen;//1 实 2 空 
int Rand(int x,int y){
	int A=rand(),B=rand();
	return A*1ll*B%(y-x+1)+x;
}
int T;//ou->you
int daojulen;
int daoju[10];
int daojulen1;
int daoju1[10];
void build_gun(){
	kong=Rand(1,4);
	shi=Rand(1,4);
	qlen=0;
	printf("%d发实弹,%d发空弹\n",shi,kong);
	int a1=kong,a2=shi;
	for(int i=1;i<=kong+shi;i++){
        Sleep(50);
		int sum=Rand(1,a1+a2);
		if(sum<=a1){
			a1--;
			q[++qlen]=2;
		}else{
			a2--;
			q[++qlen]=1;
		}
	}
	int maxn=min(4,8-daojulen);
	printf("小菜鸡获得了%d个道具:\n",maxn);
	daojulen+=maxn;
	for(int i=1;i<=maxn;i++){
        Sleep(50);
		int kkk=Rand(0,4);
		daoju[kkk]++;
		cout<<daojuname[kkk];
		if(i!=maxn){
			printf(",");
		}
	}
	printf("\n");
	maxn=min(4,8-daojulen1);
	printf("**恶魔获得了%d个道具:\n",maxn);
	daojulen1+=maxn;
	for(int i=1;i<=maxn;i++){
		int kkk=Rand(0,4);
		daoju1[kkk]++;
		cout<<daojuname[kkk];
		if(i!=maxn){
			printf(",");
		}
	}
	printf("\n");
	system("pause");
	system("cls");
}
void IsOver(){
	if(Your<=0){
		printf("小菜鸡输了\n");
		system("pause");
		exit(0);
	}
	if(Other<=0){
		printf("小菜鸡赢了\n你获得了奖金$%.2lf\n",Yourmoney);
		system("pause");
		exit(0);
	}
}
void wait(){
	for(int i=1;i<=3;i++){
		Sleep(500);
		printf(".");
	}
	Sleep(500);
}
int Hurt=1;
int shoukao_you;
void Timeyou(){
	int x;
	while(1){
		printf("小菜鸡的生命:%d/6\n**恶魔生命:%d/6\n",Your,Other);
		printf("剩余实弹数:%d    剩余空弹数:%d\n",shi,kong);
		printf("小菜鸡现在拥有的道具:\n");
		for(int i=0;i<=4;i++){
			cout<<daojuname[i];
			printf("%d",daoju[i]);
			printf("个");
			if(i!=4){
				printf(",");
			}
		}
		printf("\n");
		printf("**恶魔现在拥有的道具:\n");
		for(int i=0;i<=4;i++){
			cout<<daojuname[i];
			printf("%d",daoju1[i]);
			printf("个");
			if(i!=4){
				printf(",");
			}
		}
		printf("\n");
		printf("现在是小菜鸡的回合\n");
		printf("小菜鸡要\n1.向**恶魔开枪\n2.向自己开枪\n");
		for(int i=0;i<=4;i++){
			printf("%d.使用",i+3);
			cout<<daojuname[i]<<'\n';
		}
		scanf("%d",&x);
		if(1<=x&&x<=7){
			break;
		}
		printf("输入不合法，你像个**\n");
		Sleep(1145);
		system("cls");
	}
	if(x==1){
		printf("小菜鸡决定向**恶魔开枪");
		T++;
		wait();
		if(q[qlen]==2){
			Yourmoney+=(double)(2000.0*(Hurt*1.0)*(1+(double)(shi)*1.0/(double)(shi+kong)));
			kong--;
			qlen--;
			Hurt=1;
			printf("是空弹\n");
			if(shoukao_you==1){
				shoukao_you=0;
				printf("因为小菜鸡使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}else{
//          printf("((%lf))\n",Yourmoney);
			Yourmoney+=(double)(5000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
//          printf("{{%lf}}\n",Yourmoney);
			shi--;
			qlen--;
			Other-=Hurt;
			Hurt=1;
			printf("是实弹\n");
			Sleep(500);
			IsOver();
			if(shoukao_you==1){
				shoukao_you=0;
				Yourmoney+=1000.0;
				printf("因为小菜鸡使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}
	}else if(x==2){
		printf("小菜鸡决定向自己开枪");
		wait();
		if(q[qlen]==2){
			Yourmoney+=(double)(2000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
			kong--;
			qlen--;
			Hurt=1;
			printf("是空弹\n");
		}else{
			Yourmoney+=5000.0*(1+(double)(shi)*1.0/(double)(shi+kong));
			T++;
			shi--;
			qlen--;
			Your-=Hurt;
			Hurt=1;
			printf("是实弹\n");
			Sleep(500);
			IsOver();
			if(shoukao_you==1){
				shoukao_you=0;
				printf("因为小菜鸡使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}
	}else if(x==3){//{"放大镜","手铐","小刀","烟","饮料"};
		if(daoju[0]){
			daoju[0]--;
			daojulen--;
			printf("小菜鸡使用了放大镜\n");
			wait();
			printf("\n小菜鸡看到了");
			if(q[qlen]==1){
				printf("实弹\n");
				Yourmoney+=2500.0;
			}else{
				printf("空弹\n");
			}
			Sleep(500);
			printf("\n");
		}else{
			printf("小菜鸡现在没有放大镜\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==4){
		if(daoju[1]){
			if(!shoukao_you){
				daoju[1]--;
				daojulen--;
				printf("小菜鸡使用了手铐\n");
				printf("小菜鸡获得了连开两枪的机会\n");
				shoukao_you=1;
			}else{
				printf("你已经用过手铐了\n");
			}
			Sleep(1145);
			system("cls"); 
		}else{
			printf("你傻啊，小菜鸡现在没有手铐\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==5){
		if(daoju[2]){
			if(Hurt==1){
				daoju[2]--;
				daojulen--;
				printf("小菜鸡使用了小刀\n");
				printf("若下一发为实弹则伤害+1\n");
				Yourmoney+=500.0;
				Hurt=2;
			}else{
				printf("你傻啊，小菜鸡已经用过小刀了\n");
			}
			Sleep(1145);
			system("cls");
		}else{
			printf("你傻啊，小菜鸡现在没有小刀\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==6){
		if(daoju[3]){
			if(Your^6){
				daoju[3]--;
				daojulen--;
				printf("小菜鸡使用了烟\n");
				printf("小菜鸡回复了一点生命\n");
				Yourmoney+=500.0;
				Your++;
			}else{
				printf("小菜鸡现在不需要烟\n");
			}
			Sleep(1145);
		}else{
			printf("小菜鸡现在没有烟\n");
			Sleep(1145);
			system("cls");
		}
	}else{
		if(daoju[4]){
			daoju[4]--;
			daojulen--;
			printf("小菜鸡使用了饮料\n");
			wait();
			printf("\n");
			printf("小菜鸡退了一发"); 
			if(q[qlen]==2){
				printf("空弹");
				kong--;
			}else{
				printf("实弹");
				Yourmoney+=500.0;
				shi--;
			}
			qlen--;
			Sleep(500);
		}else{
			printf("小菜鸡现在没有饮料\n");
			Sleep(1145);
			system("cls");
		}
	}
	Sleep(1000);
	system("cls");
}
int Know;//通过放大镜得知下一发子弹 
int shoukaoemo;
void fightyou(){
	printf("**恶魔决定向你开枪");
	T++;
	wait();
	if(q[qlen]==2){
		Yourmoney+=(double)(2000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
		kong--;
		qlen--;
		Hurt=1;
		Know=0;
		printf("是空弹\n");
		if(shoukaoemo){
			printf("因为**恶魔使用了手铐，所以可以再来一次（玩完这局之后，他可能就要去见警察蜀黍了）\n");
			T--;
			Sleep(500);
			shoukaoemo=0;
		}
	}else{
		Yourmoney+=(double)(5000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
		shi--;
		qlen--;
		Your-=Hurt;
		Hurt=1;
		printf("是实弹\n");
		Know=0;
		Sleep(500);
		IsOver();
		if(shoukaoemo){
			printf("因为**恶魔使用了手铐，所以可以再来一次（玩完这局之后，他可能就要去见警察蜀黍了）\n");
			Yourmoney+=1000.0;
			T--;
			Sleep(500);
			shoukaoemo=0;
		}
	}
}
void fightemo(){
	printf("**恶魔决定向自己开枪");
	wait();
	if(q[qlen]==2){
		Yourmoney+=2000.0*(1+(double)(shi)*1.0/(double)(shi+kong));
		kong--;
		qlen--;
		printf("是空弹\n");
		Know=0;
	}else{
		Yourmoney+=5000.0*(1+(double)(kong)*1.0/(double)(shi+kong));
		shi--;
		T++;
		qlen--;
		Other-=Hurt;
		Hurt=1;
		printf("是实弹\n");
		Know=0;
		Sleep(500);
		IsOver();
		if(shoukaoemo){
			printf("因为**恶魔使用了手铐，所以可以再来一次\n");
			T--;
			Sleep(500);
			shoukaoemo=0;
		}
	}
}
void Timeother(){
	printf("小菜鸡的生命:%d/6\n**恶魔生命:%d/6\n",Your,Other);
	printf("剩余实弹数:%d    剩余空弹数:%d\n",shi,kong);
	printf("你现在拥有的道具:\n");
	for(int i=0;i<=4;i++){
		cout<<daojuname[i];
		printf("%d",daoju[i]);
		printf("个");
		if(i!=4){
			printf(",");
		}
	}
	printf("\n");
	printf("**恶魔现在拥有的道具:\n");
	for(int i=0;i<=4;i++){
		cout<<daojuname[i];
		printf("%d",daoju1[i]);
		printf("个");
		if(i!=4){
			printf(",");
		}
	}
	printf("\n");
	printf("现在是**恶魔的回合\n");
	Sleep(1500);
	
	if(Other!=6){
		if(daoju1[3]){
			daoju1[3]--;
			daojulen1--;
			printf("**恶魔使用了烟\n");
			printf("**恶魔回复了一点生命\n");
			Other++;
			Yourmoney+=500.0;
			Sleep(1145);
			system("cls");
			return ;
		}
	}
	if(Know==0&&kong==0){
		Know=1;
	}
	if(Know==0){
		if(abs(shi-kong)<2&&kong!=0){
			if(daoju1[0]){
				daoju1[0]--;
				daojulen1--;
				printf("**恶魔使用了放大镜\n");
				wait();
				printf("\n**恶魔看到了");
				if(q[qlen]==1){
					printf("实弹");
					Yourmoney+=2500.0;
					Know=1;
				}else{
					printf("空弹");
					Know=2;
				}
				Sleep(1145);
				system("cls");
				return ;
			}
		}
	}else if(Know==1){
		if(Hurt==1&&daoju1[2]){
			daoju1[2]--;
			daojulen1--;
			Hurt++;
			printf("**恶魔使用了小刀\n");
			printf("若下一发为实弹则伤害+1");
			Yourmoney+=500.0;
			Sleep(1145);
			system("cls");
			return ;
		}else{
			if(shi>=kong+1&&daoju1[1]&&shoukaoemo!=1){
				daoju1[1]--;
				daojulen1--;
				shoukaoemo=1;
				printf("**恶魔使用了手铐\n");
				printf("**恶魔获得了连开两枪的机会\n");
				Sleep(1145);
				system("cls");
				return ;
			}
			fightyou();
			system("cls");
			return ;
		}
	}else{
		if(daoju1[4]){
			daoju1[4]--;
			daojulen1--;
			printf("恶魔使用了饮料\n");
			wait();
			printf("\n");
			printf("恶魔退了一发"); 
			if(q[qlen]==2){
				printf("空弹");
				kong--;
			}else{
				printf("实弹");
				shi--;
			}
			Know=0;
			qlen--;
			Sleep(500);
			Sleep(1145);
			system("cls");
			return ;
		}else{
			fightemo();
			Sleep(1145);
			system("cls");
			return ;
		}
	}
	if(shi>=kong){
		fightyou();
	}else{
		fightemo();
	}
	Sleep(1145);
	system("cls");
}
void Play(){
	while(1){
		if(shi==0){
			build_gun();
			T=0;
			continue;
		}
		if(T%2==0){
			Timeyou();
		}else{
			Timeother();
		}
	}
}
void danrenplay(){
	for(int i=1;i<=3;i++){
		printf(".");
//      Sleep(1000);
	}
	printf("\n");
	printf("又来了一位挑战者...\n");
	Sleep(1000);
	int x;
	while(1){
		printf("准备好参与恶魔的游戏吗？胜者带走奖金，败者将会在此长眠\n1.好的\n2.没问题\n");
		scanf("%d",&x);
		if(x==1||x==2){
			break;
		}
		printf("输入不合法\n");
		Sleep(1145);
		system("cls");
	}
	while(1){
		printf("你清楚我们的规则吗？\n1.清楚\n2.不清楚\n");
		scanf("%d",&x);
		if(x==1||x==2){
			break;
		}
		printf("输入不合法，你真像个**\n");
		Sleep(1145);
		system("cls");
	}
	if(x==1){
		
	}else{
		for(int i=1;i<=3;i++){
			printf(".");
			Sleep(1000);
		}
		printf("\n");
		printf("规则:\n");
		printf("你和恶魔都各有“老六”点生命\n") ;
		printf("每一回合开始前，你将知道一共有几发实弹，几发空弹，同时双方都将获得4个道具作为补给（上限为8个）\n"); 
		printf("每一回合，你可以选择对自己开枪，对恶魔开枪或者使用道具\n");
		printf("如果你对自己开枪，若为空弹，则可以继续行动，否则，停止行动\n");
		printf("如果你对恶魔开枪，无论如何，都将停止行动\n");
		printf("道具一览：\n"); 
		printf("放大镜：可以知道下一发子弹是空弹还是实弹\n");
		printf("手铐：增加一次本回合的行动次数\n");
		printf("小刀：若下一发子弹为实弹，则伤害+1\n");
		printf("烟：可以回复1点体力\n");
		printf("饮料：可以退一发子弹\n");
		system("pause");
		system("cls");
	}
	
	printf("好吧\n");
	Sleep(1145);
	printf("游戏将要开始了哦\n");
	Sleep(1145);
	system("cls");
	Play();
}
void IsOver_duo(){
	if(Your<=0){
		printf("玩家B被关进监狱了\n玩家A获得了奖金$%.2lf\n",Yourmoney); 
		system("pause");
		exit(0);
	}else if(Other<=0){
		printf("玩家A被关进监狱了\n玩家B获得了奖金$%.2lf\n",Yourmoney); 
		system("pause");
		exit(0);
	}
	
}
void build_gun_duo(){
	kong=Rand(1,4);
	shi=Rand(1,4);
	qlen=0;
	printf("%d发实弹,%d发空弹\n",shi,kong);
	int a1=kong,a2=shi;
	for(int i=1;i<=kong+shi;i++){
//      Sleep(50);
		int sum=Rand(1,a1+a2);
		if(sum<=a1){
			a1--;
			q[++qlen]=2;
		}else{
			a2--;
			q[++qlen]=1;
		}
	}
	int maxn=min(2,8-daojulen);
	printf("玩家A获得了%d个道具:\n",maxn);
	daojulen+=maxn;
	for(int i=1;i<=maxn;i++){
//      Sleep(50);
		int kkk=Rand(0,4);
		daoju[kkk]++;
		cout<<daojuname[kkk];
		if(i!=maxn){
			printf(",");
		}
	}
	printf("\n");
	maxn=min(2,8-daojulen1);
	printf("玩家B获得了%d个道具:\n",maxn);
	daojulen1+=maxn;
	for(int i=1;i<=maxn;i++){
		int kkk=Rand(0,4);
		daoju1[kkk]++;
		cout<<daojuname[kkk];
		if(i!=maxn){
			printf(",");
		}
	}
	printf("\n");
	system("pause");
	system("cls");
}
void Timeyou_duo(){
	int x;
	while(1){
		printf("玩家A的生命:%d/4\n玩家B的生命:%d/4\n",Your,Other);
		printf("剩余实弹数:%d    剩余空弹数:%d\n",shi,kong);
		printf("玩家A现在拥有的道具:\n");
		for(int i=0;i<=4;i++){
			cout<<daojuname[i];
			printf("%d",daoju[i]);
			printf("个");
			if(i!=4){
				printf(",");
			}
		}
		printf("\n");
		printf("玩家B现在拥有的道具:\n");
		for(int i=0;i<=4;i++){
			cout<<daojuname[i];
			printf("%d",daoju1[i]);
			printf("个");
			if(i!=4){
				printf(",");
			}
		}
		printf("\n");
		printf("现在是玩家A的回合\n");
		printf("玩家A要\n1.向玩家B开枪\n2.向自己开枪\n");
		for(int i=0;i<=4;i++){
			printf("%d.使用",i+3);
			cout<<daojuname[i]<<'\n';
		}
		scanf("%d",&x);
		if(1<=x&&x<=7){
			break;
		}
		printf("输入不合法，你真是个**\n");
		Sleep(1145);
		system("cls");
	}
	if(x==1){
		printf("玩家A决定向玩家B开枪");
		T++;
		wait();
		if(q[qlen]==2){
			Yourmoney+=(double)(2000.0*(Hurt*1.0)*(1+(double)(shi)*1.0/(double)(shi+kong)));
			kong--;
			qlen--;
			Hurt=1;
			printf("是空弹\n");
			if(shoukao_you==1){
				shoukao_you=0;
				printf("因为玩家A使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}else{
//          printf("((%lf))\n",Yourmoney);
			Yourmoney+=(double)(5000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
//          printf("{{%lf}}\n",Yourmoney);
			shi--;
			qlen--;
			Other-=Hurt;
			Hurt=1;
			printf("是实弹\n");
			Sleep(500);
			IsOver_duo();
			if(shoukao_you==1){
				shoukao_you=0;
				Yourmoney+=1000.0;
				printf("因为玩家A使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}
	}else if(x==2){
		printf("玩家A决定向自己开枪");
		wait();
		if(q[qlen]==2){
			Yourmoney+=(double)(2000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
			kong--;
			qlen--;
			Hurt=1;
			printf("是空弹\n");
		}else{
			Yourmoney+=5000.0*(1+(double)(shi)*1.0/(double)(shi+kong));
			T++;
			shi--;
			qlen--;
			Your-=Hurt;
			Hurt=1;
			printf("是实弹\n");
			Sleep(500);
			IsOver_duo();
			if(shoukao_you==1){
				shoukao_you=0;
				printf("因为玩家A使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}
	}else if(x==3){//{"放大镜","手铐","小刀","烟","饮料"};
		if(daoju[0]){
			daoju[0]--;
			daojulen--;
			printf("玩家A使用了放大镜\n");
			wait();
			printf("\n玩家A看到了");
			if(q[qlen]==1){
				printf("实弹\n");
				Yourmoney+=2500.0;
			}else{
				printf("空弹\n");
			}
			Sleep(500);
			printf("\n");
		}else{
			printf("你傻啊，玩家A现在没有放大镜\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==4){
		if(daoju[1]){
			if(!shoukao_you){
				daoju[1]--;
				daojulen--;
				printf("玩家A使用了手铐\n");
				printf("玩家A获得了连开两枪的机会\n");
				shoukao_you=1;
			}else{
				printf("你傻啊，玩家A已经用过手铐了\n");
			}
			Sleep(1145);
			system("cls"); 
		}else{
			printf("你傻啊，玩家A现在没有手铐\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==5){
		if(daoju[2]){
			if(Hurt==1){
				daoju[2]--;
				daojulen--;
				printf("玩家A使用了小刀\n");
				printf("若下一发为实弹则伤害+1\n");
				Yourmoney+=500.0;
				Hurt=2;
			}else{
				printf("你傻啊，玩家A已经用过小刀了\n");
			}
			Sleep(1145);
			system("cls");
		}else{
			printf("你傻啊，玩家A现在没有小刀\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==6){
		if(daoju[3]){
			if(Your^4){
				daoju[3]--;
				daojulen--;
				printf("玩家A使用了烟\n");
				printf("玩家A回复了一点生命\n");
				Yourmoney+=500.0;
				Your++;
			}else{
				printf("你傻啊，玩家A现在不需要烟\n");
			}
			Sleep(1145);
		}else{
			printf("你傻啊，玩家A现在没有烟\n");
			Sleep(1145);
			system("cls");
		}
	}else{
		if(daoju[4]){
			daoju[4]--;
			daojulen--;
			printf("玩家A使用了饮料\n");
			wait();
			printf("\n");
			printf("玩家A退了一发"); 
			if(q[qlen]==2){
				printf("空弹");
				kong--;
			}else{
				printf("实弹");
				Yourmoney+=500.0;
				shi--;
			}
			qlen--;
			Sleep(500);
		}else{
			printf("你傻啊，玩家A现在没有饮料\n");
			Sleep(1145);
			system("cls");
		}
	}
	Sleep(1000);
	system("cls");
}
void Timeother_duo(){
	int x;
	while(1){
		printf("玩家A的生命:%d/4\n玩家B的生命:%d/4\n",Your,Other);
		printf("剩余实弹数:%d    剩余空弹数:%d\n",shi,kong);
		printf("玩家A现在拥有的道具:\n");
		for(int i=0;i<=4;i++){
			cout<<daojuname[i];
			printf("%d",daoju[i]);
			printf("个");
			if(i!=4){
				printf(",");
			}
		}
		printf("\n");
		printf("玩家B现在拥有的道具:\n");
		for(int i=0;i<=4;i++){
			cout<<daojuname[i];
			printf("%d",daoju1[i]);
			printf("个");
			if(i!=4){
				printf(",");
			}
		}
		printf("\n");
		printf("现在是玩家B的回合\n");
		printf("玩家B要\n1.向玩家A开枪\n2.向自己开枪\n");
		for(int i=0;i<=4;i++){
			printf("%d.使用",i+3);
			cout<<daojuname[i]<<'\n';
		}
		scanf("%d",&x);
		if(1<=x&&x<=7){
			break;
		}
		printf("输入不合法\n");
		Sleep(1145);
		system("cls");
	}
	if(x==1){
		printf("玩家B决定向玩家A开枪（泰裤辣）");
		T++;
		wait();
		if(q[qlen]==2){
			Yourmoney+=(double)(2000.0*(Hurt*1.0)*(1+(double)(shi)*1.0/(double)(shi+kong)));
			kong--;
			qlen--;
			Hurt=1;
			printf("是空弹\n");
			if(shoukaoemo==1){
				shoukaoemo=0;
				printf("因为玩家B使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}else{
//          printf("((%lf))\n",Yourmoney);
			Yourmoney+=(double)(5000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
//          printf("{{%lf}}\n",Yourmoney);
			shi--;
			qlen--;
			Your-=Hurt;
			Hurt=1;
			printf("是实弹\n");
			Sleep(500);
			IsOver_duo();
			if(shoukaoemo==1){
				shoukaoemo=0;
				Yourmoney+=1000.0;
				printf("因为玩家B使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}
	}else if(x==2){
		printf("玩家B决定向自己开枪（不知道他（她）咋想的，竟然不想活了）");
		wait();
		if(q[qlen]==2){
			Yourmoney+=(double)(2000.0*(Hurt*1.0)*(1+(double)(kong)*1.0/(double)(shi+kong)));
			kong--;
			qlen--;
			Hurt=1;
			printf("是空弹\n");
		}else{
			Yourmoney+=5000.0*(1+(double)(shi)*1.0/(double)(shi+kong));
			T++;
			shi--;
			qlen--;
			Other-=Hurt;
			Hurt=1;
			printf("是实弹\n");
			Sleep(500);
			IsOver_duo();
			if(shoukao_you==1){
				shoukao_you=0;
				printf("因为玩家B使用了手铐，所以可以再来一次\n");
				Sleep(500);
				T--;
			}
		}
	}else if(x==3){//{"放大镜","手铐","小刀","烟","饮料"};
		if(daoju1[0]){
			daoju1[0]--;
			daojulen1--;
			printf("玩家B使用了放大镜\n");
			wait();
			printf("\n玩家B看到了");
			if(q[qlen]==1){
				printf("实弹\n");
				Yourmoney+=2500.0;
			}else{
				printf("空弹\n");
			}
			Sleep(500);
			printf("\n");
		}else{
			printf("你傻啊，玩家B现在没有放大镜\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==4){
		if(daoju1[1]){
			if(!shoukaoemo){
				daoju1[1]--;
				daojulen1--;
				printf("玩家B使用了手铐\n");
				printf("玩家B获得了连开两枪的机会\n");
				shoukaoemo=1;
			}else{
				printf("你傻啊，玩家B已经用过手铐了\n");
			}
			Sleep(1145);
			system("cls"); 
		}else{
			printf("你傻啊，玩家B现在没有手铐\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==5){
		if(daoju1[2]){
			if(Hurt==1){
				daoju1[2]--;
				daojulen1--;
				printf("玩家B使用了小刀\n");
				printf("若下一发为实弹则伤害+1\n");
				Yourmoney+=500.0;
				Hurt=2;
			}else{
				printf("你傻啊，玩家B已经用过小刀了\n");
			}
			Sleep(1145);
			system("cls");
		}else{
			printf("你傻啊，玩家B现在没有小刀\n");
			Sleep(1145);
			system("cls");
		}
	}else if(x==6){
		if(daoju1[3]){
			if(Other^4){
				daoju1[3]--;
				daojulen1--;
				printf("玩家B使用了烟\n");
				printf("玩家B回复了一点生命\n");
				Yourmoney+=500.0;
				Other++;
			}else{
				printf("你傻啊，玩家B现在不需要烟\n");
			}
			Sleep(1145);
		}else{
			printf("玩家B现在没有烟\n");
			Sleep(1145);
			system("cls");
		}
	}else{
		if(daoju1[4]){
			daoju1[4]--;
			daojulen1--;
			printf("玩家B使用了饮料\n");
			wait();
			printf("\n");
			printf("玩家B退了一发"); 
			if(q[qlen]==2){
				printf("空弹");
				kong--;
			}else{
				printf("实弹");
				Yourmoney+=500.0;
				shi--;
			}
			qlen--;
			Sleep(500);
		}else{
			printf("你傻啊，玩家B现在没有饮料\n");
			Sleep(1145);
			system("cls");
		}
	}
	Sleep(1000);
	system("cls");
}
int asdasd;
void duorenplay(){
	while(1){
		if(shi==0){
			build_gun_duo();
			T=asdasd;
			asdasd++;
			continue;
		}
		if(T%2==0){
			Timeyou_duo();
		}else{
			Timeother_duo();
		}
	}
}
int main(){
	srand(time(0));
	int x;
	while(1){
		printf("请选择你死的方式：\n1.单人\n2.双人（此模式中，生命值为4，道具补给为2）\n");
		scanf("%d",&x);
		if(x==1||x==2){
			break;
		}
		printf("你个傻逼\n");
		Sleep(1145);
		system("cls");
	}
	system("cls");
	if(x==1){
		danrenplay();
	}else{
		Your=Other=4;
		duorenplay();
	}
	return 0;
}
